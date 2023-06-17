#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <esp_task_wdt.h>
//#define WDT_TIMEOUT 3
#define OLED_SDA 21
#define OLED_SCL 22

int i = 0;
int last = millis();
bool panic;

Adafruit_SH1106 myOLED(21, 22);




extern uint8_t logo[];
uint32_t chipId = 0;



struct tm timeinfo;
int x = 0;
//const char WIFI_SSID[] = "Administrativos Metrex";//IoT4.0
//const char WIFI_PASSWORD[] = "M3tr3x2022*";//Industria4.0Mtx
const char WIFI_SSID[] = "IND4.0";               //IoT4.0
const char WIFI_PASSWORD[] = "Industria4.0Mtx";  //Industria4.0Mtx
int randomnumero;
String HOST_NAME = "http://industria4.metrex.com.co";
//String HOST_NAME = "http://192.168.61.2:81/";
String PATH_NAME = "/iot/iot4.php";
String queryString = "";
int LED = 2;
int Bot = A0;

int valor = 0;
int contador = 0;
int contador1=0;
int estadoanteriorboton = 0;



int nvalor = 0;
int ncontador = 0;
int nestadoanteriorboton = 0;
int ncontador1=0;


int pulsador = 32;
int npulsador = 33;
void setup() {

  Serial.begin(9600);
  Wire.begin();
  myOLED.begin(SH1106_SWITCHCAPVCC, 0x3C);
  myOLED.setTextColor(WHITE);
  myOLED.setTextSize(1);
  myOLED.display();
  myOLED.clearDisplay();
  pinMode(LED, OUTPUT);      // inicializa como salida digital el pin 13
  pinMode(Bot, INPUT);       // inicializa como entrada digital el 7
  pinMode(pulsador, INPUT);  // inicializa como entrada digital el 7
  pinMode(npulsador, INPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
   
  //watch dog
  //esp_task_wdt_init(WDT_TIMEOUT, true);  // enable panic so ESP32 restarts
 // esp_task_wdt_add(NULL);
  //

  while (WiFi.status() != WL_CONNECTED) {

    panic=true;
    Serial.print(".");
    myOLED.clearDisplay();
    myOLED.drawBitmap(0, 0, logo, 128, 64, WHITE);
    myOLED.display();

    if (millis() - last >= 2000 && i < 2) {
      Serial.println("Resetting WDT...");
      //esp_task_wdt_reset();
       
      last = millis();
      i++;
      if (i == 2) {
        Serial.println("Stopping WDT reset. CPU should reboot in 3s");
        myOLED.clearDisplay();
        myOLED.setTextSize(1);
        myOLED.setCursor(0, 0);
        myOLED.print("Reset CPU ");
        ESP.restart();
      }
    }
  }

  myOLED.clearDisplay();
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("Conectando a wifi ");
  myOLED.setTextSize(0);
  myOLED.setCursor(0, 16);
  myOLED.print(WIFI_SSID);
  myOLED.display();




  for (int i = 0; i < 17; i = i + 8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  myOLED.setTextSize(1);
  myOLED.clearDisplay();
  myOLED.setCursor(0, 16);
  myOLED.print("espere");
  delay(1000);
  myOLED.display();
}

void loop() {



  valor = digitalRead(pulsador);  // lee el valor de la entrad digital pin 7
  nvalor=digitalRead(npulsador);
  digitalWrite(LED, valor);
  digitalWrite(LED, nvalor);
  int RSSI = WiFi.RSSI();
  myOLED.setCursor(0, 0);
  myOLED.print("RSSI:");
  myOLED.setCursor(110, 0);
  myOLED.print(RSSI);
  myOLED.setCursor(0, 10);
  myOLED.print("Conformes:");
  myOLED.setCursor(100, 10);
  myOLED.print(contador1);
  
  myOLED.setCursor(0, 20);
    myOLED.print("no conformes:");
  myOLED.setCursor(100, 20);    
  myOLED.print(ncontador1);
  myOLED.setCursor(0, 40);
  myOLED.print("chipID:");
    myOLED.setCursor(80, 40);
      myOLED.print(chipId);
  



  myOLED.setTextSize(1);

  myOLED.display();
  myOLED.clearDisplay();


  if (WiFi.status() != WL_CONNECTED || RSSI >= 0) {

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
      myOLED.setCursor(0, 20);
      myOLED.print("Desconectado: ");
      myOLED.display();

if (millis() - last >= 2000 && i < 4) {
      Serial.println("Resetting WDT...");
     
      last = millis();
      i++;
      if (i == 4) {
        Serial.println("Stopping WDT reset. CPU should reboot in 3s");
        myOLED.clearDisplay();
        myOLED.setTextSize(1);
        myOLED.setCursor(0, 0);
        myOLED.print("Reset CPU ");
        ESP.restart();
      }
    }



      
    }
  }


//para conformes 
  if (valor != estadoanteriorboton) {

    if (valor == 0) {
      contador++;
      contador1++;
      //delay(1500);


          queryString = ("?pulso=" + String(contador) + "," + String(RSSI) + "," + String(chipId)+ ","+String(ncontador));
      Serial.println(queryString);
      HTTPClient http;
      digitalWrite(2, HIGH);

      http.begin(HOST_NAME + PATH_NAME + queryString);  //HTTP
      int httpCode = http.GET();
      if (httpCode > 0) {
        // file found at server
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        } else {
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();




      if (contador == 1 ){
        contador = 0;
      }
    }
  }
  estadoanteriorboton = valor;


  
// para no conformes 
  if (nvalor != nestadoanteriorboton) {
    if (nvalor == 0) {
      ncontador++;
      ncontador1++;
      
      queryString = ("?pulso=" + String(contador) + "," + String(RSSI) + "," + String(chipId)+ ","+String(ncontador));
      Serial.println(queryString);
      HTTPClient http;
      digitalWrite(2, HIGH);

      http.begin(HOST_NAME + PATH_NAME + queryString);  //HTTP
      int httpCode = http.GET();
      if (httpCode > 0) {
        // file found at server
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        } else {
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();




      if (ncontador == 1) {
        ncontador = 0;
      }
    }
  }
  nestadoanteriorboton = nvalor;




  if (RSSI < 0) {
    myOLED.setCursor(0, 30);
    myOLED.print("Conectado ");
    panic=false;
  
  }
}