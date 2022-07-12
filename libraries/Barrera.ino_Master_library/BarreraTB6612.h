
#ifndef BarreraTB6612_h
#define BarreraTB6612_h
#include "Arduino.h"
 
class motores
{
  public:
#define AIN1  3
#define AIN2  4
#define PWMB  5
#define PWMA  6
#define BIN1  8
#define BIN2  7
#define STBY  13
   void Motoriz(int value);
   void Motorde(int value);
   void Motor(int left, int righ);
   void freno(boolean left, boolean righ, int value);
  private:
}; 
#endif