/*
IngenieroMakerSeguidor16s.h
*/
#ifndef barra16_h
#define barra16_h
#include "Arduino.h"
 
class barra16
{
  public:
const int LedsIr = 11;    //Pin para encender los leds ir
const int S0 = 14;        //Pin A0 de modo digital 
const int S1 = 15;        //Pin A1 de modo digital
const int S2 = 16;        //Pin A2 de modo digital
const int S3 = 17;        //Pin A3 de modo digital
const int ANALOG_IN = A4;
//Variables de los sensores.
int sensorValores[16];
int Valor_Digital[16];
int sensorValores_B[16];
int sensorValores_N[16];
int sensorValores_R[16];

//VARIABLES POSICION PONDERADA
int x;
int y;
int p;
//Variables de calibracion
int Muestras[16]={590, 686, 600, 600, 617,585, 631, 566, 592, 563, 617, 627, 634, 697, 616, 650};
   void leer_blanco();
   void leer_negro();
   void valor();
   void Calcula_muestras();
   void Leer_Sensores_ir(boolean L);
   int proporcional();
  private:
}; 
#endif