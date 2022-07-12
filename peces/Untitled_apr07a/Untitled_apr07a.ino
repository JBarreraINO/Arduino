#include "arduino_secrets.h"
#include "thingProperties.h"
#include <ESP32Time.h>
#include "time.h"
#include <Arduino.h>

#include <OLED_I2C.h>

OLED  myOLED(21,22);
extern uint8_t SmallFont[];

ESP32Time rtc;
const char* ssid       = "Barrera.ino";
const char* password   = "1061814177_1";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 0;
int contador,contador1,contador2,contador3,contador4,contador5,contador6,contador7=0;
void printLocalTime()
{
  
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup()
{
 myOLED.begin();
  myOLED.setFont(SmallFont);
  //myOLED.setFont(TinyFont);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
    Serial.printf("Connecting to %s ", ssid);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); delay(1500);
  delay(1500);
  //connect to WiFi
Serial.println(" CONNECTED");
 
 	
  
}

void loop()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  ArduinoCloud.update();
  //Your code here
  //printLocalTime();
  //string Horario= rtc.getTimeDate();    //  () 2:24:38 Sun, Jan 17 2021
  int HR = rtc.getHour(true)  ;
  int SC = rtc.getSecond();
  int MN = rtc.getMinute();
  string fecha= rtc.getDate(); 
  myOLED.clrScr();
  
  myOLED.print("fecha:", LEFT, 0);
  myOLED.print(fecha, CENTER, 16);
  myOLED.print(HR,MN,SC, CENTER, 24);
  myOLED.update();
  delay (5000);
  
  
  
  Serial.print("   HORA:");
  Serial.println(HR);
  Serial.print("  MINUTO:");
  Serial.println(MN);
  Serial.print("  segundo:");
  Serial.println(SC);
  //dispensar 1 ves por dia
  
  if (veces == 1) {
    Serial.print("1 VEZ POR DIA");
    if (HR==12&&MN==1&&SC==1)
    {
     
        digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 1 DOSIS");
      }

    }
    //termina



  //dispensar 2 ves por dia
  if (veces == 2) {
    Serial.print("2 VECES POR DIA");
    //primera dosis
    if (HR == 12 && MN ==1 &&SC==1)
    {
             digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 1 DOSIS");

    }
    //segunda dosis
    if (HR == 23 && MN == 1 && SC==1)
    {
            digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 2 DOSIS");

    }
    //termina
  }


  //dispensar 3 ves por dia
  if (veces == 3) {
    Serial.print("3 VECES POR DIA");
    //primera dosis
    if (HR == 8 && MN == 1 && SC==1)
    {
            digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 1 DOSIS");

    }
    //segunda dosis
    if (HR == 16 && MN == 1 && SC==1)
    {
             digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 2 DOSIS ");

    }
    //tercera dosis
    if (HR == 23 &&MN == 1 && SC==1)
    {
             digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 3 DOSIS");

    }
    //termina
  }





  //dispensar 4 ves por dia
  if (veces == 4) {
    Serial.print("4 VECES POR DIA");
    //primera dosis
    if (HR == 6 && MN == 1 && SC==1)
    {
      digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 1 DOSIS");

    }
    //segunda dosis
    if (HR == 12 && MN == 1 && SC==1)
    {
     digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 2 DOSIS");

    }
    //tercera dosis
    if (HR == 16 &&MN == 1 && SC==1)
    {
digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 3 DOSIS");

    }
    //cuarta dosis
    if (HR == 23 && MN == 1 && SC==1)
    {
    digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 4 DOSIS");
    }
    //termina
  }


  //dispensar 5 ves por dia
  if (veces == 5) {
    Serial.print("5 VECES POR DIA");
    //primera dosis
    if (HR == 4 &&MN == 1 && SC==1)
    {
    digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 1 DOSIS");
    }
    //segunda dosis
    if (HR == 9 && MN == 1 && SC==1)
    {
       digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 2 DOSIS");

    }
    //tercera dosis
    if (HR == 2 && MN == 1 && SC==1)
    {
       digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 3 DOSIS");

    }
    //cuarta dosis
    if (HR == 20 && MN == 1 && SC==1)
    {
   digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 4 DOSIS");

    }
    //quinta dosis
    if (HR == 23 && MN == 1 && SC==1)
    {
      digitalWrite(2, HIGH);
        delay(cantidad*1000);
        digitalWrite(2, LOW);
        Serial.print("ECHO 5 DOSIS");

    }
    //termina
  }
  

  if (manual == true && seguridad==true)
  {
    digitalWrite(2, HIGH);
    delay(cantidad * 1000);
    digitalWrite(2, LOW);
    delay(50);
    contador++;
    Serial.print("ECHO MANUALMENTE");
    Serial.print(contador);

  }
  if (contador>5){
   digitalWrite(2, LOW);
    delay(50);
    
  }






  /*
    getTime()          //  (String) 15:24:38
    getDate()          //  (String) Sun, Jan 17 2021
    getDate(true)      //  (String) Sunday, January 17 2021
    getDateTime()      //  (String) Sun, Jan 17 2021 15:24:38
    getDateTime(true)  //  (String) Sunday, January 17 2021 15:24:38
    getTimeDate()      //  (String) 15:24:38 Sun, Jan 17 2021
    getTimeDate(true)  //  (String) 15:24:38 Sunday, January 17 2021

    getMicros()        //  (long)    723546
    getMillis()        //  (long)    723
    getEpoch()         //  (long)    1609459HIGH
    getSecond()        //  (int)     38    (0-59)
    getMinute()        //  (int)     24    (0-59)
    getHour()          //  (int)     3     (0-12)
    getHour(true)      //  (int)     15    (0-23)
    getAmPm()          //  (String)  pm
    getAmPm(true)      //  (String)  PM
    getDay()           //  (int)     17    (1-31)
    getDayofWeek()     //  (int)     0     (0-6)
    getDayofYear()     //  (int)     16    (0-365)
    getMonth()         //  (int)     0     (0-11)
    getYear()          //  (int)     2021

  */


}

void onCantidadChange()  {
  // Add your code here to act upon Cantidad change
}
void onManualChange() {
  
}

void onVecesChange() {}

/*
  Since Seguridad is READ_WRITE variable, onSeguridadChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSeguridadChange()  {
  // Add your code here to act upon Seguridad change
}
