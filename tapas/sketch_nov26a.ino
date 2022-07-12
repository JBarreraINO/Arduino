#include <Servo.h>

Servo Rojo;
Servo Verde,Azul ;

int dato_serial =0; // para los datos de entrada serie
float C;
int temp;
int color=0;
int conteo=0;
int conteoazul=0;
int conteorojo=0;
int conteoverde=0;
int conteonegro=0;
long milivolts;
long temperatura;
const int sensor = A2;
const int ledrojo = 5;
const int ledazul = 6;
int total=-1;
void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
 Rojo.attach(4);
  Verde.attach(3);
  Azul.attach(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  milivolts = (analogRead (sensor)*5000L) / 1023;
  temperatura=milivolts/10;
  if (Serial.available() > 0) {  // si ha llegado un dato serial

  int input=Serial.read(); 
   if(input =='1'){ 
   digitalWrite(13,HIGH);
   }




if(input =='2'){
 digitalWrite(13, LOW);
}

if (input=='4')
{
  total=0;
  conteonegro=0;
  conteorojo=0;
  conteoazul=0;
  conteoverde=0;
 }
}
   int sensorValue = analogRead(A0);
   //Serial.print(    "            ");
  // Serial.print(    "valor sensor: ");
  //Serial.print(sensorValue);
  //Serial.print(                           "             -          ");
 Serial.print("                              ");
  Serial.print  (                       temperatura);
  Serial.print  (" ° ");
    Serial.print  (    "   -                           " );
    Serial.print (             conteonegro             );
    Serial.print(    "      -              ");
     Serial.print (             conteoazul           );
       Serial.print(    "      -             ");
     Serial.print (             conteoverde             );
      Serial.print(    "      -                  ");
     Serial.print(      conteorojo         );
      Serial.print(    "      -                   ");

     
     
  //Serial.println(                           " grados");
  delay (2000);
 

 
 if(sensorValue<590&&sensorValue>300)
  {
      
  color=1;
  conteoazul++;
    
    
  ;// waits 15ms for the servo to reach the position
  }
  else if(sensorValue<1300&&sensorValue>871)
  {
  
   conteoverde++;
   color=2;
   
  }
   else if(sensorValue<870&&sensorValue>520)
  {
  
  conteorojo++;
  

  color=3;}

  else if(sensorValue<35&&sensorValue>0)
  {
   
  conteonegro++;
  
   
  color=4;}

total=conteonegro+conteorojo+conteoazul+conteoverde;
 Serial.print(total);
Serial.print(    "    -             ");
 Serial.println(sensorValue);
       
  switch (color) {
    case 1:
   
    Azul.write(180);
    delay(500);
       Azul.write(90);
    break;
    case 2:
    
    Verde.write(180);
    delay(500);
        Verde.write(90);
    break;
    case 3:
    
    Rojo.write(180);
    delay(500);
    Rojo.write(90);
    break;
    case 4 :
      Rojo.write(90);
       Verde.write(90);
       Azul.write(90);
    
    
    case 0:
    break;
  }
  delay(10);
}

  





