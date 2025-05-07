#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Pines para el módulo nRF24L01
#define CE_PIN 4  // D4 en ESP32
#define CSN_PIN 5 // D5 en ESP32

RF24 radio(CE_PIN, CSN_PIN);

// Dirección de comunicación
const byte address[6] = "00001";

// Variables de control
int receivedData[16]; // Para almacenar los datos recibidos
unsigned long lastReceiveTime = 0;
const unsigned long timeout = 60000; // Timeout de 1 minuto

void setup() {
  Serial.begin(115200);
  delay(1000); // Esperar para inicializar el puerto serial

  // Inicializar nRF24L01
  Serial.println("Inicializando nRF24L01...");
  if (!radio.begin()) {
    Serial.println("ERROR: nRF24L01 no detectado. Verifica las conexiones.");
    while (1); // Detener ejecución si no se detecta el módulo
  } else {
    Serial.println("nRF24L01 inicializado correctamente.");
  }

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  // Confirmar conexión con el emisor
  Serial.println("Confirmando conexión con el emisor...");
  radio.stopListening();
  const char confirmation[] = "OK";
  if (radio.write(&confirmation, sizeof(confirmation))) {
    Serial.println("Confirmación enviada al emisor.");
    lastReceiveTime = millis(); // Actualizar tiempo inicial
  } else {
    Serial.println("ERROR: No se pudo enviar la confirmación.");
  }
  radio.startListening();

  Serial.println("Receptor listo. Esperando datos...");
}

void loop() {
  unsigned long currentTime = millis();

  // Verificar si hay datos disponibles
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    lastReceiveTime = millis(); // Actualizar el tiempo de la última recepción

    // Mostrar datos recibidos
    Serial.print("Datos recibidos: ");
    for (int i = 0; i < 16; i++) {
      Serial.print(receivedData[i]);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Verificar timeout
  if (currentTime - lastReceiveTime >= timeout) {
    Serial.println("Tiempo de espera agotado. No se han recibido datos.");
  }
}
