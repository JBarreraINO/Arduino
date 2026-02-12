#include <Arduino.h>
#include "BluetoothSerial.h"
BluetoothSerial BT;
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <EEPROM.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int pinSensor = 14;
int pinSensor1 = 27;
int pinSensor2 = 13;
int pinSensor3 = 12;
int pinSensor4 = 35;
int pinBuzzer = 2;  // Pin del buzzer
bool buzzerEN = 1;
bool rotacion = 0;
bool color = 0;
bool logica = 0;
int interval = 100;
Adafruit_SH1106 myOLED(21, 22);
unsigned long tiempoInicio = 0;
unsigned long tiempoAnterior = 0;
static int contadorVueltas = 0;
bool condicionCumplida = false;  // Variable de bandera para controlar la ejecución
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
int rssi;
int velocidad = 0;
const unsigned long TIEMPO_MINIMO_VALIDO = interval * 3;
String listo = "";
String INTERVAL = "";
String BUZEN = "";


#define EEPROM_SIZE 4
#define DEBUG(a) BT.println(a);

RF24 radio(4, 5); // CE, CSN
const uint64_t canal = 0xE8E8F0F0E1LL;




const int pinPWM = 17;         // GPIO donde se genera la señal
const int canalPWM = 0;        // Canal de PWM (0–15)
const int frecuencia = 38000;  // Frecuencia en Hz
const int resolucion = 8;      // Resolución en bits (0–20), 8 bits → 0–255 duty


char mensaje[] = "RADIO LISTO";

