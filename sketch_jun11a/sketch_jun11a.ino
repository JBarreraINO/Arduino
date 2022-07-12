/*Leer Boton

Ejemplo 1 

Desarrollado por Barrera.ino

Objetivo:
* En consola serial debe aparecer el estado del boton ON-OFF ademas el boton que se ha presionado
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
  Serial.println("");  
    /*|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|
    Boton es una variable real con un rango 1 a 0
    y repesenta la accion del pulsador ON - OFF
    |#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|#|*/
  if(Robot.Boton1()){
Serial.print("ON:  ");
Serial.print("presionaste el boton 1 ");}
else
Serial.print("   boton 1 OFF");  
if(Robot.Boton2()){
Serial.print("ON:  ");
Serial.print("presionaste el boton 2 ");}  

else
Serial.print("   botont 2 OFF");  
}

