/*
   === Arduino Mecanum Wheels Robot ===
     Radio control with NRF24L01 
  by Dejan, www.HowToMechatronics.com
  Libraries:
  RF24, https://github.com/tmrh20/RF24/
  AccelStepper by Mike McCauley: http://www.airspayce.com/mikem/arduino/AccelStepper/index.html

*/



#include <AccelStepper.h>
int PWM_PIN1 = 44; //Define Digital PIN
int PWM_PIN2 = 52; //Define Digital PIN
int PWM_PIN3 = 45; //Define Digital PIN
  int sV1;    //These are all different speed values that will be mapped
  int sV2;
  int sV3;
  int sV4;
  int sV5;
  int sV6;
  int neutralh = 1500;//PUT YOUR HIGH NEUTRAL VALUE HERE. REPLACE 1500  =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
int neutrall = 1430;//PUT YOUR LOW NEUTRAL VALUE HERE. REPLACE 1420  =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
int maxval = 1996; //PUT YOUR MAX VALUE HERE   REPLACE 1870           =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~==~=~==~=~==~=~==~=~==~=~==~=~=
int minval = 980; 
#define STEPPER1_DIR_PIN 6
#define STEPPER1_STEP_PIN 3
// The Y stepper pins
#define STEPPER2_DIR_PIN 50
#define STEPPER2_STEP_PIN 2

#define STEPPER3_DIR_PIN 22
#define STEPPER3_STEP_PIN 4
long unsigned int pos = 0;

#define STEPPER4_DIR_PIN 26
#define STEPPER4_STEP_PIN 24


// Define the stepper motors and the pins the will use
AccelStepper LeftBackWheel(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper LeftFrontWheel(AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);  // Stepper2
AccelStepper RightBackWheel(AccelStepper::DRIVER, STEPPER3_STEP_PIN, STEPPER3_DIR_PIN);  // Stepper3
AccelStepper RightFrontWheel(AccelStepper::DRIVER, STEPPER4_STEP_PIN, STEPPER4_DIR_PIN); // Stepper4

int wheelSpeed = 1500;
int led=13;
// Max size of this struct is 32 bytes - NRF24L01 buffer limit

//Create a variable with the above structure

void setup() {
 pinMode(PWM_PIN1, INPUT);
  pinMode(8, OUTPUT); 
  pinMode(PWM_PIN2, INPUT);
  pinMode(PWM_PIN3, INPUT);
  Serial.begin(115200);

  
 
  // Set initial seed values for the steppers
  LeftFrontWheel.setMaxSpeed(1000);
   
  LeftBackWheel.setMaxSpeed(1000);

  
  RightFrontWheel.setMaxSpeed(1000);



  
  RightBackWheel.setMaxSpeed(1000);

  
}

void loop() {
  // Check whether we keep receving data, or we have a connection between the two modules
 
   int pwm1 = pulseIn(PWM_PIN1, HIGH); //Read PWM Pulse
  int pwm2 = pulseIn(PWM_PIN2, HIGH); //Read PWM Pulse
  int pwm3 = pulseIn(PWM_PIN3, HIGH);
  digitalWrite(8,LOW);//Read PWM Pulse
  
  Serial.print("PWM CH1: ");
  Serial.print(pwm1);
  Serial.print(" PWM CH2: ");
  Serial.print(pwm2);
  Serial.print(" PWM CH3: ");
  Serial.println(pwm3);
  // Set speed - left potentiometer
  
  int valorVelocidad = pwm3;
  int valorDireccion =pwm2;
   if (valorVelocidad >= 1400 && valorVelocidad <= 1530) {stopMoving();}
   if (valorVelocidad > 1530 && valorDireccion >= 1420 && valorDireccion <= 1500) {sV1 = map(valorVelocidad, neutralh, maxval, 0, 255);   moveForward();}
   if (valorVelocidad < 1400 && valorDireccion >= 1420 && valorDireccion <= 1500) { sV2 = map(valorVelocidad, neutralh, maxval, 0, 255);  moveBackward();}
   if (valorDireccion > neutralh && valorVelocidad > neutralh)                    {sV3 = map(valorVelocidad, neutralh, maxval, 0, 255);   moveSidewaysRight();}
   if (valorDireccion < neutrall && valorVelocidad > neutralh)                    { sV4 = map(valorVelocidad, neutralh, maxval, 0, 255);  moveSidewaysLeft(); }
    if (valorDireccion > neutralh && valorVelocidad < neutrall)                    {sV5 = map(valorVelocidad, neutralh, minval, 140, 255); rotateLeft();}
if (valorDireccion < neutrall && valorVelocidad < neutrall)                         {sV6 = map(valorVelocidad, neutralh, minval, 140, 255); rotateRight();}

 
LeftFrontWheel.run();LeftBackWheel.run();RightFrontWheel.run();  RightBackWheel.run();
  // Monitor the battery voltage
  int sensorValue = analogRead(A8);
  float voltage = sensorValue * (5.0 / 1023.00) * 3; // Convert the reading values from 5v to suitable 12V i
  // If voltage is below 11V turn on the LED
  if (voltage < 11) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}

void moveForward() {

  LeftFrontWheel.setSpeed(sV1);
  LeftBackWheel.setSpeed(sV1);
  RightFrontWheel.setSpeed(sV1);
  RightBackWheel.setSpeed(sV1);
    
}
void moveBackward() {
  LeftFrontWheel.setSpeed(sV2);
  LeftBackWheel.setSpeed(sV2);
  RightFrontWheel.setSpeed(sV2);
  RightBackWheel.setSpeed(sV2);
}
void moveSidewaysRight() {
  LeftFrontWheel.setSpeed(sV3);//i o
                                //o o
  LeftBackWheel.setSpeed(-sV3); //o i
                                //o o
  
  RightFrontWheel.setSpeed(-sV3);//o o 
                                 //i o
  RightBackWheel.setSpeed(sV3);//o o 
                                //o i
}
void moveSidewaysLeft() {
  LeftFrontWheel.setSpeed(sV4);
  LeftBackWheel.setSpeed(-sV4);
  RightFrontWheel.setSpeed(sV4);
  RightBackWheel.setSpeed(-sV4);
}
void rotateLeft() {
  LeftFrontWheel.setSpeed(-sV5);
  LeftBackWheel.setSpeed(sV5);
  RightFrontWheel.setSpeed(-sV5);
  RightBackWheel.setSpeed(sV5);
}
void rotateRight() {
  LeftFrontWheel.setSpeed(sV6);
  LeftBackWheel.setSpeed(-sV6);
  RightFrontWheel.setSpeed(sV6);
  RightBackWheel.setSpeed(-sV6);
}
void moveRightForward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveRightBackward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftForward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftBackward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void stopMoving() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(0);
}