// 'LOGOBPM', 128x64px
const unsigned char barreraLOGOBPM[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x01, 0xf8, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x03, 0xfe, 0x00, 0x30, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1e, 0x0f, 0x8f, 0x00, 0x70, 0x03, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x07, 0x9e, 0x07, 0x00, 0x88, 0x04, 0x40, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x03, 0xbc, 0x03, 0x80, 0x06, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x01, 0xf8, 0x01, 0x80, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0xf0, 0x01, 0x80, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0xf0, 0x01, 0x80, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x01, 0xf8, 0x01, 0x80, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x03, 0xfc, 0x03, 0x80, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x07, 0x9e, 0x03, 0x80, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x0f, 0x0f, 0x0f, 0x00, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x07, 0xfe, 0x00, 0xc8, 0x04, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x01, 0xfc, 0x00, 0x30, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0xe0, 0x00, 0x60, 0x00, 0x30, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x30, 0xc7, 0x87, 0x8f, 0x3e, 0x3e, 0x78, 0x37, 0xe1, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x30, 0x87, 0xcf, 0x9f, 0x7f, 0x7e, 0x7c, 0x37, 0xf3, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3f, 0xc7, 0x48, 0x30, 0x41, 0x60, 0xf4, 0x34, 0x12, 0x18, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x30, 0x4f, 0x48, 0x30, 0x5f, 0x61, 0xf4, 0x34, 0x16, 0x18, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x30, 0x48, 0x48, 0x30, 0x60, 0x61, 0x84, 0x34, 0x12, 0x18, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3f, 0xcf, 0xc8, 0x30, 0x7c, 0x61, 0xfd, 0x34, 0x13, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0x87, 0x88, 0x10, 0x1c, 0x60, 0x79, 0x24, 0x11, 0xe0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char btimages[] PROGMEM = {
  0xff, 0xff, 0xf3, 0xff, 0xff, 0x80, 0xff, 0xff, 0xf1, 0xff, 0xff, 0x80, 0xff, 0xff, 0xf0, 0xff,
  0xff, 0x80, 0xff, 0xff, 0xf2, 0x7f, 0xff, 0x80, 0xff, 0xff, 0xf2, 0x3f, 0xff, 0x80, 0xff, 0xfe,
  0x73, 0x3f, 0xff, 0x80, 0xff, 0xff, 0x33, 0x3f, 0xff, 0x80, 0xff, 0xff, 0x92, 0x7f, 0xff, 0x80,
  0xff, 0xff, 0xc0, 0xff, 0xff, 0x80, 0xff, 0xff, 0xe1, 0xff, 0xff, 0x80, 0xff, 0xff, 0xe3, 0xff,
  0xff, 0x80, 0xff, 0xff, 0xe1, 0xff, 0xff, 0x80, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x80, 0xff, 0xff,
  0x92, 0x7f, 0xff, 0x80, 0xff, 0xff, 0x33, 0x3f, 0xff, 0x80, 0xff, 0xfe, 0x73, 0x3f, 0xff, 0x80,
  0xff, 0xff, 0xf3, 0x3f, 0xff, 0x80, 0xff, 0xff, 0xf2, 0x7f, 0xff, 0x80, 0xff, 0xff, 0xf0, 0xff,
  0xff, 0x80, 0xff, 0xff, 0xf1, 0xff, 0xff, 0x80, 0xff, 0xff, 0xf3, 0xff, 0xff, 0x80
};
// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1040)
const int barreraallArray_LEN = 1;
const unsigned char* barreraallArray[1] = {
  barreraLOGOBPM
};
const int btallArray_LEN = 1;
const unsigned char* btallArray[1] = {
  btimages
};

String limpiarString(String str) {
  String resultado = "";

  for (int i = 0; i < str.length(); i++) {
    char c = str.charAt(i);
    if (isPrintable(c)) {  // Verifica si el carácter es imprimible
      resultado += c;      // Agrega el carácter a la cadena resultado
    }
  }

  return resultado;  // Retorna la cadena limpia
}
void setupRadio() {
 
  Serial.println("iniciado radio ");
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(canal);
  radio.stopListening(); // modo TX

     radio.write(&mensaje, sizeof(mensaje));
   delay(2000);
}

void setup() { 
  Serial.begin(9600);
  ledcSetup(canalPWM, frecuencia, resolucion);
  Serial.println("cronometro Barrera");
   

    
  // Asignar canal al pin 17
  ledcAttachPin(pinPWM, canalPWM);

  // Activar la señal con 50% de duty cycle (127/255)
  ledcWrite(canalPWM, 127);
  EEPROM.begin(200);
  EEPROM.get(0, buzzerEN);
  EEPROM.get(5, interval);
  EEPROM.get(10, pinSensor);
  EEPROM.get(15, color);
  EEPROM.get(20, rotacion);
  EEPROM.get(25, logica);

  // Validar y asignar valores por defecto si están corruptos o vacíos
if (buzzerEN != 0 ||  buzzerEN != 1) {buzzerEN = 1;   EEPROM.put(0, buzzerEN); } // valor por defecto
if (interval <= 0 || interval > 5000) {interval = 10;EEPROM.put(5, interval);}
if (pinSensor < 0 || pinSensor > 100) {pinSensor = 13;EEPROM.put(10, pinSensor);}
if (color != 0 || color != 1) {color = 0; EEPROM.put(15, color);}
if (rotacion  != 0 || rotacion != 1) {rotacion = 0;  EEPROM.put(20, rotacion);}
if (logica != 0 || logica != 1) {logica = 1;  EEPROM.put(25, logica);}

  // (Opcional) Guardar otra vez en EEPROM si detectaste que estaban mal

  
  
 



  if (rotacion == 1) {
    myOLED.setRotation(2);  // Rota el texto 180 grados
  } else {
    myOLED.setRotation(0);  // Rotación normal (0 grados)
  }

  // Condición para invertir la pantalla según el valor de 'color'

  myOLED.begin(SH1106_SWITCHCAPVCC, 0x3C);
  BT.begin("CRBarreraINO");
  myOLED.setTextColor(WHITE);
  myOLED.setTextSize(1);

  pinMode(pinSensor, INPUT_PULLDOWN);
  pinMode(pinSensor1, INPUT_PULLDOWN);
  pinMode(pinSensor2, INPUT_PULLDOWN);
  pinMode(pinSensor4, INPUT_PULLDOWN);


  pinMode(pinBuzzer, OUTPUT);
  // Configurar el pin del buzzer como salida
  digitalWrite(pinBuzzer, LOW);
  myOLED.drawBitmap(0, 0, barreraLOGOBPM, 128, 64, WHITE, BLACK);
  myOLED.display();
  delay(1000);
  myOLED.setCursor(22, 50);  // Ajusta la posición vertical
  myOLED.print("ESTOY LISTO!!!");
   
  if (color == 1) {
    myOLED.invertDisplay(true);  // Invierte la pantalla
    myOLED.display();
  } else {
    myOLED.invertDisplay(false);  // Pantalla normal (sin invertir)
    myOLED.display();
  }

  myOLED.display();
  // rssi=BT.getSignalStrength();

  Serial.println(pinSensor);
  Serial.println(color);
  Serial.println(rotacion);
  Serial.println(logica);



  while (true) {


    if (condicionCumplida == false) {  // Si la condición no se ha cumplido aún
      if (BT.connected()) {
        myOLED.drawBitmap(100, 0, btimages, 41, 21, BLACK, WHITE);
        myOLED.display();
        delay(1000);
        Serial.println("CONECTADO A BT.");
        Serial.println(pinSensor);
        Serial.println(color);
        Serial.println(rotacion);
        Serial.println(logica);
        condicionCumplida = true;
      }
    }

    if (condicionCumplida == true) {  // Si la condición no se ha cumplido aún
      if (!BT.connected()) {
        myOLED.drawBitmap(100, 0, btimages, 41, 21, BLACK, BLACK);
        myOLED.display();
        delay(1000);
        condicionCumplida = false;
      }
    }
 
    if (digitalRead(pinSensor) == logica) {
      break;
    }



    if (BT.available() || Serial.available()) {
      //BT.print("waiting..");

      myOLED.display();
      String data = BT.readStringUntil('\n');

      data = limpiarString(data);  // Llamar a la función para limpiar el string

      Serial.println(data);
      BT.print("comando:");
      BT.println(data);
      if (data == "show" || data == "mostrar" || data == "variables") {

        BT.print("BUZZER:");
        BT.println(buzzerEN);
        BT.print("INTERVAL:");
        BT.println(interval);
        BT.print("SENSOR:");
        BT.println(pinSensor);
        BT.print("color:");
        BT.println(color);
        BT.print("rotacion:");
        BT.println(rotacion);
        BT.print("logica:");
        BT.println(logica);
      } else

        if (data == "interval" || data == "INTERVAL") {
        BT.print("comando:");
        BT.println(data);
        BT.print("WRITE INTERVAL:");
        while (true) {
          if (BT.available()) {

            String data = BT.readStringUntil('\n');
            data = limpiarString(data);  // Llamar a la función para limpiar el string

            Serial.println(data);
            int temp = data.toInt();
            EEPROM.put(5, temp);
            EEPROM.commit();

            BT.print("INTERVAL cambiado a:");
            EEPROM.get(5, interval);
            BT.print(interval);
            break;
          }
        }
      }  //data if


      else

        if (data == "sensor" || data == "SENSOR") {
        BT.print("comando:");
        BT.println(data);
        BT.print("WRITE MAIN SENSOR:");
        while (true) {
          if (BT.available()) {

            String data = BT.readStringUntil('\n');
            data = limpiarString(data);  // Llamar a la función para limpiar el string

            Serial.println(data);
            int temp = data.toInt();

            if (temp == 12 || temp == 13 || temp == 14 || temp == 27 || temp == 35 || temp == 23 ) {
              EEPROM.put(10, temp);
              EEPROM.commit();

              BT.print("SENSOR cambiado a:");
              EEPROM.get(10, pinSensor);
              BT.print(pinSensor);
              break;
            } else {
              // La condición no se cumple cuando temp es diferente de 0 y 1
              BT.print("deber ser  12 o 13 o 14 o 27 o 35 o 23");
            }
          }
        }
      }  //data if

      else

        if (data == "buzzer" || data == "BUZZER") {
        BT.print("comando:");
        BT.println(data);
        BT.print("ENABLE BUZZER:");
        while (true) {
          if (BT.available()) {

            String data = BT.readStringUntil('\n');
            data = limpiarString(data);  // Llamar a la función para limpiar el string

            Serial.println(data);
            int temp = data.toInt();
            if (temp == 0 || temp == 1) {
              // La condición se cumple cuando miValor es igual a 0 o 1
              EEPROM.put(0, temp);
              EEPROM.commit();
              BT.print("buzzer cambiado a:");
              EEPROM.get(0, buzzerEN);
              BT.print(buzzerEN);
              if (buzzerEN == 1) {
                BT.println("ENABLE");
              } else BT.println("DISABLE");
              break;
            } else {
              // La condición no se cumple cuando miValor es diferente de 0 y 1
              BT.print("deber ser  0 or 1");
            }
          }
        }
      } else if (data == "color" || data == "COLOR") {
        BT.print("comando:");
        BT.println(data);
        BT.print("Elija color:");
        while (true) {
          if (BT.available()) {
            String data = BT.readStringUntil('\n');
            data = limpiarString(data);  // Llamar a la función para limpiar el string

            Serial.println(data);

            int temp = data.toInt();
            if (temp == 0 || temp == 1) {
              // La condición se cumple cuando temp es igual a 0 o 1
              EEPROM.put(15, temp);
              EEPROM.commit();
              BT.print("color cambiado a:");

              EEPROM.get(15, color);
              BT.print(color);
              if (color == 1) {
                BT.println(" fondo blanco");
              } else {
                BT.println(" fondo negro ");
              }
              break;
            } else {
              // La condición no se cumple cuando temp es diferente de 0 y 1
              BT.print("deber ser  0 or 1");
            }
          }
        }
      }

      else if (data == "rotacion" || data == "ROTACION") {
        BT.print("comando:");
        BT.println(data);
        BT.print("SET ROTACION (1 = 0°, 0 = 180° ):");
        while (true) {
          if (BT.available()) {
            String data = BT.readStringUntil('\n');
            data = limpiarString(data);  // Llamar a la función para limpiar el string

            Serial.println(data);

            int temp = data.toInt();
            if (temp == 0 || temp == 1) {
              // La condición se cumple cuando temp es igual a 0 o 1
              EEPROM.put(20, temp);
              EEPROM.commit();
              BT.print("rotacion cambiado a:");

              EEPROM.get(20, rotacion);
              BT.print(rotacion);

              if (rotacion == 1) {
                BT.println(" 0 degrees (0°)");
              } else {
                BT.println(" 180 degrees (180°)");
              }
              break;
            } else {
              // La condición no se cumple cuando temp es diferente de 0 y 1
              BT.print("deber ser  0 or 1");
            }
          }
        }
      }


      else

        if (data == "reset") {
        BT.print("reset...");
        ESP.restart();
      }

      else

        if (data == "help" || data == "ayuda") {
        BT.println("commands for change");

        BT.println("buzzer= 1 o 0");
        BT.println("sensors= (1 a4)");
        BT.println("interval= (50 a 1000)ms");
        BT.println("rotacion= 1 o 0");
        BT.println("color= (1 o 0)");

        BT.println("Logica= (1 o 0)");
      }



      else if (data == "logica" || data == "LOGICA") {
        BT.print("comando:");
        BT.println(data);
        BT.print("Logica de sensor:");
        while (true) {
          if (BT.available()) {

            String data = BT.readStringUntil('\n');
            data = limpiarString(data);  // Llamar a la función para limpiar el string

            Serial.println(data);
            int temp = data.toInt();
            if (temp == 0 || temp == 1) {
              // La condición se cumple cuando miValor es igual a 0 o 1
              EEPROM.put(25, temp);
              EEPROM.commit();
              BT.print("logica cambiada a:");
              EEPROM.get(25, logica);
              BT.print(logica);
              if (logica == 1) {
                BT.println("HIGH");
              } else BT.println("LOW");
              break;
            } else {
              // La condición no se cumple cuando miValor es diferente de 0 y 1
              BT.print("deber ser  0 or 1");
            }
          }
        }
      }

      else

        if (data == "ok" || data == "save") {
        BT.println("brake and exit");
        break;
      }

      if (data == "guardar") {


        while (true) {
          if (BT.available()) {

            String data = BT.readStringUntil('\n');
            data = limpiarString(data);  // Llamar a la función para limpiar el string
            BT.println(data);
            Serial.println(data);

            char inputBuffer[data.length() + 1];  // +1 para el carácter nulo
            data.toCharArray(inputBuffer, data.length() + 1);

            char* token = strtok(inputBuffer, ",");

            if (token != NULL) {
              pinSensor = atoi(token);  // Convertir el token a entero (ejemplo)
              int temp = pinSensor;

              if (temp == 12 || temp == 13 || temp == 14 || temp == 27 || temp == 35) {
                EEPROM.put(10, temp);
                EEPROM.commit();
                EEPROM.get(10, pinSensor);


              } else {
                BT.print("dato invalido");
              }
            }




            // Obtener el siguiente token
            token = strtok(NULL, ",");

            if (token != NULL) {
              buzzerEN = atoi(token);  // Convertir el token a entero (ejemplo)
              int temp = buzzerEN;
              if (temp == 0 || temp == 1) {
                // La condición se cumple cuando miValor es igual a 0 o 1
                EEPROM.put(0, temp);
                EEPROM.commit();

              } else {
                // La condición no se cumple cuando miValor es diferente de 0 y 1
                BT.print("dato invalido");
              }
            }
            token = strtok(NULL, ",");

            if (token != NULL) {
              interval = atoi(token);

              EEPROM.put(5, interval);
              EEPROM.commit();
            }

            token = strtok(NULL, ",");

            if (token != NULL) {
              color = atoi(token);  // Convertir el token a entero (ejemplo)
              int temp = color;
              if (temp == 0 || temp == 1) {
                // La condición se cumple cuando temp es igual a 0 o 1
                EEPROM.put(15, temp);
                EEPROM.commit();

              } else {
                // La condición no se cumple cuando temp es diferente de 0 y 1
                BT.print("dato invalido");
              }
            }

            token = strtok(NULL, ",");

            if (token != NULL) {
              rotacion = atoi(token);  // Convertir el token a entero (ejemplo)
              int temp = rotacion;
              if (temp == 0 || temp == 1) {
                // La condición se cumple cuando temp es igual a 0 o 1
                EEPROM.put(20, temp);
                EEPROM.commit();
              } else {
                // La condición no se cumple cuando temp es diferente de 0 y 1
                BT.print("dato invalido");
              }
            }

            Serial.println("Datos guardados en EEPROM.");
            BT.println("guardando..");
            break;
          }
        }
      }

      if (data == "leer") {
        BT.print("datos:,");
        EEPROM.begin(200);
        EEPROM.get(0, buzzerEN);
        EEPROM.get(5, interval);
        EEPROM.get(10, pinSensor);
        EEPROM.get(15, color);
        EEPROM.get(20, rotacion);
        String result = String(pinSensor) + "," + String(buzzerEN) + "," + String(interval) + "," + String(color) + "," + String(rotacion);

        // Imprimimos la cadena en el monitor serial
        Serial.println(result);
        BT.print(result);
      }






      //if bt available
    }
  }

  setupRadio();
}


void loop() {
  ledcWrite(canalPWM, 127);
  // Formateamos el mensaje
   
  int estadoSensor = digitalRead(pinSensor);
  if (estadoSensor == !logica && tiempoInicio == 0) {

    tiempoInicio = millis();
    myOLED.clearDisplay();  // Borra la pantalla OLED después de 5 vueltas
  }

  if (estadoSensor == logica && tiempoInicio != 0) {

    tiempoAnterior = tiempoInicio;
    tiempoInicio = millis();

    long tiempoCalculado = (long)(tiempoInicio - tiempoAnterior) - interval;
    unsigned long tiempoVuelta = (tiempoCalculado < 0) ? 0 : (unsigned long)tiempoCalculado;

    // Mostramos el tiempo de vuelta en una nueva línea en la pantalla OLED


    if (tiempoVuelta < TIEMPO_MINIMO_VALIDO) {
      return;  // Salir sin imprimir ni contar vuelta
    }

    String mensaje = "Tiempo de vuelta ";
    mensaje += String(contadorVueltas + 1);
    mensaje += ": ";
    mensaje += formatoTiempoTranscurrido(tiempoVuelta);

    digitalWrite(pinBuzzer, buzzerEN);          // Activar el buzzer cuando se activa el sensor
    myOLED.setCursor(0, contadorVueltas * 10);  // Ajusta la posición vertical
    myOLED.print("Vuelta ");
    myOLED.print(contadorVueltas + 1);
    myOLED.print(": ");
    myOLED.print(formatoTiempoTranscurrido(tiempoVuelta));

   
    myOLED.display();


 
    Serial.print("Tiempo de vuelta ");
    Serial.print(contadorVueltas + 1);
    Serial.print(": ");
    Serial.println(formatoTiempoTranscurrido(tiempoVuelta));

  char buffer[32];
 formatoTiempoTranscurrido(tiempoVuelta).toCharArray(buffer, sizeof(buffer));

    radio.write(&buffer, sizeof(buffer));               // enviar solo lo que ocupa

    BT.print("Tiempo de vuelta ");
    BT.print(contadorVueltas + 1);
    BT.print(": ");
    BT.println(formatoTiempoTranscurrido(tiempoVuelta));

    contadorVueltas++;

    // Si se han completado 5 vueltas, reiniciamos el contador de vueltas
    if (contadorVueltas == 5) {
      contadorVueltas = 0;
      myOLED.clearDisplay();  // Borra la pantalla OLED después de 5 vueltas
    }

    digitalWrite(pinBuzzer, LOW);  // Apagar el buzzer cuando se suelta el sensor
  }
}

String formatoTiempoTranscurrido(unsigned long tiempoTranscurrido) {
  int minutos = tiempoTranscurrido / 60000;
  int segundos = (tiempoTranscurrido % 60000) / 1000;
  int milisegundos = (tiempoTranscurrido % 1000);

  String tiempoFormateado = "";
  tiempoFormateado += String(minutos) + "m ";
  tiempoFormateado += String(segundos) + "s ";
  tiempoFormateado += String(milisegundos) + "ms";

  return tiempoFormateado;
}
void writeString(char add, String data) {
  int _size = data.length();
  int i;
  for (i = 0; i < _size; i++) {
    EEPROM.write(add + i, data[i]);
  }
  EEPROM.write(add + _size, '\0');  //Add termination null character for String Data
  EEPROM.commit();
}


String read_String(char add) {
 
  char data[200];  //Max 100 Bytes
  int len = 0;
  unsigned char k;
  k = EEPROM.read(add);
  while (k != '\0' && len < 500)  //Read until null character
  {
    k = EEPROM.read(add + len);
    data[len] = k;
    len++;
  }
  data[len] = '\0';
  return String(data);
}