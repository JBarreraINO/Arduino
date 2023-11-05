#include <Arduino.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

int pinSensor = 12;
int pinBuzzer = 2; // Pin del buzzer
Adafruit_SH1106 myOLED(21, 22);
unsigned long tiempoInicio = 0;
unsigned long tiempoAnterior = 0;
static int contadorVueltas = 0;

void setup() {
  myOLED.begin(SH1106_SWITCHCAPVCC, 0x3C);
  SerialBT.begin("CRBarreraINO");
  myOLED.setTextColor(WHITE);
  myOLED.setTextSize(1);
  myOLED.display();
  Serial.begin(9600);
  pinMode(pinSensor, INPUT);
  pinMode(pinBuzzer, OUTPUT); // Configurar el pin del buzzer como salida
   digitalWrite(pinBuzzer, LOW);
   myOLED.clearDisplay(); // Borra la pantalla OLED después de 5 vueltas
   myOLED.display();
   myOLED.setCursor(0,0); // Ajusta la posición vertical
   myOLED.print("ESTOY READY PRRO!!!");
  myOLED.display();
}

void loop() {
  int estadoSensor = digitalRead(pinSensor);

  if (estadoSensor == LOW && tiempoInicio == 0) {
    tiempoInicio = millis();
       myOLED.clearDisplay(); // Borra la pantalla OLED después de 5 vueltas
    delay(200); // Pequeño retardo para estabilidad
  }

  if (estadoSensor == HIGH && tiempoInicio != 0) {
    delay(100);
    tiempoAnterior = tiempoInicio;
    tiempoInicio = millis();
    unsigned long tiempoVuelta = tiempoInicio - tiempoAnterior;
    digitalWrite(pinBuzzer, HIGH); // Activar el buzzer cuando se activa el sensor
    // Mostramos el tiempo de vuelta en una nueva línea en la pantalla OLED
    myOLED.setCursor(0, contadorVueltas * 10); // Ajusta la posición vertical
    myOLED.print("Vuelta ");
    myOLED.print(contadorVueltas + 1);
    myOLED.print(": ");
    myOLED.print(formatoTiempoTranscurrido(tiempoVuelta));
    myOLED.display();

    Serial.print("Tiempo de vuelta ");
    Serial.print(contadorVueltas + 1);
    Serial.print(": ");
    Serial.println(formatoTiempoTranscurrido(tiempoVuelta));

    SerialBT.print("Tiempo de vuelta ");
    SerialBT.print(contadorVueltas + 1);
    SerialBT.print(": ");
    SerialBT.println(formatoTiempoTranscurrido(tiempoVuelta));

    contadorVueltas++;

    // Si se han completado 5 vueltas, reiniciamos el contador de vueltas
    if (contadorVueltas == 5) {
      contadorVueltas = 0;
      myOLED.clearDisplay(); // Borra la pantalla OLED después de 5 vueltas
    }

    digitalWrite(pinBuzzer, LOW); // Apagar el buzzer cuando se suelta el sensor
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
