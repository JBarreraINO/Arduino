byte PIN_SENSOR = A2;
int dato_serial =0; // para los datos de entrada serie
float C;
int temp;
#include <Servo.h>

Servo Rojo;
Servo Verde,Azul ;

int color=0;
int conteo=0;
int conteoazul=0;
int conteorojo;
int conteoverde;
 
void setup() {
Serial.begin(9600);
 Rojo.attach(4);
  Verde.attach(3);
  Azul.attach(2);// abre el puerto serie, establece la velocidad a 9600 bps
}
 
void loop() {
  
C = (5000.0 * analogRead(PIN_SENSOR) ) / (1023.0*10.0);
temp=C;
// envía datos solo cuando recibe datos:
if (Serial.available() > 0) {  // si ha llegado un dato serial
lectura_dato(); // realiza una operacion
comparacion_dato();          // llama a la funcion de comparar el dato
   int sensorValue = analogRead(A0);
     delay(2000);
if(sensorValue<590&&sensorValue>300)
  {
  
  delay(1);  
  color=1;
  conteoazul++;
  
  ;// waits 15ms for the servo to reach the position
  }
  else if(sensorValue<1200&&sensorValue>871)
  {
   delay(1);
   conteoverde++;
   
   color=2;
   
  }
   else if(sensorValue<870&&sensorValue>520)
  {
  delay(1);
  conteorojo++;
  
  color=3;}

  else if(sensorValue<30&&sensorValue>0)
  
  delay(1);
  color=4;}




  switch (color) {
    case 1:
    Azul.write(180);
    delay(500);
        Azul.write(90);
    break;
    case 2:
    Verde.write(180);
    delay(500);
        Verde.write(90);
    break;
    case 3:
    Rojo.write(180);
    delay(500);
    Rojo.write(90);
    break;
    case 4 :
      Rojo.write(90);
       Verde.write(90);
       Azul.write(90);
    
    
    case 0:
    break;
  }
  delay(10);
  
  
  // delay in between reads for stability
} 
 
void lectura_dato (void){
// lee el byte de entrada:
dato_serial = Serial.read();
}
 
void comparacion_dato (void){
if (dato_serial=='T') { // si el dato serial es la T envía la temperatura a java
Serial.write(temp);
}}

