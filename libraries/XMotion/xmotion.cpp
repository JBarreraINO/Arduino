#include "Arduino.h"
#include "xmotion.h"

#define RM_DIR 13
#define RM_PWM 11
#define LM_DIR 12
#define LM_PWM 3
#define TP A3 //Trimpot
#define VI A0 //Trimpot
#define UL1 8 //User Led1
#define UL2 9 //User Led2


String XMotionReadString; 




XMotionClass::XMotionClass(){
	pinMode(RM_DIR, OUTPUT);
	pinMode(RM_PWM, OUTPUT);
	pinMode(LM_DIR, OUTPUT);
	pinMode(LM_PWM, OUTPUT);
	pinMode(UL1, OUTPUT);
	pinMode(UL2, OUTPUT);
	pinMode(TP,INPUT);
        pinMode(VI,INPUT);
}

void XMotionClass::SETUP(){

}

void XMotionClass::UserLed1(int Time){
	digitalWrite(UL1,HIGH);
	delay(Time);
	digitalWrite(UL1,LOW);
	delay(Time);
}

void XMotionClass::UserLed2(int Time){
	digitalWrite(UL2,HIGH);
	delay(Time);
	digitalWrite(UL2,LOW);
	delay(Time);		
}

void XMotionClass::Forward(byte speed, int Time){
   
   speed = constrain(speed,0,100);
   speed = map(speed,0,100,0,255);
   digitalWrite(RM_DIR,HIGH);
   digitalWrite(LM_DIR,HIGH);
   analogWrite(RM_PWM, speed);
   analogWrite(LM_PWM, speed);
   delay(Time);
   
}
 
void XMotionClass::Backward(byte speed, int Time){
   
   speed = constrain(speed,0,100);
   speed = map(speed,0,100,0,255);
   digitalWrite(RM_DIR,LOW);
   digitalWrite(LM_DIR,LOW);
   analogWrite(LM_PWM, speed);
   analogWrite(RM_PWM, speed);
   delay(Time);
   
}

void XMotionClass::Right0(byte speed, int Time){
   
   speed = constrain(speed,0,100);
   speed = map(speed,0,100,0,255);
   digitalWrite(RM_DIR,LOW);
   digitalWrite(LM_DIR,HIGH);
   analogWrite(RM_PWM, speed);
   analogWrite(LM_PWM, speed);
   delay(Time);
   
}

void XMotionClass::Left0(byte speed, int Time){
   
   speed = constrain(speed,0,100);
   speed = map(speed,0,100,0,255);
   digitalWrite(RM_DIR,HIGH);
   digitalWrite(LM_DIR,LOW);
   analogWrite(RM_PWM, speed);
   analogWrite(LM_PWM, speed);
   delay(Time);
   
}

void XMotionClass::ArcTurn(byte LeftSpeed, byte RightSpeed, int Time){
	
	LeftSpeed = constrain(LeftSpeed,0,100);
	LeftSpeed = map(LeftSpeed,0,100,0,255);
	RightSpeed = constrain(RightSpeed,0,100);
	RightSpeed = map(RightSpeed,0,100,0,255);
	digitalWrite(RM_DIR,HIGH);
    digitalWrite(LM_DIR,HIGH);
    analogWrite(RM_PWM, RightSpeed);
    analogWrite(LM_PWM, LeftSpeed);
    delay(Time);
	
}

void XMotionClass::MotorControl(int RightMotorPwm, int LeftMotorPwm) {

  if (RightMotorPwm <= 0) {
    RightMotorPwm = abs(RightMotorPwm);
    digitalWrite(RM_DIR, LOW);
    analogWrite(RM_PWM, RightMotorPwm);
  }
  else {
    digitalWrite(RM_DIR, HIGH);
    analogWrite(RM_PWM, RightMotorPwm);
  }
  if (LeftMotorPwm <= 0) {
    LeftMotorPwm = abs(LeftMotorPwm);
    digitalWrite(LM_DIR, LOW);
    analogWrite(LM_PWM, LeftMotorPwm);
  }
  else {
    digitalWrite(LM_DIR, HIGH);
    analogWrite(LM_PWM, LeftMotorPwm);
  }
}


void XMotionClass::StopMotors(int Time){
   analogWrite(RM_PWM, 0);
   analogWrite(LM_PWM, 0);
   delay(Time);
   
}

int XMotionClass::Trimpot(){
	return analogRead(TP);
}

float XMotionClass::VoltageIn(){
   int Total=0;
  for (int x = 0; x <10; x=x+1){
  int sensorValue = analogRead(A0);
  Total=Total+sensorValue; 
  delay(1);
  }
   return  Total * 0.8021* (5.0 / 1023.0);
}

void XMotionClass::ToggleLeds(int Time){	
	digitalWrite(UL1,HIGH);
	digitalWrite(UL2,LOW);
	delay(Time);
	digitalWrite(UL2,HIGH);
	digitalWrite(UL1,LOW);
	delay(Time);
	digitalWrite(UL1,LOW);
	digitalWrite(UL2,LOW);	
}

void XMotionClass::LipoCutOff(int Cell){
      Serial.begin(9600);
      delay(300);
    float CellVoltage = xmotion.VoltageIn() / Cell; 
     if (CellVoltage < 3.6) {
    while (1) {
   xmotion.ToggleLeds(80);
   }
       Serial.print("Low Battery");
       Serial.print(CellVoltage);
     } else {
      Serial.print("OK");
     }
}

void XMotionClass::CounterLeds(int Time, int countx){
for (int i=0; i < countx; i++){ // 
  xmotion.ToggleLeds(Time/2); // 
 }
}

XMotionClass xmotion = XMotionClass();