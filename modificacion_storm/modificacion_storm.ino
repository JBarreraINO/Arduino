#define RightMotorDir  9
#define RightMotorPwmPin 5
#define LeftMotorDir 6
#define LeftMotorPwmPin 3
#define Led1 13



#define Start 4


const int  s0= 14;
const int  s1= 15;
const int  s2= 16;
const int  s3= 17;
#define Sens A4
                            


int a = 0;
int Threshold = 600;
int LimitMin = -40;
int LimitMax = 30;
int Error;
int LastError = 0;
int TotalError;
int Correction;
int BaseSpeed; 
int ExtraNos; 
int NoNos;
int NosTime;

float Kp;
float Ki;
float Kd;

int RightMotorPwm = 0;
int LeftMotorPwm = 0;
int zemin=1;
void setup() {
  

pinMode(Start, INPUT);



pinMode(Led1, OUTPUT);

pinMode(s0, OUTPUT);
pinMode(s1, OUTPUT);
pinMode(s2, OUTPUT);
pinMode(s3, OUTPUT);
digitalWrite(s0, LOW);
digitalWrite(s1, LOW);
digitalWrite(s2, LOW);
digitalWrite(s3, LOW);
   
      delay(2000);
int SpeedPlus=1;
BaseSpeed=(20+(SpeedPlus/8)); // Min 20 - Max 148
ExtraNos = BaseSpeed+5;
NoNos = BaseSpeed;

      pinMode(Sens,INPUT);
      pinMode(RightMotorDir, OUTPUT);
      pinMode(RightMotorPwmPin, OUTPUT);
      pinMode(LeftMotorDir, OUTPUT);
      pinMode(LeftMotorPwmPin, OUTPUT);
      
Serial.begin(9600);
}
int ReadSensor(){

  for (int i=1; i <= 16; i++){
  if (i == 6)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
   a=190;
        }
    }
    else if (i == 2)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
   a=150;
        }
    }
    else if (i == 3)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
      if(analogRead(Sens)<Threshold){
      a=70;
    }

    }
    else if (i == 4)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
   a=50;
        }
    }
    else if (i == 5)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
    a=20; 
        }
    }
    else if (i == 1)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
    a=0;
     digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
      if(analogRead(Sens)<500){
      BaseSpeed=ExtraNos;
      digitalWrite(Led1, HIGH);
      delay(NosTime);
      
      
    } else {BaseSpeed=NoNos;}
     
    }}
    else if (i == 7)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
      if(analogRead(Sens)<Threshold){
      a=-20; 
    }
 
    }
    else if (i == 8)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
       a=-40;
    }
    }
    else if (i == 9)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
      if(analogRead(Sens)<Threshold){
      a=-70;
    }
    
    }
    else if (i == 10)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
   a=-150;
        }
    }
    else if (i == 11)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
        a=-190;
        }
    }
    else if (i == 12)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
    a=-250; 
        }
    }
    else if (i == 13)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
     a=-400;
        }
    }
    else if (i == 14)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
      if(analogRead(Sens)<Threshold){
      //a=2;
    }}
    else  if (i == 15)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
           a=400;
        }}
            else  if (i == 16)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
           a=250;
        }
    }
  

}}

void MotorControl(int LeftMotorPwm, int RightMotorPwm){

  if(LeftMotorPwm<=0) {
       LeftMotorPwm=abs(LeftMotorPwm);
      digitalWrite(LeftMotorDir, LOW);
      analogWrite(LeftMotorPwmPin, LeftMotorPwm);
    }
  else {
      digitalWrite(LeftMotorDir, HIGH);
      analogWrite(LeftMotorPwmPin, LeftMotorPwm);
}
       
    
  if(RightMotorPwm <= 0) {
     RightMotorPwm=abs(RightMotorPwm);
      digitalWrite(RightMotorDir, HIGH);
      analogWrite(RightMotorPwmPin, RightMotorPwm);
    }
  else {
      digitalWrite(RightMotorDir, LOW);
      analogWrite(RightMotorPwmPin, RightMotorPwm);
      }
  } 



