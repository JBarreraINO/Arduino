/*Leer entrada Analogica - Voltaje del Robot 

Ejemplo 4

Objetivo:
*La consola serial muestra el voltaje actual del robot.
*/
//Libreria Skybots
#include <sky.h>
sky Robot;//Declaracion de el robot

void setup() {
  Robot.SkyDragon();
   // Iniciamos la comunicacion serial
  Serial.begin(9600);
}

//Establecemos la rutina.
void loop() {
   float voltaje= Robot.Battery();
  Serial.println(voltaje);
}
/*
SkyDragon es una tarjeta electronica diseñada para robotica general
contiene las siguientes conexiones:
  *Entradas
    -Boton D4
    -Sensor Bateria A11
    - 9 pines digitales (A5,A4,A3,A2,A1,A0,D13,D10,D9), 6 pueden ser Analogos, 3 de PWM
  *Salidas
    -Motor MA(D6-D8)
    -Motor MB(D5-D7)
    -LED D11
  *Comunicacion
    -1 Serial Rx D0, Tx D1
    -1 I2C SDA D2, SCL D3
*/