#include <Arduino.h>
#line 1 "C:\\Users\\Juan Carlos Barragan\\AppData\\Local\\Temp\\Rar$DIa0.564\\LED_CONTROL_BLUE\\LED_CONTROL_BLUE.ino"
int led1 = 2;
int led2 = 13;
unsigned long previousTimeLed1 = millis();
long timeIntervalLed1 = 1000;
int ledState1 = LOW;

unsigned long previousTimeSerialPrintPotentiometer = millis();
long timeIntervalSerialPrint = 2000;

int estado = 0;

#line 12 "C:\\Users\\Juan Carlos Barragan\\AppData\\Local\\Temp\\Rar$DIa0.564\\LED_CONTROL_BLUE\\LED_CONTROL_BLUE.ino"
void setup();
#line 19 "C:\\Users\\Juan Carlos Barragan\\AppData\\Local\\Temp\\Rar$DIa0.564\\LED_CONTROL_BLUE\\LED_CONTROL_BLUE.ino"
void loop();
#line 12 "C:\\Users\\Juan Carlos Barragan\\AppData\\Local\\Temp\\Rar$DIa0.564\\LED_CONTROL_BLUE\\LED_CONTROL_BLUE.ino"
void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop()
{
 unsigned long currentTime = millis();

 

  
  if( Serial.available()>0)
  {
    estado = Serial.read();
  }
  switch( estado)
  {
    case 'a':
  
    digitalWrite(led1, HIGH);
    Serial.println("prendido");
    
    break;
    case 'b':
    digitalWrite(led1, LOW);
     Serial.println("apagado");
    break;
    
    case 'c':
    digitalWrite(led2, HIGH);
      if (currentTime - previousTimeSerialPrintPotentiometer > timeIntervalSerialPrint) {
    previousTimeSerialPrintPotentiometer = currentTime;
    while (estado=='c'){Serial.print("Value : ");}}
    break;
    case 'd':
    digitalWrite(led2, LOW);
    break;
  }
}

