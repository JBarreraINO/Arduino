/*Leer Boton

Ejemplo 1 

Desarrollado por Skybots y tdrobotica

Objetivo:
* En consola serial debe aparecer el estado del boton ON-OFF
*/

//Libreria Skybots
#include <sky.h>
sky Robot;//Declaracion de el robot


void setup() {
  //Carga la configuraciones de I/O Linebot, Wizard, Skydragon, etc...
  Robot.SkyDragon();
  //Configuracion de la consola serial
  Serial.begin(9600);
}

 void loop()
{
    /*|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|
    Boton es una variable real con un rango 1 a 0
    y repesenta la accion del pulsador ON - OFF
    |#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|*/
  if(Robot.Boton())
    Serial.println("ON");
  else
    Serial.println("OFF");    
}

/*
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