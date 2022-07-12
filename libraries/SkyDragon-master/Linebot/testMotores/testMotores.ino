/*Test Motores

Ejemplo 2 

Desarrollado por Skybots y tdrobotica

Objetivo:
*Se moveran los motores MA y MB cada vez que se presione el boton
*/

//Libreria Skybots
#include <sky.h>
sky Robot;//Declaracion de el robot

void setup(){
  //Carga la configuraciones de I/O Linebot, Wizard, Skydragon, etc...
  Robot.Linebot();
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