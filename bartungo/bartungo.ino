#include <ESC.h>
#define ESC_PIN 10
#define s0      14
#define s1      15
#define s2      16
#define s3      17
#define AI      A4
#define LED_ON  12
#define LED     13
#define BOTON    9
#define GO       2
//#define GO       11
#define pwmi     3   //PWM LEFT MOTOR
#define izq1     5   //LEFT1 MOTOR
#define izq2     4   //LEFT2 MOTOR
#define pwmd     11  //PWM RIGHT MOTOR
#define der1     6   //RIGHT1 MOTOR
#define der2     7   //RIGHT2 MOTOR
//#define BOTON    2
ESC EDF27(ESC_PIN);
int sensores[16];
int digital[16];
int lectura_fondo[16];
int lectura_linea[16];
int umbral[16];
//int umbral=750;
long int sumap, suma, pos, poslast, position;

//////COLOR DE LÍNEA SEGÚN LA BARRA//////////
//I.M BLANCA=1 NEGRA=0
//PHOENIX BLANCA=0 NEGRA=1
int linea=0;
///////////////////////////////////////////

//////BARRAS//////////
//I.M 1
//PHOENIX 0
int barra=1;
///////////////////////////////////////////

//////////////// pid/////////////////////
float KP=0.18;//constante proporcional
float KD=4;//constante derivativa
float KI=0.002;//constante integral
int vel=180;//VELOCIDAD MÁXIMA DEL ROBOT MÁXIMA 255
int turbina=1800;//VELOCIDAD DE LA TURBINA MINIMA 1000 MÁXIMA2000
int veladelante=200;//VELOCIDAD DEL FRENO DIRECCIÓN ADELANTE
int velatras=100;//VELOCIDAD DEL FRENO DIRECCIÓN ATRÁS
int veltest=1650;//VELOCIDAD DE TEST DE LA TURBINA
////////////////////////////////////////

/// datos para la integral
int error1=0;
int error2=0;
int error3=0;
int error4=0;
int error5=0;
int error6=0;
/////////////////////////

///////////variable PID///////////////
int proporcional=0;
int integral=0;
int derivativo=0;
int diferencial=0;
int last_prop;
int setpoint=750;



void setup() {
//Serial.begin(115200);
//TCCR2B = TCCR2B & B11111000 | B00000001;
//set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz

//TCCR2B = TCCR2B & B11111000 | B00000010; 
//set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

TCCR2B = TCCR2B & B11111000 | B00000011;   
//set timer 2 divisor to    32 for PWM frequency of   980.39 Hz

//TCCR2B = TCCR2B & B11111000 | B00000100;   
//set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)

//TCCR2B = TCCR2B & B11111000 | B00000101;   
//set timer 2 divisor to   128 for PWM frequency of   245.10 Hz

//TCCR2B = TCCR2B & B11111000 | B00000110;   
//set timer 2 divisor to   256 for PWM frequency of   122.55 Hz

//TCCR2B = TCCR2B & B11111000 | B00000111;   
//set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz
  pinMode(pwmi, OUTPUT);
  pinMode(izq1, OUTPUT);
  pinMode(izq2, OUTPUT);
  pinMode(pwmd, OUTPUT);
  pinMode(der1, OUTPUT);
  pinMode(der2, OUTPUT);
pinMode(s0,OUTPUT);
pinMode(s1,OUTPUT);
pinMode(s2,OUTPUT);
pinMode(s3,OUTPUT);
pinMode(LED,OUTPUT);
pinMode(LED_ON,OUTPUT);
pinMode(BOTON,INPUT);
pinMode(GO,INPUT);
EDF27.init();
digitalWrite(LED_ON,1);
digitalWrite(LED,1);
delay(500);
while(digitalRead(BOTON));
for(int i=0;i<50;i++){
  fondos();
  digitalWrite(LED,0);
  delay(20);
  digitalWrite(LED,1);
  delay(20);
}
while(digitalRead(BOTON));
for(int i=0;i<50;i++){
  lineas();
  digitalWrite(LED,0);
  delay(20);
  digitalWrite(LED,1);
  delay(20);
}
promedio();
while(digitalRead(BOTON));
for(int i=1000;i<=2000;i++){
  EDF27.setSpeed(i);
  delay(2);
}
EDF27.setSpeed(veltest);
while(digitalRead(BOTON));
EDF27.setSpeed(turbina);

digitalWrite(LED,0);

while(digitalRead(BOTON)==LOW);


}


void loop() {
int go=digitalRead(GO);
while(true){
  int go=digitalRead(GO);
  frenos();
  lectura();
  PID();
  /*
  if(go==0){
    motores(-20,-20);
    break;
  }
*/
}
while(true){
  motores(0,0);
  EDF27.setSpeed(1000);
  
}
}


