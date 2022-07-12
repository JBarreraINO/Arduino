//CODIGO SEGUIDOR DE LINEA kiiiii
//DESIGN BY JUAN BARRERA
//SAMURAI TEAM BLACK
#include <sky.h>
#include<Servo.h>
 #include <QTRSensors.h>
Servo ESC; //Crear un objeto de clase servo


sky Robot;
#define NUM_SENSORS   8    
#define TIMEOUT       2000  
#define EMITTER_PIN   9
 
int vel = 1000; //amplitud del pulso   
int pin_pwm_i   =  6;
int pin_pwm_d    = 5;
int led1   =       11;
int mot_i =        8;
int mot_d    =     7;


#define sensores      8

QTRSensorsRC qtrrc((unsigned char[]) {9, 10, 13, A0, A1, A3, A5, A4},NUM_SENSORS, TIMEOUT, EMITTER_PIN);
 
//variables para almacenar valores de sensores y posicion
unsigned int sensorValues[NUM_SENSORS];
unsigned int position=0;
 
/// variables para el pid
int  derivativo=0, proporcional=0, integral=0; //parametros
int  salida_pwm=0, proporcional_pasado=0;
 ////////////////////////////////
 ////////////////// SAMURAI /////////
///////////////VARIABLES    //////////////
int velocidad=90;              //variable para la velocidad, el maximo es 255
float Kp=0.45, Kd=4, Ki=0.001;  //constantes
//variable para escoger el tipo de linea
int linea=0;                    //  0 para lineas negra, 1 para lineas blancas
 /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////
  /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////
  /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////
  /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////
  /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////
void setup()
{
 //activacion esc
  ESC.attach(A2);
  ESC.writeMicroseconds(1000); //1000 
 delay(3000); 
 pinMode(led1, OUTPUT); //led1
  Robot.SkyDragon();
    //calibracion QTR     
 for (int i = 0; i <100; i++)  //calibracion durante 2.5 segundos,
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
  
  
     if(Robot.Boton()) //si se presiona boton 
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
turbina(1500);
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
                              //segundo parametro:flanco de comparaciÃ³n va desde 0 hasta 1000 , esto para ver 
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
        Robot.Speeds(velocidad+salida_pwm, velocidad);
 }
 if (salida_pwm >0)
 {
  Robot.Speeds(velocidad, velocidad-salida_pwm);
 }
 
 proporcional_pasado = proporcional;  
}
 
//funcion para control de motores

void motores(int motor_izq, int motor_der)
{
  if ( motor_izq >= 0 )  //motor izquierdo
 {
  digitalWrite(mot_i,HIGH); // con high avanza

 }
 else
 {
  digitalWrite(mot_i,LOW); //con low retrocede

 }
 
  if ( motor_der >= 0 ) //motor derecho
 {
  digitalWrite(mot_d,HIGH);

 }
 else
 {
  digitalWrite(mot_d,LOW);

 }
 
   
}
 
void frenos_contorno(int tipo,int flanco_comparacion)
{
   
if(tipo==0)
{
  if(position<=50) //si se salio por la parte derecha de la linea
 {
  //debido a la inercia, el motor 
       Robot.Speeds (-150,140)  ;     
       turbina(1800);                   
                                
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
   Robot.Speeds(140,-150);
     turbina(2000);
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
   Robot.Speeds(-120,100); //debido a la inercia el motor 
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
   Robot.Speeds(100,-120);
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

void turbina(int vel)
{
    if(vel != 0)
    {
      ESC.writeMicroseconds(vel); //Generar un pulso con el numero recibido
    }
    
}
