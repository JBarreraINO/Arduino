/*activar y desactivar rele
Ejemplo 1 
Desarrollado por Barrera.ino

Objetivo:
*activar y desactivar cargas mayores a las que puede 
controlar el microcontrolador de arduino.
ej:encender un bombillo de 110v 
*/
//Libreria 
#include <Barreraino.h>
barrera Robot;//Declaracion del objeto


void setup() {
  //Carga la configuraciones de las entradas o salidas
 Robot.unoBarrera();
  //Configuracion de la consola serial
  Serial.begin(9600);
}

void loop()
{
Robot.activarele();
delay(1000);
Robot.desactivarele();
 delay(1000);
}