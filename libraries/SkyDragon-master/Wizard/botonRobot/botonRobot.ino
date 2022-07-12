/*Leer entrada Digital

Ejemplo 3

Conexiones Necesarias:
*Wizard
  -Boton D14
*Bateria 74.V
*Cable MicroUSB

Objetivo:
*Al presionar el boton 14 debe imprimirse en la consola serial el estado, con esto usamos una entrada digital de la tarjeta.
*/

#include <sky.h>
sky Robot;//Declaracion de los motores MA y MB


void setup() {
  Robot.Wizard();
  Serial.begin(9600);
}

//Establecemos la rutina.
 void loop()
{
  if(Robot.Boton())
    Serial.println("ON");
  else
    Serial.println("OFF");    
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