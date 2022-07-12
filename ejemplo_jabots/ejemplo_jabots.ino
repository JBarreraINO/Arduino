#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Logos.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES 10 // Number of snowflakes in the animation example
#define imageWidth 128
#define imageHeight 64
int sensorPin = A4; //Seleccion de pin analógico a ser leido
int sensorValue = 0; //Variable que captura el valor analógico del sensor
int ValueFinal = 0; //Variable a ser mostrada en la OLED
int i=0; //Variable incremental para el muestreo de los sensores.
int buttonState=0;
int k=0; //Variable que para la seleccion del sensor

int S0 = A0;   // A4 conectado a S0     S0 DEL MULTIPLEXOR
int S1 = A1;   // S1 conectado a S1     S1 DEL MULTIPLEXOR
int S2 = A2;   // A1 conectado a S2     S2 DEL MULTIPLEXOR
int S3 = A3;   // S0 conectado a S3     S3 DEL MULTIPLEXOR

void setup() {
 Serial.begin(9600);
 // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
 Serial.println(F("SSD1306 allocation failed"));
 for(;;); // Don't proceed, loop forever
 }
 //pinMode(A1, INPUT);
 pinMode(S0, OUTPUT);//S0
 pinMode(S1, OUTPUT);//S1
 pinMode(S2, OUTPUT);//S2
 pinMode(S3, OUTPUT);//S3

 drawbitmap();
 sixteenline();
}
void drawbitmap(void) { ///Función que imprime el logo ja-bots
 display.clearDisplay();
 display.drawBitmap(0,0,bitmap, 128, 64, 1);
 display.display();
 delay(2000);
}
void sixteenline(void) { ///Función que imprime el texto "SIXTEENLINE"
 display.clearDisplay();
 display.drawBitmap(0,0,SIXTEENLINE, 128, 64, 1);
 display.display();

 delay(2000);
}

void lectura(int k) { //Función para la selección del sensor especifico.
 switch (k) {
 case 15: digitalWrite(S0, LOW);digitalWrite(S1, LOW);digitalWrite(S2,
LOW);digitalWrite(S3, LOW);break;
 case 14: digitalWrite(S0, HIGH);digitalWrite(S1, LOW);digitalWrite(S2,
LOW);digitalWrite(S3, LOW);break;
 case 13: digitalWrite(S0, LOW);digitalWrite(S1, HIGH);digitalWrite(S2,
LOW);digitalWrite(S3, LOW);break;
 case 12: digitalWrite(S0, HIGH);digitalWrite(S1, HIGH);digitalWrite(S2,
LOW);digitalWrite(S3, LOW);break;
 case 11: digitalWrite(S0, LOW);digitalWrite(S1, LOW);digitalWrite(S2,
HIGH);digitalWrite(S3, LOW);break;
 case 10: digitalWrite(S0, HIGH);digitalWrite(S1, LOW);digitalWrite(S2,
HIGH);digitalWrite(S3, LOW);break;
 case 9: digitalWrite(S0, LOW);digitalWrite(S1, HIGH);digitalWrite(S2,
HIGH);digitalWrite(S3, LOW);break;
 case 8: digitalWrite(S0, HIGH);digitalWrite(S1, HIGH);digitalWrite(S2,
HIGH);digitalWrite(S3, LOW);break;
 case 7: digitalWrite(S0, LOW);digitalWrite(S1, LOW);digitalWrite(S2,
LOW);digitalWrite(S3, HIGH);break;
 case 6: digitalWrite(S0, HIGH);digitalWrite(S1, LOW);digitalWrite(S2,
LOW);digitalWrite(S3, HIGH);break;
 case 5: digitalWrite(S0, LOW);digitalWrite(S1, HIGH);digitalWrite(S2,
LOW);digitalWrite(S3, HIGH);break;
 case 4: digitalWrite(S0, HIGH);digitalWrite(S1, HIGH);digitalWrite(S2,
LOW);digitalWrite(S3, HIGH);break;
 case 3: digitalWrite(S0, LOW);digitalWrite(S1, LOW);digitalWrite(S2,
HIGH);digitalWrite(S3, HIGH);break;
 case 2: digitalWrite(S0, HIGH);digitalWrite(S1, LOW);digitalWrite(S2,
HIGH);digitalWrite(S3, HIGH);break;
 case 1: digitalWrite(S0, LOW);digitalWrite(S1, HIGH);digitalWrite(S2,
HIGH);digitalWrite(S3, HIGH);break;
 case 0: digitalWrite(S0, HIGH);digitalWrite(S1, HIGH);digitalWrite(S2,
HIGH);digitalWrite(S3, HIGH);break;
 }
}
void loop() { // Codigo principal a ser repetido indefinidamente.
 display.clearDisplay(); // Limpia el buffer de la pantalla
 display.fillRect(0, 2, 128, 61, SSD1306_WHITE);
 for(i=0; i<=15; i++) {
 lectura(15-i);
 sensorValue = analogRead(sensorPin);
 
 ValueFinal=(61-sensorValue*(61/1023.0));
  Serial.println( ValueFinal);
 display.fillRect((i*8), 3, 8, ValueFinal, SSD1306_BLACK);//coordenada en x, coordenada en y, ancho del rectangulo, altura del rectangulo, color
 display.drawRect((i*8), 2, (8+i*8), 61, SSD1306_BLACK);//coordenada x1,coordenada y1, coordenada x2, coordenada y2, color.
 }
 display.display(); // Actualiza la pantalla con los valores cargados.
}