void fondos(){
  for(int i=0;i<16;i++){
  digitalWrite(s0,i&0x01);
  digitalWrite(s1,i&0x02);
  digitalWrite(s2,i&0x04);
  digitalWrite(s3,i&0x08);
  lectura_fondo[i]=analogRead(AI);
  //Serial.print(lectura_fondo[i]);
  //Serial.print("\t");
}
//Serial.println(" ");
}

void lineas(){
  for(int i=0;i<16;i++){
  digitalWrite(s0,i&0x01);
  digitalWrite(s1,i&0x02);
  digitalWrite(s2,i&0x04);
  digitalWrite(s3,i&0x08);
  lectura_linea[i]=analogRead(AI);
  //Serial.print(lectura_linea[i]);
  //Serial.print("\t");
}
//Serial.println(" ");
}

void promedio(){
  for(int i=0;i<16;i++){
  umbral[i]=750;
  //Serial.print(umbral[i]);
  //Serial.print("\t");
}
//Serial.println(" ");
}

int lectura(void){
  
/*digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,0);sensores[0]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,0);sensores[1]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,0);sensores[2]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,0);sensores[3]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,0);sensores[4]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,0);sensores[5]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,0);sensores[6]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,0);sensores[7]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,1);sensores[8]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,1);sensores[9]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,1);sensores[10]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,1);sensores[11]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,1);sensores[12]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,1);sensores[13]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,1);sensores[14]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,1);sensores[15]=analogRead(AI);*/
/*for(int i=0;i<16;i++){
  if(sensores[i]<=umbral){
    sensores[i]=0;
  }
  Serial.print(sensores[i]);
  Serial.print("\t");
}
Serial.println(" ");*/
for(int i=0;i<16;i++){
  digitalWrite(s0,i&0x01);
  digitalWrite(s1,i&0x02);
  digitalWrite(s2,i&0x04);
  digitalWrite(s3,i&0x08);
  sensores[i]=analogRead(AI);
  if(linea==0){if(sensores[i]<=umbral[i]){digital[i]=0;}else{digital[i]=1;}}
  if(linea==1){if(sensores[i]<=umbral[i]){digital[i]=1;}else{digital[i]=0;}}
  //Serial.print(digital[i]);
  //Serial.print("\t");
}
//Serial.println(" ");
if(barra==0){sumap=(1500*digital[0]+1400*digital[1]+1300*digital[2]+1200*digital[3]+1100*digital[4]+1000*digital[5]+900*digital[6]+800*digital[7]+700*digital[8]+600*digital[9]+500*digital[10]+400*digital[11]+300*digital[12]+200*digital[13]+100*digital[14]+0*digital[15]);}
if(barra==1){sumap=(1500*digital[15]+1400*digital[14]+1300*digital[13]+1200*digital[12]+1100*digital[11]+1000*digital[10]+900*digital[9]+800*digital[8]+700*digital[7]+600*digital[6]+500*digital[5]+400*digital[4]+300*digital[3]+200*digital[2]+100*digital[1]+0*digital[0]);}
suma=(digital[0]+digital[1]+digital[2]+digital[3]+digital[4]+digital[5]+digital[6]+digital[7]+digital[8]+digital[9]+digital[10]+digital[11]+digital[12]+digital[13]+digital[14]+digital[15]);
pos=(sumap/suma);
if(poslast<=100 && pos==-1){
  pos=1500;
}
if(poslast>=1400 && pos==-1){
  pos=0;
}
poslast=pos;
return pos;
}

void PID(){
  proporcional=pos-setpoint;
  derivativo=proporcional-last_prop;
  integral=error1+error2+error3+error4+error5+error6;
  last_prop=proporcional;
  error6=error5;
  error5=error4;
  error4=error3;
  error3=error2;
  error2=error1;
  error1=proporcional;
  int diferencial=(proporcional*KP) + (derivativo*KD) + (integral*KI);
  if(diferencial > vel) diferencial=vel;
  else if(diferencial < -vel) diferencial=-vel;
  (diferencial < 0)?
  motores(vel, vel+diferencial):motores(vel-diferencial, vel);
}

void frenos(){
  if(pos<=150){
    motores(veladelante, -velatras);
  }
  if(pos>=1350){
    motores(-velatras, veladelante);
  }
}

void motores(int izq, int der){//0 hasta 255    0 hasta -255
  ////////////////motor LEFT "IZQUIERDO" ////////////////////////
  if(izq>=0){
    digitalWrite(izq1,HIGH);
    digitalWrite(izq2,LOW);
  }
  else{
    digitalWrite(izq1,LOW);
    digitalWrite(izq2,HIGH);
    izq=izq*(-1);
  }
  analogWrite(pwmi,izq);
  
  ////////////////motor RIGHT "DERECHO" ////////////////////////
  if(der>=0){
    digitalWrite(der1,HIGH);
    digitalWrite(der2,LOW);
  }
  else{
    digitalWrite(der1,LOW);
    digitalWrite(der2,HIGH);
    der=der*(-1);
  }
  analogWrite(pwmd,der);
  
}