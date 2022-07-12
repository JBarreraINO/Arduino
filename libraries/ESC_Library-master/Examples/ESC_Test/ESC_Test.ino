/*
 * Libreria desarrolada por Michael Vargas
 * Ejemplo sencillo para el control de turbina 11000Kv EDF27
 * ESC_Test.ino
 * 
 * 07/01/2017
 */
#include <ESC.h>

#define PIN_ESC 9

ESC EDF27(PIN_ESC);
                               //Min - Max
//Change Speed in microseconds: 1000 - 2000

void setup() {
  EDF27.init();//Inicialia el timer1
  delay(150); //Pequeño tiempo de espera
}

void loop() {
  EDF27.setSpeed(2000);//Enciende el motor al maximo
  delay(2000);
  EDF27.setSpeed(1500);//Apaga el motor
  delay(2000);
}
