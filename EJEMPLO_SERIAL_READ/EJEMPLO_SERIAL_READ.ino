
#include <Servo.h>
int temp=0;

int ventilador1 = A0;




void setup() {
  
Serial.begin(9600);

 pinMode(ventilador1,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available()== 0);
int val = Serial.read();
if (val=='0')
{
 Serial.println("cuevo mik");

 digitalWrite(ventilador1,HIGH);
 delay(1000);
 
}
if (val=='1'){
   digitalWrite(ventilador1,LOW);
 delay(1000);
   Serial.println("esta apagado");
  }
  if(val=='T')
  {
 
  }
}
  