//************************************
void MotorControl2(int LeftMotorPwm, int RightMotorPwm){

  if(LeftMotorPwm<=(BaseSpeed-10)) {
      LeftMotorPwm=(BaseSpeed-LeftMotorPwm)*2;
      digitalWrite(LeftMotorDir, LOW);
      analogWrite(LeftMotorPwmPin, LeftMotorPwm);
    }
  else if (LeftMotorPwm>(BaseSpeed+10)){
    LeftMotorPwm=(LeftMotorPwm-BaseSpeed)*2;
      digitalWrite(LeftMotorDir, HIGH);
      analogWrite(LeftMotorPwmPin, LeftMotorPwm);
}
    else {analogWrite(LeftMotorPwmPin, 0);}
    
  if(RightMotorPwm<=(BaseSpeed-10)) {
      RightMotorPwm=(BaseSpeed-RightMotorPwm)*2;
      digitalWrite(RightMotorDir, LOW);
      analogWrite(RightMotorPwmPin, RightMotorPwm);
    }
  else if (RightMotorPwm>(BaseSpeed+10)){
    RightMotorPwm=(RightMotorPwm-BaseSpeed)*2;
      digitalWrite(RightMotorDir, HIGH);
      analogWrite(RightMotorPwmPin, RightMotorPwm);
      }
      else {analogWrite(RightMotorPwmPin, 0);}
  } 



void loop() {
  while(digitalRead(Start)==0) {MotorControl(0,0); digitalWrite(Led1, HIGH); } 
    digitalWrite(Led1, LOW); 

  BaseSpeed = NoNos;
  ReadSensor();

    Error = a;
    if (Error == 0 ) {TotalError=0;}
    TotalError = TotalError+Error;
    if (TotalError >= 15000 ) {TotalError=15000;}
    if (TotalError <= -15000 ) {TotalError=-15000;}
    
    Correction = Kp * Error + Ki*TotalError + Kd*(Error - LastError);
    LastError = Error;
 
    RightMotorPwm = BaseSpeed + Correction  ;
    LeftMotorPwm = BaseSpeed - Correction  ;
    
    RightMotorPwm = constrain(RightMotorPwm, LimitMin, LimitMax); 
    LeftMotorPwm = constrain(LeftMotorPwm, LimitMin, LimitMax); 
    MotorControl(LeftMotorPwm, RightMotorPwm);
   // MotorControl2(LeftMotorPwm, RightMotorPwm);

    //Kp 0,55 Kd 60 
   /* if (digitalRead(DipSwitch1)==1) {Kp=0.30;} else */{Kp=0.35;}
      /* if (digitalRead(DipSwitch2)==1) {NosTime=1;} else*/ {NosTime=5;}
      /* if (digitalRead(DipSwitch3)==1) {Kd=50.00;} else*/ {Kd=60.00;}

    Serial.print("Kp-Ki-Kd ");
    Serial.print(Kp);
    Serial.print("  ") ;
    Serial.print(Ki);
    Serial.print("  ") ;
    Serial.print(Kd);
    Serial.print("  ") ;

    Serial.print("BaseSpeed = ");
    Serial.print(BaseSpeed);
    Serial.print('\t') ; 
    
    Serial.print("Error = ");
    Serial.print(Error);
    Serial.print('\t') ; 
    //Serial.print("TotalError = ");
    //Serial.print(TotalError);
    //Serial.print('\t') ;
    Serial.print("Correction = ");
    Serial.print(Correction);
    Serial.print('\t') ; 
    Serial.print("LeftSpeed = ");
    Serial.print(LeftMotorPwm);
    Serial.print('\t') ; 
    Serial.print("RightSpeed = ");
    Serial.println(RightMotorPwm);
    delay(10);
 /*   
*/

}
