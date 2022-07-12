#include <QTRSensors.h>
/////////////////////////////////////////////////////////////////////////////////////
//*************  Programa realizado por MARCO A. CABALLERO MORENO***************   //
// Solo para fines educativos   
// robot velocista mini FK BOT  V 2.0                                            //
// micro motores pololu MP 10:1, sensores qtr 8rc, driver drv8833, arduino nano    //
//                                     05/12/2014                  
// ACTUALIZADO 29/3/2015            
/////////////////////////////////////////////////////////////////////////////////////
 
#define NUM_SENSORS   8     //numero de sensores usados
#define TIMEOUT       2000  // tiempo de espera para dar resultado en uS
#define EMITTER_PIN   14     //pin led on
///////////////pines arduino a utilizar/////////////////////
#define led1          13 
//#define led2          4  
#define mot_i         10
#define mot_d         6
#define sensores      8
#define boton_1       12  //pin para boton
#define pin_pwm_i     11
#define pin_pwm_d     5
 
QTRSensorsRC qtrrc((unsigned char[]) {8, 18, 19, 15, 16, 9, 8, 7, 4, 14}
,NUM_SENSORS, TIMEOUT, EMITTER_PIN);
 
//variables para almacenar valores de sensores y posicion
unsigned int sensorValues[NUM_SENSORS];
unsigned int position=0;
 
/// variables para el pid
int  derivativo=0, proporcional=0, integral=0; //parametros
int  salida_pwm=0, proporcional_pasado=0;
 
///////////////AQUI CAMBIEREMOS LOS PARAMETROS DE NUESTRO ROBOT!!!!!!!!!!!!!!!
int velocidad=135;              //variable para la velocidad, el maximo es 255
float Kp=0.18, Kd=4, Ki=0.001;  //constantes
//variable para escoger el tipo de linea
int linea=0;                    //  0 para lineas negra, 1 para lineas blancas
 
void setup()
{
 delay(800);
 pinMode(mot_i, OUTPUT);//pin de direccion motor izquierdo
 pinMode(mot_d, OUTPUT);//pin de direccion motor derecho
 pinMode(led1, OUTPUT); //led1
// pinMode(led2, OUTPUT); //led2
 pinMode(boton_1, INPUT); //boton 1 como pull up
         
 for (int i = 0; i <40; i++)  //calibracion durante 2.5 segundos,
 {                                 //para calibrar es necesario colocar los sensores sobre la superficie negra y luego 
  digitalWrite(led1, HIGH);  //la blanca
  delay(20);
  qtrrc.calibrate();    //funcion para calibrar sensores   
  digitalWrite(led1, LOW);  
  delay(20);
 }
digitalWrite(led1, LOW); //apagar sensores para indicar fin de calibracion 
delay(400); 
//digitalWrite(led2,HIGH); //encender led 2 para indicar la
while(true)
{
    int x=digitalRead(boton_1); //leemos y guardamos el valor
                                      // del boton en variable x
    delay(100);
    if(x==0) //si se presiona boton 
    {
//        digitalWrite(led2,LOW); //indicamos que se presiono boton
        digitalWrite(led1,HIGH); //encendiendo led 1
        delay(100);
        break; //saltamos hacia el bucle principal
    }
}
}       
 
 
void loop()
{
 
 //pid(0, 120, 0.18, 0.001, 4 );
  pid(linea,velocidad,Kp,Ki,Kd); //funcion para algoritmo pid 
                                 //primer parametro: 0 para lineas negras, tipo 1 para lineas blancas
                                 //segundo parametro: velocidad pwm de 0 a 255
                                 //tercer parametro: constante para accion proporcional
                                 //cuarto parametro: constante para accion integral
                                 //quinto parametro: constante para accion derivativa
  //frenos_contorno(0,700);
  frenos_contorno(linea,700); //funcion para frenado en curvas tipo 
                              //primer parametro :0 para lineas negras, tipo 1 para lineas blancas
                              //segundo parametro:flanco de comparación va desde 0 hasta 1000 , esto para ver 
}
 
