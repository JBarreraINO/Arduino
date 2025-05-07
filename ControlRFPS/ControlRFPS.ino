#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Pines para el módulo nRF24L01
#define CE_PIN 4  // D4 en ESP32
#define CSN_PIN 5 // D5 en ESP32

// Pines analógicos de la ESP32 y pines de encendido/apagado
const int analogPins[] = {13, 15, 2, 21, 22, 14, 27, 12, 36, 39, 34, 35, 32, 33, 25, 26};
const int powerPin = 18;  // Pin de encendido
const int powerOffPin = 19; // Pin de apagado
int analogValues[16]; // Valores leídos de los pines analógicos

// Control de tiempos
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 2000; // Intervalo de envío (ms)

RF24 radio(CE_PIN, CSN_PIN);

// Dirección de comunicación
const byte address[6] = "00001";

// Estado de confirmación
bool confirmed = false;

void setup() {
  Serial.begin(115200);
  delay(1000); // Esperar para inicializar el puerto serial

  // Configurar pines de encendido/apagado
  pinMode(powerPin, OUTPUT);
  pinMode(powerOffPin, OUTPUT);
  digitalWrite(powerPin, LOW);   // Asegurarse de que el sistema está apagado inicialmente
  digitalWrite(powerOffPin, LOW);

  // Inicializar nRF24L01
  Serial.println("Inicializando nRF24L01...");
  if (!radio.begin()) {
    Serial.println("ERROR: nRF24L01 no detectado. Verifica las conexiones.");
    while (1); // Detener ejecución si no se detecta el módulo
  } else {
    Serial.println("nRF24L01 inicializado correctamente.");
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setRetries(15, 15);
  radio.stopListening();

  // Confirmar conexión con el receptor
  Serial.println("Esperando confirmación del receptor...");
  const char confirmationResponse[] = "OK";
  unsigned long startTime = millis();
  while (millis() - startTime < 5000) { // Timeout de 5 segundos
    if (radio.write(&confirmationResponse, sizeof(confirmationResponse))) {
      Serial.println("Confirmación recibida del receptor.");
      confirmed = true;
      break;
    }
  }

  if (!confirmed) {
    Serial.println("ERROR: No se recibió confirmación del receptor. Verifica la conexión.");
    while (1); // Detener ejecución si no hay confirmación
  }

  // Encender el sistema después de la confirmación
  digitalWrite(powerPin, HIGH);
  Serial.println("Sistema encendido.");
}

void loop() {
  unsigned long currentTime = millis();

  // Leer señales analógicas
  for (int i = 0; i < 16; i++) {
    analogValues[i] = analogRead(analogPins[i]);
  }

  // Enviar datos al receptor
  if (currentTime - lastSendTime >= sendInterval) {
    lastSendTime = currentTime;

    Serial.print("Enviando datos al receptor: ");
    for (int i = 0; i < 16; i++) {
      Serial.print(analogValues[i]);
      Serial.print(" ");
    }
    Serial.println();

    if (radio.write(&analogValues, sizeof(analogValues))) {
      Serial.println("Datos enviados correctamente.");
    } else {
      Serial.println("ERROR: Fallo al enviar los datos.");
    }
  }

  // Apagar el sistema bajo ciertas condiciones (puedes personalizar esta parte)
  if (/* condición para apagar */ false) { // Cambia la condición según tu necesidad
    digitalWrite(powerPin, LOW);
    digitalWrite(powerOffPin, HIGH);
    Serial.println("Sistema apagado.");
    delay(1000); // Esperar un momento antes de detener
    while (1); // Detener ejecución
  }
}
