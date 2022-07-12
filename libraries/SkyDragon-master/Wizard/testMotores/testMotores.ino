/*Mover Motores

Ejemplo 2

Conexiones Necesarias:
*Wizar/*Mover Motores

Ejemplo 2

Conexiones Necesarias:
*Wizard
  -Motores MA Y MB
  -Boton D14
*Bateria 74.V
*Cable MicroUSB

Objetivo:
*Se moveran los motores MA y MB y luego se apagaran cada segundo
*/

#include <sky.h>
sky Robot;//Declaracion de los motores MA y MB

void setup(){
  Robot.Wizard();
}

 void loop()
{
  if(Robot.Boton())
    Robot.Speeds(0,0);
  else
    Robot.Speeds(100,-100);    
}

/*
Wizard es una tarjeta electronica diseñada para robotica general
contiene las siguientes conexiones:
	*Entradas
		-Boton D14
		-Sensor Bateria A1
		- 7 pines digitales (A11,D16,A0,A9,A6,D7,A8), los A puenden ser analogos
		-Receptor D1 TX
	*Salidas
		-Motor MA(D5-D6)
		-Motor MB(D10-D11)
		-Parlante D0 RX
*/