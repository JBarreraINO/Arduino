#include <QTRSensors.h>
/////////////////////////////////////////////////////////////////////////////////////
//*************  Programa realizado por MARCO A. CABALLERO MORENO***************   //
// Solo para fines educativos   
// robot velocista mini FK BOT  V 2.0                                            //
// micro motores pololu MP 10:1, sensores qtr 8rc, driver drv8833, arduino nano    //
//                                     05/12/2014                  
// ACTUALIZADO 29/3/2015            
/////////////////////////////////////////////////////////////////////////////////////
 
#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             12  // emitter is controlled by digital pin 2
///////////////pines arduino a utilizar/////////////////////
#define led1          11

#define mi1       4
#define mi2       5
#define pwmi      3   //~
#define md1       7
#define md2       8
#define pwmd      9   //~
int boton_1=A7;
QTRSensorsRC qtrrc((unsigned char[]) {14,15,16,17,18,2,10,19},
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

 

unsigned int position=0;
 
/// variables para el pid
int  derivativo=0, proporcional=0, integral=0; //parametros
int  salida_pwm=0, proporcional_pasado=0;
 
///////////////AQUI CAMBIEREMOS LOS PARAMETROS DE NUESTRO ROBOT!!!!!!!!!!!!!!!
int velocidad=50;              //variable para la velocidad, el maximo es 255
float Kp=0.18, Kd=4, Ki=0.001;  //constantes
//variable para escoger el tipo de linea
int linea=0;                    //  0 para lineas negra, 1 para lineas blancas
 
void setup()
{
 delay(800);
 pinMode(mi2, OUTPUT);//pin de direccion motor izquierdo
 pinMode(md2, OUTPUT);//pin de direccion motor derecho
pinMode(led1, OUTPUT); //led1
// pinMode(led2, OUTPUT); //led2
 pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);      
 for (int i = 0; i <40; i++)  //calibracion durante 2.5 segundos,
 {                                 //para calibrar es necesario colocar los sensores sobre la superficie negra y luego 
  digitalWrite(led1, HIGH);  //la blanca
  delay(20);
  qtrrc.calibrate();    //funcion para calibrar sensores   
//  digitalWrite(led1, LOW);  
  delay(20);
 }
//digitalWrite(led1, LOW); //apagar sensores para indicar fin de calibracion 
delay(400); 
//digitalWrite(led2,HIGH); //encender led 2 para indicar la
while(true)
{
    int x=analogRead(boton_1); //leemos y guardamos el valor
                                      // del boton en variable x
    delay(100);
    if(x>800) //si se presiona boton 
    {
       // digitalWrite(led2,LOW); //indicamos que se presiono boton
//        digitalWrite(led1,HIGH); //encendiendo led 1
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
 
/*funcion para control de motores
void motores(int motor_izq, int motor_der)
{
  if ( motor_izq >= 0 )  //motor izquierdo
 {
  digitalWrite(mi2,HIGH); // con high avanza
  analogWrite(pin_pwm_i,255-motor_izq); //se controla de manera
                                        //inversa para mayor control
 }
 else
 {
  digitalWrite(mi2,LOW); //con low retrocede
  motor_izq = motor_izq*(-1); //cambio de signo
  analogWrite(pin_pwm_i,motor_izq); 
 }
 
  if ( motor_der >= 0 ) //motor derecho
 {
  digitalWrite(md2,HIGH);
  analogWrite(pin_pwm_d,255-motor_der);
 }
 else
 {
  digitalWrite(md2,LOW);
  motor_der= motor_der*(-1);
  analogWrite(pin_pwm_d,motor_der);
 }
 
   
}
 */
void frenos_contorno(int tipo,int flanco_comparacion)
{
   
if(tipo==0)
{
  if(position<=50) //si se salio por la parte derecha de la linea
 {
  motores(-80,90); //debido a la inercia, el motor 
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
  motores(90,-80);
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
void motores(int motor_izq, int motor_der)
{
  if ( motor_izq >= 0 )  
  {
    digitalWrite(mi1,LOW);
    digitalWrite(mi2,HIGH); 
    analogWrite(pwmi,motor_izq); 
  }
  else
  {
    digitalWrite(mi1,HIGH); 
    digitalWrite(mi2,LOW);
    motor_izq = motor_izq*(-1); 
    analogWrite(pwmi,motor_izq);
  }
 
  if ( motor_der >= 0 ) //motor derecho
  {
    digitalWrite(md1,LOW);
    digitalWrite(md2,HIGH);
    analogWrite(pwmd,motor_der);
  }
  else
  {
    digitalWrite(md1,HIGH);
    digitalWrite(md2,LOW);
    motor_der= motor_der*(-1);
    analogWrite(pwmd,motor_der);
  }
}

