#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
 #include <Barreraino.h>
SoftwareSerial BT(0,1);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
barrera Alarma;
int estado = 0;
void setup()
{ pinMode(12,OUTPUT);
pinMode(5,OUTPUT);
  BT.begin(9600);       // Inicializamos el puerto serie BT que hemos creado
  Serial.begin(9600);  
   Alarma.unoBarrera();// Inicializamos  el puerto serie  
}
 
void loop()
{
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
   // Serial.write(BT.read());
     estado = Serial.read();
  }
   if(Alarma.Boton1()){
    //ACTIVAR ALARMA BOTON
      digitalWrite(12, HIGH);
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
    digitalWrite(5, HIGH);
    break;
    case 'd':
    digitalWrite(5, LOW);
    break;
  }
 
}
