
 
#include "Arduino.h"
#include "BarreraTB6612.h"
 

void motores::Motoriz(int value)
{
  pinMode(BIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(PWMB,OUTPUT);
  if ( value >= 0 )
  {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else
  {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    value ;
  }
  analogWrite(PWMB, value);
}
 
void motores::Motorde(int value)
{
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
if ( value >= 0 )
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
  else
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    value *= -1;
  }
  analogWrite(PWMA, value);

}
void motores::Motor(int left, int righ)
{

  Motoriz(left);
  Motorde(righ);

}

void motores::freno(boolean left, boolean righ, int value)
{
 
  if ( left )
  {

//    digitalWrite(BIN1, LOW);
//    digitalWrite(BIN2, HIGH);

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, HIGH);
    analogWrite (PWMB, value);
  }
  if ( righ )
  {

//    digitalWrite(AIN1, LOW);
//    digitalWrite(AIN2, HIGH);
    
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
    analogWrite (PWMA, value);
  }
}
