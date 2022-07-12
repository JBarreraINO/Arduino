////////////////////////////
////////velocista////////////
//////////////////////////
#include <QTRSensors.h>

//DECLARACION DE ENTRADAS///////////////
//BOTONES

const int btn1=A7;


int cruzero = 40;   //////////     V   /////



int pwma=9;
int ain2=8;
int ain1=7;
int pwmb=3;
int bin2=4;
int bin1=5;

int P=0.5;
int I=0.001;
int D=4;
int LAST=0;
float vel;

#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   12    // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {14,15,16,17,18,2,10,19},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

unsigned int position=0;

void setup()
{

  pinMode(btn1, INPUT);
    
 
  pinMode(pwma,OUTPUT);
  pinMode(ain1,OUTPUT);
  pinMode(ain2,OUTPUT);
  pinMode(pwmb,OUTPUT);
  pinMode(bin1,OUTPUT);
  pinMode(bin2,OUTPUT);
  
  pinMode(6,OUTPUT);

//Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(1500);
  digitalWrite(6, HIGH);
   for (int j = 0; j < 40; j++)  
 {                                 
                    
  qtrrc.calibrate();       

 }
 
 
                                                                   
 digitalWrite(ain1,LOW);
 digitalWrite(ain2,HIGH);
 
 digitalWrite(bin1,HIGH);
 digitalWrite(bin2,LOW);
 
 analogWrite(pwma,0);
 analogWrite(pwmb,0);
}


void loop()
{
  
  if (analogRead(btn1)>800){

for(;;){ 

  qtrrc.read(sensorValues);

     position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 0);
                                             
                       Serial.println(position) ;                                                                
 P = ((position)-(3500)); /// ERROR
/////FRENOS////
if(P<-3500){
 motores(50,-250);

} else if (P>3500){
 motores(-250,100);



}
/////////////////////////
  else{
 D= (P - LAST); /// ERROR MENOS EL ERROR ANTERIOR , DERIVATIVO
   I=(P+ LAST); //INTEGRAL
   
   
//vel=(P*0.025)+(D*0.095)+(I*0); // PID
   
vel=(P*0.045)+(D*0.07)+(I*0.00065);// para velocidad 120//////estaba en 0.0925

//vel=(P*0.0428)+(D*0.085)+(I*0); //para velocidad 80 kd=0.06

///CRUZERO =VELOCIDAD PUNTA , V

    if(vel >cruzero) vel=cruzero;
    if(vel<-cruzero) vel=-cruzero;

  analogWrite(pwmb,cruzero-vel); // VELOCIDAD PARA EL MOTOR DERECHO
  analogWrite(pwma,cruzero+vel); //  VELOCIDAD PARA EL MOTOR IZQUIERDO

 digitalWrite(ain1,LOW);   ///FRENTE
 digitalWrite(ain2,HIGH);
 digitalWrite(bin1,HIGH);  ///FRENTE
 digitalWrite(bin2,LOW);
 
LAST=P;
  }
}////BUCLE INFINITO
}///PRESIONO BOTON
}///FIN DEL LOOP

void motores(int motor_izq, int motor_der)
{
  if ( motor_izq >= 0 )  
  {
    digitalWrite(bin2,LOW);
    digitalWrite(bin1,HIGH); 
    analogWrite(pwmb,motor_izq); 
  }
  else
  {
    digitalWrite(bin2,HIGH); 
    digitalWrite(bin1,LOW);
    motor_izq = motor_izq*(-1); 
    analogWrite(pwmb,motor_izq);
  }
 
  if ( motor_der >= 0 ) //motor derecho
  {
    digitalWrite(ain1,LOW);
    digitalWrite(ain2,HIGH);
    analogWrite(pwma,motor_der);
  }
  else
  {
    digitalWrite(ain1,HIGH);
    digitalWrite(ain2,LOW);
    motor_der= motor_der*(-1);
    analogWrite(pwma,motor_der);
  }
}




