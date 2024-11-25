#include <QTRSensors.h>
 
  //entradas
int btn1=     13 ;


int mi1     =  4;
int  mi2      = 2;
int  pwmi     = 3  ; //~
int  md1      = 8;
int  md2      = 7;
int  pwmd      =6 ;  //~
   
 
#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4 // average 4 analog samples per sensor reading
#define EMITTER_PIN             12   // emitter is controlled by digital pin 2
 
QTRSensorsAnalog qtra((unsigned char[]) {7, 6, 5, 4, 3, 2,1,0},NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
int proporcional=0;
int derivativo=0;
int integral=0;
int salida_pwm=0;
int proporcional_pasado=0;
int position=0;
 
////////////////////Parametros PID/////////////////////////////////
int velocidad=120;
//float KP=0.15, KD=2.2, KI=0.006; //reaccion rapida
float KP=0.01, KD=0.15 , KI=0.0001; //reaccion rapida
///////////////////////////////////////////////////////
 
/////////////////parametros de sensado/////////////////////////////
int linea=0; //0 linea negra, 1 para linea blanca
int flanco_color=  0 ;
int en_linea=  500 ;
int ruido= 30;
/////////////////////////////////////////////////////////

 
void setup()
{
    
    pinMode(mi1,OUTPUT);
    pinMode(mi2,OUTPUT);
    pinMode(pwmi,OUTPUT);
    pinMode(md1,OUTPUT);
    pinMode(md2,OUTPUT);
    pinMode(pwmd,OUTPUT);
 

 

  for (int i = 0; i < 200; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
   // turn off Arduino's LED to indicate we are through with calibration
 //Serial.begin(115200);
   //Serial.println();
 
   while(true)
   {
     
      if(btn1==1) 
      {
       
        break;
      }
   }
   
Serial.begin(115200);
//bt.println("Hello, world?");
 
}
 
void loop()
{
  pid(1,velocidad,KP,KI,KD);
  frenos_contorno(600);
 
 Serial.println(position);
 delay(2);
}
 
void pid(int linea, int velocidad, float Kp, float Ki, float Kd)
{
    
   position = qtra.readLine(sensorValues,QTR_EMITTERS_ON, linea, flanco_color, en_linea, ruido);
  //0 linea negra, 1 para linea blanca
   
      //  Serial.println(position);
  proporcional = (position) - 3500; // set point es 3500, asi obtenemos el error
  integral=integral + proporcional_pasado; //obteniendo integral
  derivativo = (proporcional - proporcional_pasado); //obteniedo el derivativo
  int ITerm=integral*KI;
  if(ITerm>=255) ITerm=255;
  if(ITerm<=-255) ITerm=-255;
   
  salida_pwm =( proporcional * KP ) + ( derivativo * KD )+(ITerm);
   
  if (  salida_pwm >velocidad )  salida_pwm = velocidad; //limitamos la salida de pwm
  if ( salida_pwm  <-velocidad )  salida_pwm = -velocidad;
   
  if (salida_pwm < 0)
 {
    int der=velocidad-salida_pwm; //(+)
    int izq=velocidad+salida_pwm;  //(-)
    if(der>=255)der=255;
    if(izq<=0)izq=0;
    motores(izq, der);
 }
 if (salida_pwm >0)
 {
  int der=velocidad-salida_pwm; //(-)
  int izq=velocidad+salida_pwm; //(+)
   
  if(izq >= 255) izq=255;
  if(der <= 0) der=0;
  motores(izq ,der );
 }
 
 proporcional_pasado = proporcional;  
}
 
 
void frenos_contorno(int flanco_comparacion)
{
    if (position <=10) //si se salio por la parte derecha de la linea
    {
      while(true)
      { 
       
        motores(-125,60);
        qtra.read(sensorValues); //lectura en bruto de sensor
        if ( sensorValues[0]<flanco_comparacion || sensorValues[1]<flanco_comparacion || sensorValues[2]<flanco_comparacion || sensorValues[3]<flanco_comparacion || sensorValues[4]<flanco_comparacion || sensorValues[5]<flanco_comparacion || sensorValues[6]<flanco_comparacion || sensorValues[7]<flanco_comparacion)
        {
          break;
        }
         
      }
    }
 
    if (position>=6990) //si se salio por la parte izquierda de la linea
    {
      while(true)
      {
      
        motores(60,-125); 
        qtra.read(sensorValues);
        if (sensorValues[7]<flanco_comparacion || sensorValues[6]<flanco_comparacion|| sensorValues[5]<flanco_comparacion || sensorValues[4]<flanco_comparacion || sensorValues[3]<flanco_comparacion || sensorValues[2]<flanco_comparacion || sensorValues[1]<flanco_comparacion|| sensorValues[0]<flanco_comparacion)
        {
          break;
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
 
