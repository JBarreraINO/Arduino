/*Leer Boton

Ejemplo 1 

Desarrollado por Barrera.ino

Objetivo:
* En consola serial debe aparecer el estado del boton ON-OFF ademas el boton que se ha presionado
*/

//Libreria 
#include <Barreraino.h>
barrera Robot;//Declaracion del objeto

#define pinLED 2
#define pinLED2 13
int count = 0;
int count2 = 0;

void setup() {
    //Carga la configuraciones de las entradas o salidas
 Robot.unoBarrera();
  //Configuracion de la consola serial
  Serial.begin(9600);
  //declaracion de salidas
  pinMode(pinLED, OUTPUT);
  pinMode(pinLED2, OUTPUT);
    pinMode(11,INPUT );
}

void loop() {
  count++;
  count2++;
  delay(10);
int lectura = digitalRead(10);
Serial.println(count);
  

 
 
if(count == 100){

ledAzul();}

  
}


void ledAzul(){
  int estadoLED = digitalRead(pinLED);
  digitalWrite(pinLED, !estadoLED);
  count = 0;
}

void ledRojo(){
  int estadoLED = digitalRead(pinLED2);
  digitalWrite(pinLED2, !estadoLED);
  count2 = 0;
}
