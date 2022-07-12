/*Test Sensores

Ejemplo 3 

Desarrollado por Skybots y tdrobotica

Objetivo:
*Conocer el estado de los sensores por medio de la
consola serial.
*/
//Libreria Skybots
#include <sky.h>
//Declaracion del Objeto Robot
sky Robot;

void setup(){
  //Consola serial
  Serial.begin(9600);
  //Carga la configuraciones de I/O Linebot, Wizard, Skydragon, etc...
  Robot.Linebot();
  //Configuracion(#sensores,1,2,3,4,5,6,7,8,LEDon)
  Robot.LineConfig(8, 18, 19, 15, 16, 9, 8, 7, 4, 14);
  Robot.Speeds(0,0);
}

 void loop(){
    //Carga el valor de la posicion digital
    float pos= Robot.LinePosDigital();
    Serial.println(pos);
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