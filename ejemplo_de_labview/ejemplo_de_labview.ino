byte PIN_SENSOR = A2;
int dato_serial =0; // para los datos de entrada serie
float C;
int temp;
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position



void setup() {
Serial.begin(9600);
myservo.attach(9);
}
 
void loop() {
  

if (Serial.available() > 0) {  // si ha llegado un dato serial
lectura_dato(); // realiza una operacion
comparacion_dato();          // llama a la funcion de comparar el dato
}

}
void lectura_dato (void){
// lee el byte de entrada:
dato_serial = Serial.read();
}
 
void comparacion_dato (void){
if (dato_serial=='T') { // si el dato serial es la T envía la temperatura a java
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(8);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(8);                       // waits 15ms for the servo to reach the position
  }




}}
