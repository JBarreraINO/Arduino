/*Test Motores

Ejemplo 3 

Desarrollado por Skybots y tdrobotica

Objetivo:
*Se moveran los motores MA y MB cada vez que se presione el boton
*/

//Libreria Skybots
#include <sky.h>
sky Robot;//Declaracion de el robot

void setup(){
  //Carga la configuraciones de I/O Linebot, Wizard, Skydragon, etc...
  Robot.SkyDragon();
}

 void loop()
{
  if(Robot.Boton())
    Robot.Speeds(0,0);
  else
    Robot.Speeds(100,-100); 
    /*|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|
    Speed recibe valores enteros en un rango de -255 a 255
    si el valor de entrada es positivo el motor va en sentido horario
    |#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|*/   
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