
// Modificado por: www.elprofegarcia.com
// Visualiza en LCD 16x2 el valor de BPM, grafica el ritmo cardiaco por el Serial Plotter y pulso por el pin 3
// Conexion Sensor Pulsos -> Arduino UNO:   S -> A0 , Vcc -> 5V , (-) -> GND
// Conexion i2C -> Arduino UNO:  SCL-> A5   SDA->A4  VCC->5V  GND->GND
#include <Wire.h>                   // Incluimos la libreria i2c
unsigned char lectura=0;            // Establecemos una variable global, y la seteamos en cero
int pulsePin = 0;                   // Sensor de Pulso conectado al puerto A0
// Estas variables son volatiles porque son usadas durante la rutina de interrupcion en la segunda Pestaña
volatile int BPM;                   // Pulsaciones por minuto
volatile int Signal;                // Entrada de datos del sensor de pulsos
volatile int IBI = 600;             // tiempo entre pulsaciones
volatile boolean Pulse = false;     // Verdadero cuando la onda de pulsos es alta, falso cuando es Baja
volatile boolean QS = false;        // Verdadero cuando el Arduino Busca un pulso del Corazon

#include "pitches.h" //add Equivalent frequency for musical note
#include "themes.h" //add Note vale and duration 

void setup(){  
  interruptSetup();                  // Configura la interrucion para leer el sensor de pulsos cada 2mS  
  
  Serial.begin(9600); 
   Wire.begin(1);                    // Nos asignamos el numero 1 como esclavos (de ser maestro va vacio esto)
  Wire.onRequest(respuestaEvento);  // Al activarse el evento de peticion, se ejecuta la funcion respuestaEvento
  Wire.onReceive(recibidoEvento);   // Al activarse el evento de lectura, se ejecuta la funcion recibidoEvento  
 pinMode(3, OUTPUT);                         
               // Puerto serial configurado a 9600 Baudios

}

void loop(){
 int pulso = analogRead(A0);           //Lee el valor del pulsometro conectado al puerto Analogo A0
 if (pulso >= 600) {                   // Enciende led 3 cuando el pulso pasa de un valor (debe ajustarse)
    digitalWrite(3, HIGH);
 }  
 else{
    digitalWrite(3, LOW);
 }  
   //lcd.setCursor(1,0);                   //Muestra en el LCD el valor de BPM 
    //lcd.print("BPM= ");
   // lcd.print(BPM);
   // lcd.print("   "); 
   //Serial.print("BPM = ");  Serial.println(BPM); //Habilitar estas linea para ver BPM en el monitor serial pero deshabilitar la siguiente
  // Serial.println(pulso);         
   lectura=BPM;
   Serial.println(pulso);      
   // envia el valor del pulso por el puerto serie  (desabilitarla si habilita la anterior linea)
  if (QS == true){                       // Bandera del Quantified Self es verdadera cuando el Arduino busca un pulso del corazon
    QS = false;                          // Reset a la bandera del Quantified Self 
  }
}







void respuestaEvento()            // Evento de peticion se activa cuando un master nos pide que le enviemos algun dato
{
  Wire.write(lectura);            // Enviamos el resultado de la lectura al maestro que lo solicito
}

void recibidoEvento(int howMany)  // Evento de recpcion
{
  unsigned char pedido;
  while( Wire.available())        // Leemos hasta que no haya datos, osea el 1 que va a enviar el maestro
  {
    pedido = Wire.read();       
  }
}



 
