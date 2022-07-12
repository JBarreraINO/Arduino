#include <Wire.h>                   // Incluimos la libreria i2c
unsigned char lectura=0;            // Establecemos una variable global, y la seteamos en cero

void setup()
{
  Wire.begin(1);                    // Nos asignamos el numero 1 como esclavos (de ser maestro va vacio esto)
  Serial.begin(9600);               // Iniciamos el serial 9600 baudios, para testear
  Wire.onRequest(respuestaEvento);  // Al activarse el evento de peticion, se ejecuta la funcion respuestaEvento
  Wire.onReceive(recibidoEvento);   // Al activarse el evento de lectura, se ejecuta la funcion recibidoEvento  
}

void loop()
{
  lectura = analogRead(A0)/4;     // La variable global es igual a la lectura analogica del pin A0 dividido en 4 para que entre en un byte (0 a 255)
  delay(100);                     // Damos un respiro 
}

void respuestaEvento()            // Evento de peticion se activa cuando un master nos pide que le enviemos algun dato
{
  Wire.write(lectura);            // Enviamos el resultado de la lectura al maestro que lo solicito
  Serial.println(lectura);        // Enviamos el resultado por el puerto serie para testear
}

void recibidoEvento(int howMany)  // Evento de recpcion
{
  unsigned char pedido;
  while( Wire.available())        // Leemos hasta que no haya datos, osea el 1 que va a enviar el maestro
  {
    pedido = Wire.read();         // Leemos el 1
    Serial.println(pedido);       // Imprimimos el 1 por serial para testear   
  }
}

