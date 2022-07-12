/*
  IngenieroMakerMax.cpp 
*/
 
#include "Arduino.h"
#include "IngenieroMakerMax.h"
 

void motores::Motoriz(int value)
{
  pinMode(DA,OUTPUT);
  pinMode(PWMA,OUTPUT);
  if ( value >= 0 )
  {
    digitalWrite(DB, LOW);
    analogWrite(PWMA,value);
  }
  else
  {
    digitalWrite(DA, HIGH); //con low retrocede
    value = value * (-1);
    analogWrite(PWMA, value);
  }
}
 
void motores::Motorde(int value)
{
  pinMode(DB,OUTPUT);
  pinMode(PWMB,OUTPUT);
if ( value >= 0 )
  {
    digitalWrite(DB, LOW);
    analogWrite(PWMB,value);
  }
  else
  {
    digitalWrite(DB, HIGH);
    value = value * (-1);
    analogWrite(PWMB, value);
  }
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

   digitalWrite(DA, HIGH);
   analogWrite (PWMA, value);
  }
  if ( righ )
  {

   digitalWrite(DB, LOW);
   analogWrite (PWMB, value);
  }
}
