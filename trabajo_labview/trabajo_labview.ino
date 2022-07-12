int LED=13;
int var;
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
 Serial.begin(9600);
 pinMode(LED,OUTPUT);
 myservo.attach(9);
 
}

void loop() {

if(Serial.available())
{
 
  var=Serial.read();
  if(var=='a'){
  
   
      
digitalWrite(LED,HIGH);
delay(500);

  
  if(var=='b')
  {
digitalWrite(LED,LOW);
delay(500);
   
  }
  }
  else
  {
    digitalWrite(LED,LOW);
delay(500);myservo.write(10); }
 
}
}
