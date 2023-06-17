/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-mysql
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <OLED_I2C.h>
#include <ESP32Time.h>
#include "time.h"
OLED  myOLED(21,22); // Remember to add the RESET pin if your display requires it...
ESP32Time rtc;
extern uint8_t SmallFont[];
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 0;
int HR =0;
int SC = 0;
int MN =0;
String SE;
struct tm timeinfo;
int x=0;
const char WIFI_SSID[] = "Administrativos Metrex";
const char WIFI_PASSWORD[] = "M3tr3x2022*";
int randomnumero;
String HOST_NAME = "http://192.168.16.156"; // change to your PC's IP address
String PATH_NAME   = "/iot/iot4.php";
String queryString = "?temperature=12";
int LED = 2;
int Bot = A0;
int valor = 0;
int contador = 0;
int estadoanteriorboton = 0;
int pulsador=35;
extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
void setup() {
  Serial.begin(9600);    
   
  
 Wire.begin();
  myOLED.begin();
  myOLED.clrScr();
  //myOLED.drawBitmap(0, 0, logo, 128, 64);
  myOLED.setFont(SmallFont);
  //myOLED.update();
  myOLED.clrScr();

 pinMode(LED, OUTPUT); // inicializa como salida digital el pin 13
pinMode(Bot, INPUT); // inicializa como entrada digital el 7
pinMode(pulsador, INPUT); // inicializa como entrada digital el 7
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    myOLED.setFont(SmallFont);
      myOLED.print("Conectando a wifi ", LEFT, 0);
       myOLED.setFont(TinyFont);
     myOLED.print(WIFI_SSID, LEFT, 16);
    Serial.print(".");
    myOLED.update();
  myOLED.print(WIFI_SSID, LEFT, 16);
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
    myOLED.setFont(SmallFont);
   myOLED.clrScr();
  myOLED.print("espere....", LEFT, 16);
  delay(1000);
  myOLED.print("ok", RIGHT, 16);
  delay(1000);
    myOLED.update();
}

void loop() {
configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
HR = rtc.getHour(true)  ;
SC = rtc.getSecond();
MN = rtc.getMinute();
SE = rtc.getDateTime();
Serial.print(SE);

 valor = digitalRead(pulsador); // lee el valor de la entrad digital pin 7
digitalWrite(LED, valor);
       int RSSI=WiFi.RSSI();
  myOLED.print("RSSI:", LEFT, 0);
   myOLED.printNumI(RSSI, RIGHT, 0);
  myOLED.print("HH:", LEFT, 16);
  myOLED.printNumI(contador, RIGHT, 16);
     myOLED.update();
    myOLED.clrScr();
    if (RSSI<0){
    myOLED.print("Conectado ", LEFT, 32);
}

if (WiFi.status() != WL_CONNECTED)
    {
    myOLED.print("Desconectado: ", LEFT, 32);
    myOLED.update();
  
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }

if(RSSI>=0)
{myOLED.setFont(TinyFont);
  myOLED.print("Error de conexion" , LEFT, 32);
  myOLED.update();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}
//reinicio de conteo 

if(valor != estadoanteriorboton){
 
if(valor == 0){
contador++;
Serial.print(contador);
//
 queryString=("?temperature=" + String(contador));
 Serial.println(queryString);
  HTTPClient http;
digitalWrite(2,HIGH);
  http.begin(HOST_NAME + PATH_NAME + queryString); //HTTP  
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
//
if (contador == 1000) {
contador = 0;
}
}
}
estadoanteriorboton = valor;

  
}
