/*
  IngenieroMakerTB6612.h
*/
#ifndef IngenieroMakerMax_h
#define IngenieroMakerMax_h
#include "Arduino.h"
 
class motores
{
  public:
#define DB  9
#define PWMB  5
#define DA  6
#define PWMA  3

   void Motoriz(int value);
   void Motorde(int value);
   void Motor(int left, int righ);
   void freno(boolean left, boolean righ, int value);
  private:
}; 
#endif