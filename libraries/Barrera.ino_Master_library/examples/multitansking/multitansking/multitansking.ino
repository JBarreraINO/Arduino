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
#define pinBtn 13
#define pinLEDred A5
int count = 0;
int count2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
  pinMode(pinLEDred, OUTPUT);
  pinMode(pinBtn, INPUT_PULLUP);
}

void loop() {
  count++;
  count2++;
  delay(10);

  lecturaBtn();
  
  if(count == 100){
    ledAzul();
  }

  if(count2 == 50){
    ledRojo();
  }
}



void lecturaBtn(){
  int lectura = digitalRead(pinBtn);
  Serial.println(lectura);
}

void ledAzul(){
  int estadoLED = digitalRead(pinLED);
  digitalWrite(pinLED, !estadoLED);
  count = 0;
}

void ledRojo(){
  int estadoLED = digitalRead(pinLEDred);
  digitalWrite(pinLEDred, !estadoLED);
  count2 = 0;
}
