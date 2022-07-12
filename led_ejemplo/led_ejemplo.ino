#include <Servo.h>



int LED = 13;
int pul=12;
Servo emp1;
void setup(){
  emp1.attach(4);
  pinMode(LED,OUTPUT);
  pinMode(pul,OUTPUT);
  Serial.begin(9600);
}

void loop(){
   // pin 0: sensor de proximidad 
   int sensorValue = analogRead(A0);
   
digitalWrite(LED,HIGH);
delay(500);
digitalWrite(LED,LOW);
delay(500);
Serial.println(pul);
}
