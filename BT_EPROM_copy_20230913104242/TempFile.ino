#include "BluetoothSerial.h"
BluetoothSerial BT;
#include <EEPROM.h>
String ssid = "";
String password = "";
String listo = "";

char WIFI_SSID[50] = "";      //IoT4.0
char WIFI_PASSWORD[50] = "";  //Industria4.0Mtx
String HOST_NAME = "http://192.168.16.156";  // PC's IP address

String PATH_NAME = "/iot/iot4.php";
String queryString = "";
#define EEPROM_SIZE 4
#define DEBUG(a) BT.println(a);


//////////////
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

void setup() {
  Serial.begin(115200);
  BT.begin("PROMEESP32");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  EEPROM.begin(200);
  ssid = read_String(0);
  password = read_String(30);
  PATH_NAME = read_String(50);
  HOST_NAME = read_String(100);
  queryString = read_String(150);
  password.toCharArray(WIFI_PASSWORD, 50);
  ssid.toCharArray(WIFI_SSID, 50);
}

void loop() {

  if (BT.available()) {
    String data = BT.readStringUntil('\n');
    int conteo = data.length();
    data.remove(conteo - 1, 1);
    data.remove(0, 1);
    Serial.println(data);



    if (data == "show") {
      BT.print("espere...");
      ssid = read_String(0);
      password = read_String(30);
      PATH_NAME = read_String(50);
      HOST_NAME = read_String(100);
      queryString = read_String(150);
      BT.print("WIFI_SSID:");
      BT.print(WIFI_SSID);
      BT.print(";");
      BT.print("WIFI_PASSWORD:");
      BT.print(WIFI_PASSWORD);
      BT.print(";");
      BT.print("PATH_NAME:");
      BT.print(PATH_NAME);
      BT.print(";");
      BT.print("HOST_NAME:");
      BT.print(HOST_NAME);
      BT.print(";");
      BT.print("QueryString");
      BT.print(queryString);
      BT.print(";");
    } else

      if (data == "read") {

      BT.print("WIFI_SSID:");
      BT.print(WIFI_SSID);
      BT.print(";");
      BT.print("WIFI_PASSWORD:");
      BT.print(WIFI_PASSWORD);
      BT.print(";");
      BT.print("PATH_NAME:");
      BT.print(PATH_NAME);
      BT.print(";");
      BT.print("HOST_NAME:");
      BT.print(HOST_NAME);
      BT.print(";");
      BT.print("QueryString:");
      BT.print(queryString);
      BT.print(";");
    } else








      if (data == "ssid" || data == "SSID") {
      BT.print("escriba su ssid");
      while (true) {
        if (BT.available()) {
          String data = BT.readStringUntil('\n');
          int conteo = data.length();  //cuenta longitud de el string
          data.remove(conteo - 1, 1);
          data.remove(0, 1);
          listo = data;
          ssid = listo;
          BT.print(ssid);
          writeString(0, ssid);

          ssid.toCharArray(WIFI_SSID, 50);

          if (listo.length() > 0) {
            BT.print("parametro cambiado a:");
            BT.print(ssid);
            listo = "";

            break;
          }
        }
      }
    }  //data if

    else

      if (data == "password" || data == "PASSWORD") {
      BT.print("escriba su PASSWORD");
      while (true) {
        if (BT.available()) {
          String data = BT.readStringUntil('\n');
          int conteo = data.length();  //cuenta longitud de el string
          data.remove(conteo - 1, 1);
          data.remove(0, 1);
          listo = data;
          password = listo;

          writeString(30, password);
          password.toCharArray(WIFI_PASSWORD, 50);


          if (listo.length() > 0) {
            BT.print("parametro cambiado a:");
            BT.print(password);
            listo = "";

            break;
          }
        }
      }
    }  //data if

    else

      if (data == "PATH_NAME" || data == "path_name") {
      BT.print("Escriba su PATH_NAME");
      while (true) {
        if (BT.available()) {
          String data = BT.readStringUntil('\n');
          int conteo = data.length();
          data.remove(conteo - 1, 1);
          data.remove(0, 1);
          listo = data;
          PATH_NAME = listo;
          //BT.print(PATH_NAME);
          writeString(50, PATH_NAME);
          //EEPROM.commit();

          if (listo.length() > 0) {
            BT.print("parametro cambiado a:");
            BT.print(PATH_NAME);
            listo = "";

            break;
          }
        }
      }
    }


    else

      if (data == "reset") {
      BT.print("reseteando...");
      ESP.restart();
    }


    else

      if (data == "HOST_NAME" || data == "host_name") {
      BT.print("Escriba su HOST_NAME");
      while (true) {
        if (BT.available()) {
          String data = BT.readStringUntil('\n');
          int conteo = data.length();
          data.remove(conteo - 1, 1);
          data.remove(0, 1);
          listo = data;
          HOST_NAME = listo;
          //BT.print(PATH_NAME);
          writeString(100, HOST_NAME);
          //EEPROM.commit();

          if (listo.length() > 0) {
            BT.print("parametro cambiado a:");
            BT.print(HOST_NAME);
            listo = "";

            break;
          }
        }
      }
    }


    else

      if (data == "query" || data == "QUERY") {
      BT.print("escriba su cadena");
      while (true) {
        if (BT.available()) {
          String data = BT.readStringUntil('\n');
          int conteo = data.length();  //cuenta longitud de el string
          data.remove(conteo - 1, 1);
          data.remove(0, 1);
          listo = data;
          queryString = listo;

          writeString(150, queryString);


          if (listo.length() > 0) {
            BT.print("parametro cambiado a:");
            BT.print(queryString);
            listo = "";

            break;
          }
        }
      }
    }  //data if












  }  //if bt available
  
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
  int i;
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