
#include <Wire.h>                // I2C  Library
#include "MAX30105.h"            // MAX3010x library
#include "heartRate.h"           // Heart rate calculating algorithm
#include "pitches.h" //add Equivalent frequency for musical note
#include "themes.h" //add Note vale and duration 




MAX30105 particleSensor;

const byte RATE_SIZE = 4;        // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];           // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;               // Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

unsigned int lectura=0;      


void setup() {
  Wire.setClock(400000);                         // Set I2C speed to 400kHz
  
  Serial.begin(9600); 
  Wire.begin(1);                    // Nos asignamos el numero 1 como esclavos (de ser maestro va vacio esto)
  Wire.onRequest(respuestaEvento);  // Al activarse el evento de peticion, se ejecuta la funcion respuestaEvento
  Wire.onReceive(recibidoEvento);   // Al activarse el evento de lectura, se ejecuta la funcion recibidoEvento  
  // Initialize sensor
  
  particleSensor.begin(Wire, I2C_SPEED_FAST);    // Use default I2C port, 400kHz speed
  particleSensor.setup();                        // Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A);     // Turn Red LED to low to indicate sensor is running

Play_Pirates();
}

void loop() {
  long irValue = particleSensor.getIR();              // Reading the IR value it will permit us to know if there's a finger on the sensor or not

  if (irValue > 50000)
  {

    if (checkForBeat(irValue) == true)                  //If a heart beat is detected, call checkForBeat as frequent as possible to get accurate value
    {
      long delta = millis() - lastBeat;                 //Measure duration between two beats
      lastBeat = millis();
      beatsPerMinute = 60 / (delta / 1000.0);           //Calculating the BPM
      if (beatsPerMinute < 255 && beatsPerMinute > 20)  //To calculate the average we strore some values (4) then do some math to calculate the average
      {
        rates[rateSpot++] = (byte)beatsPerMinute;       //Store this reading in the array
        rateSpot %= RATE_SIZE;                          //Wrap variable

        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
   tone(3,1000);                                        //And tone the buzzer for a 100ms you can reduce it it will be better
    delay(100);
    noTone(3);      

      
        lectura=beatAvg;
        Serial.println(beatAvg);
       
      }
    }
  }
  else
  {
    long int x=0;
    lectura=x;
  
     noTone(3);  
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

void Play_Pirates()
{ 
  for (int thisNote = 0; thisNote < (sizeof(Pirates_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / Pirates_duration[thisNote];//convert duration to time delay
    tone(3, Pirates_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.05; //Here 1.05 is tempo, increase to play it slower
    delay(pauseBetweenNotes);
    noTone(3); //stop music on pin 8 
    }
}