////////funciones para el control del robot////
 void pid(int linea, int velocidad, float Kp, float Ki, float Kd)
{
  position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, linea); //0 para linea negra, 1 para linea blanca
  proporcional = (position) - 3500; // set point es 3500, asi obtenemos el error
  integral=integral + proporcional_pasado; //obteniendo integral
  derivativo = (proporcional - proporcional_pasado); //obteniedo el derivativo
  if (integral>1000) integral=1000; //limitamos la integral para no causar problemas
  if (integral<-1000) integral=-1000;
  salida_pwm =( proporcional * Kp ) + ( derivativo * Kd )+(integral*Ki);
   
  if (  salida_pwm > velocidad )  salida_pwm = velocidad; //limitamos la salida de pwm
  if ( salida_pwm < -velocidad )  salida_pwm = -velocidad;
   
  if (salida_pwm < 0)
 {
  motores(velocidad+salida_pwm, velocidad);
 }
 if (salida_pwm >0)
 {
  motores(velocidad, velocidad-salida_pwm);
 }
 
 proporcional_pasado = proporcional;  
}
 
//funcion para control de motores
void motores(int motor_izq, int motor_der)
{
  if ( motor_izq >= 0 )  //motor izquierdo
 {
  digitalWrite(mot_i,HIGH); // con high avanza
  analogWrite(pin_pwm_i,255-motor_izq); //se controla de manera
                                        //inversa para mayor control
 }
 else
 {
  digitalWrite(mot_i,LOW); //con low retrocede
  motor_izq = motor_izq*(-1); //cambio de signo
  analogWrite(pin_pwm_i,motor_izq); 
 }
 
  if ( motor_der >= 0 ) //motor derecho
 {
  digitalWrite(mot_d,HIGH);
  analogWrite(pin_pwm_d,255-motor_der);
 }
 else
 {
  digitalWrite(mot_d,LOW);
  motor_der= motor_der*(-1);
  analogWrite(pin_pwm_d,motor_der);
 }
 
   
}
 
void frenos_contorno(int tipo,int flanco_comparacion)
{
   
if(tipo==0)
{
  if(position<=50) //si se salio por la parte derecha de la linea
 {
  motores(-120,140); //debido a la inercia, el motor 
                                  //tendera a seguri girando
                                  //por eso le damos para atras , para que frene
                                 // lo mas rapido posible 
  while(true)  
  {
   qtrrc.read(sensorValues); //lectura en bruto de sensor   
   if( sensorValues[0]>flanco_comparacion || sensorValues[1]>flanco_comparacion ) 
   //asegurar que esta en linea
   {
    break;
   } 
  }
 }
 
 if (position>=6550) //si se salio por la parte izquierda de la linea
 { 
  motores(140,-120);
  while(true)
  {
   qtrrc.read(sensorValues);
   if(sensorValues[7]>flanco_comparacion || sensorValues[6]>flanco_comparacion )
   {
    break;
   }  
  }
 }
}
 
if(tipo==1) //para linea blanca con fondo negro
{
 if(position<=50) //si se salio por la parte derecha de la linea
 {
  motores(-80,90); //debido a la inercia el motor 
                   //tendera a seguri girando
                   //por eso le damos para atras  
                   //para que frene lo mas rapido posible 
  while(true)  
  {
   qtrrc.read(sensorValues); //lectura en bruto de sensor
   if(sensorValues[0]<flanco_comparacion || sensorValues[1]<flanco_comparacion )   //asegurar que esta en linea
   {
    break;
   }
  }
 }
 
 if(position>=6550) //si se salio por la parte izquierda de la linea
 { 
  motores(90,-80);
  while(true)
  {
   qtrrc.read(sensorValues);
   if(sensorValues[7]<flanco_comparacion || sensorValues[6]<flanco_comparacion)
   {
    break;
   }  
  }
 }
}
}
