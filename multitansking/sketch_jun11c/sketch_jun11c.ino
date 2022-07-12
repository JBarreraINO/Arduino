
#include <Servo.h>
Servo servo1;
Servo servo2;
int motorbanda=2;
int sensor1=A1; //camara
int sensor2=7; // accion servo1
int sensor3=10; // accion servo2
int pos=0;
char val;

void setup() {
  // put your setup code here, to run once:
pinMode(sensor1, INPUT);
pinMode(sensor2, INPUT);
pinMode(sensor3, INPUT);
pinMode(motorbanda, OUTPUT);

servo1.attach(A3);
servo2.attach(A2);

Serial.begin(9600);
}

void loop() {
 int buttonState = digitalRead(sensor1);
     Serial.print("sensor1: ");
    Serial.print(buttonState);
 int buttonState2 = digitalRead(sensor2);
  Serial.print("sensor2: ");
    Serial.print(buttonState2);
 int buttonState3 = digitalRead(sensor3);
  Serial.print("sensor3: ");
    Serial.println(buttonState3);
    
 if (buttonState == HIGH) {
  motorON();
  }
  
  }


  void motorON(){
  static long ultimo_cambio=0;
 long   hora;
  hora=millis();
  if(hora-ultimo_cambio>3000){
    ultimo_cambio=hora;
 // put your main code here, to run repeatedly:
digitalWrite(2,LOW);


}

  }
  
/*
void motorOFF(){
  static long ultimo_cambio=0;
 long   hora;
  hora=millis();
  if(hora-ultimo_cambio>6000){
    ultimo_cambio=hora;
 // put your main code here, to run repeatedly:

  digitalWrite(motorbanda,LOW);
 

}

}
void Servo2()
{
 static long ultimo_cambio=0;
 long   hora;
  hora=millis();
  if(hora-ultimo_cambio>3000){
    ultimo_cambio=hora;

while (digitalRead(7)==LOW){
 // if (val=='1'){
    for(pos =0; pos<=180; pos +=1){
       Serial.println("servo1 activado");
     servo2.write(pos);
     
    }
             for (pos =180; pos >=0; pos -=1){
         servo2.write(pos);  
     
      }                      
   
               //}
                           }
  }
 
}
  void servomotor1(){
 
  while (digitalRead(7)==LOW){
 // if (val=='1'){
    for(pos =0; pos<=180; pos +=1){
       Serial.println("servo1 activado");
     servo1.write(pos);
     delay(15);
    }
             for (pos =180; pos >=0; pos -=1){
         servo1.write(pos);  
     delay(15);
      }                      
   
               //}
                           }
}*/
