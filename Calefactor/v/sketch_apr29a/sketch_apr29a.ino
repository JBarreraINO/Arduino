#include "DHT.h"
int GAS=2;
int chispero=7;
int bajo=10;
int alto=11;
int FAN=4;
int AGUA=5;
int presion=9;
#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
void setup() {

Serial.begin(9600);
 dht.begin();
pinMode(chispero,OUTPUT);
pinMode(presion , INPUT);
pinMode(bajo, INPUT);
pinMode(alto, INPUT);
pinMode(AGUA, OUTPUT);
pinMode(GAS, OUTPUT);
pinMode(FAN,OUTPUT);
ENCENDER();

}
void loop() {
 float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
 if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float hi = dht.computeHeatIndex(f, h);

if(t>45)
{digitalWrite(FAN,HIGH);
delay(100);
 }
else if(t<45){digitalWrite(FAN,LOW);}


  
  if(digitalRead(bajo) == HIGH){
 while(digitalRead(alto) == HIGH){
  AGUA1();
 }
  AGUACLOSE();
 }

  
if (digitalRead(presion)==LOW){
    while (digitalRead(presion) == LOW) {
  APAGAR();
  } 
 ENCENDER();
  }



Serial.println("Danilson es gay");

}



void ENCENDER(){
  digitalWrite(chispero,HIGH);
  digitalWrite(GAS,HIGH);
  delay(5000);
  digitalWrite(chispero,LOW);
  
 }
 void APAGAR(){
 digitalWrite(GAS,LOW);delay(10);
 }
 void AGUA1()
 {
   digitalWrite(AGUA,HIGH);delay(10);
  
  }
  void AGUACLOSE(){ digitalWrite(AGUA,LOW);delay(1000);                    }
