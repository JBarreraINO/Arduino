/*
   This code is for DIY Heartbeat Monitoring Device which uses
   MAX30102 sensor for heart rate measurement. An arduino board
   used to get the raw readings from MAX30102 sensor then calculate
   the average heart beat and display the values in an OLED Display.
   This code is the modified version of the HeartRate Library example
   sketch.

   This device is for educational purpose only. This heart rate monitoring
   device cannot used in any health or medical sector.

   If you have any doubts then you can ask in the comment section of my
   YouTube Channel UtGo

   If you want to support me then please subscribe to my YouTube
   Channel https://bit.ly/34GtRnZ

   UtGo YouTube channel
*/


#include <Adafruit_GFX.h>        // OLED Library
#include <Adafruit_SSD1306.h>    // OLED Library
#include <Wire.h>                // I2C  Library
#include "MAX30105.h"            // MAX3010x library
#include "heartRate.h"           // Heart rate calculating algorithm


MAX30105 particleSensor;

const byte RATE_SIZE = 4;        // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];           // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;               // Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

#define SCREEN_WIDTH 128         // OLED display width, in pixels
#define SCREEN_HEIGHT 64         // OLED display height, in pixels
#define OLED_RESET    -1         // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)



void setup() {
  Wire.setClock(400000);                         // Set I2C speed to 400kHz
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);     // Start the OLED display
  display.setTextColor(WHITE);

  // Initialize sensor
  particleSensor.begin(Wire, I2C_SPEED_FAST);    // Use default I2C port, 400kHz speed
  particleSensor.setup();                        // Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A);     // Turn Red LED to low to indicate sensor is running

  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0, 20);
  display.print("BPM:");
  display.print(0);
  display.display();
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

        display.clearDisplay();
        display.setTextSize(3);
        display.setCursor(0, 20);
        display.print("BPM:");
        display.print(beatAvg);
        display.display();
      }
    }
  }
  else
  {
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(0, 20);
    display.print("BPM:");
    display.print(0);
    display.setCursor(0, 45);
    display.setTextSize(1);
    display.print("Place your finger in sensor and wait..");
    display.display();
     noTone(3);  
  }
}
