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
  Robot.Linebot();
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
Linebot es un robot Seguidor de lineas educativo.
contiene las siguientes conexiones:
	*Entradas
		-1 Boton D12
		-8 sensores de linea Digitales D4, D7, D8, D16, D15, D19,D18
		-1 Led-On habilitador de los sensores D14
	*Salidas
		-1 Motor MA(D5-D6)
		-1 Motor MB(D10-D11)
		-1 LED D13
	*Comunicacion
		-1 Serial Rx D0, Tx D1
		-1 I2C SDA D2, SCL D3
*/