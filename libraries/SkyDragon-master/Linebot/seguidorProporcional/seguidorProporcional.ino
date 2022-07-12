/*Seguidor de linea con velocidad proporcional

Ejemplo 5

Desarrollado por Skybots y tdrobotica

Objetivo:
*Hacer que el robot siga una linea usando logica digital
 escalando la entrada con respecto a la salida, con este
 control el robot es capaz de seguir la linea de forma
 proporcional.
*/
//Libreria Skybots
#include <sky.h>
//Declaracion del Objeto Robot
sky Robot;

void setup(){
  //Carga la configuraciones de I/O Linebot, Wizard, Skydragon, etc...
  Robot.Linebot();
  //Configuracion(#sen,1,2,3,4,5,6,7,8,LEDon)
  Robot.LineConfig(8, 18, 19, 15, 16, 9, 8, 7, 4, 14);
  //Espera que se presione el boton de inicio y espera
  while(Robot.Boton()){}
  //Retardo de incio
  delay(2000);
  //Impulso inicial
  Robot.Speeds(100,-100);
  delay(10000);
}

 void loop(){
    //Carga el valor de la posicion digital 1 - 9
    float pos= Robot.LinePosDigital();
    /*|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|
    Velocidad de los motores proporcional a la posicion
    |#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|*/
    int VMA= map(pos,8,1,-35,115);
    int VMB= map(pos,1,8,-35,115);
    //Carga velocidad a cada motor
    Robot.Speeds(VMA,-VMB);
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