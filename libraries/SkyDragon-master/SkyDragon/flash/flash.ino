/*LED Flash

Ejemplo 2 

Desarrollado por Skybots y tdrobotica

Objetivo:
* El LED se enciende y se apaga infinitamente
*/
//El LED esta conectado al pin D11
int led = 11;
void setup() {
  //Declara el LED como salida                
  pinMode(led, OUTPUT);     
}
void loop() {
  //Enciende el LED por 50ms
  digitalWrite(led, HIGH);
  delay(50);
  //Apaga el LED por 500ms
  digitalWrite(led, LOW);
  delay(500);
}
/*
SkyDragon es una tarjeta electronica diseñada para robotica general
contiene las siguientes conexiones:
  *Entradas
    -Boton D4
    -Sensor Bateria A11
    - 9 pines digitales (A5,A4,A3,A2,A1,A0,D13,D10,D9), 6 pueden ser Analogos, 3 de PWM
  *Salidas
    -Motor MA(D6-D8)
    -Motor MB(D5-D7)
    -LED D11
  *Comunicacion
    -1 Serial Rx D0, Tx D1
    -1 I2C SDA D2, SCL D3
*/