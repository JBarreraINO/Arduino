#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(0,1);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
 
int estado = 0;
void setup()
{ pinMode(12,OUTPUT);
pinMode(11,OUTPUT);
  BT.begin(9600);       // Inicializamos el puerto serie BT que hemos creado
  Serial.begin(9600);   // Inicializamos  el puerto serie  
}
 
void loop()
{
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
   // Serial.write(BT.read());
     estado = Serial.read();
  }
    switch( estado)
  {
    case 'a':
    digitalWrite(12, HIGH);
    break;
    case 'b':
    digitalWrite(12, LOW);
    break;
    
    case 'c':
    digitalWrite(11, HIGH);
    break;
    case 'd':
    digitalWrite(11, LOW);
    break;
  }
 
}
