/*Leer entrada Analogica - Voltaje del Robot 

Ejemplo 4

Conexiones Necesarias:
*Wizard
  -Pin A1
*Bateria 74.V
*Cable MicroUSB

Objetivo:
*La consola serial muestra el voltaje actual del robot.
*/

void setup() {
   // Iniciamos la comunicacion serial
  Serial.begin(9600);
}

//Establecemos la rutina.
void loop() {
  // Leemos el pin analogico 1
  int valorSensor = analogRead(A1);//  // Convierte el valor analogico (0 - 1023)  a voltaje (0V - 5V)
  //y lo multimplica por 2 ya que son dos baterias en serie.
  float voltaje = 2*valorSensor * (5.0 / 1023.0);
   //Imprimimos en la consola el valor de voltaje
  Serial.println(voltaje);
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
