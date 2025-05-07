#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Definimos los pines CE y CSN para el NRF24L01
#define CE_PIN 4  // D4 en ESP32
#define CSN_PIN 5 // D5 en ESP32
#define canal 45
// Creamos el objeto radio
RF24 radio(CE_PIN, CSN_PIN);

// Dirección de comunicación (debe ser la misma en el emisor y el receptor)
const byte address[6] = "00001";

// Array para almacenar los valores recibidos
int receivedValues[11]; // Ajusta el tamaño según el número de sensores

void setup() {
  // Iniciamos la comunicación serial
  Serial.begin(9600);

  // Iniciamos el módulo NRF24L01
  if (!radio.begin()) {
    Serial.println("Error al iniciar el NRF24L01");
    while (1);
  }

  // Configuramos la máxima potencia y la velocidad de transmisión más alta
  radio.setPALevel(RF24_PA_MAX);   // Máxima potencia
  radio.setDataRate(RF24_2MBPS);  // Velocidad de transmisión más alta (2 Mbps)
  radio.setChannel(canal);           // Canal de comunicación (0-125, elige uno sin interferencias)

  // Abrimos un canal de lectura
  radio.openReadingPipe(0, address);
  radio.startListening(); // Configuramos como receptor
  
  Serial.print("Canal: ");
  Serial.println(canal);
  Serial.println("Receptor listo");
}

void loop() {
  // Verificamos si hay datos disponibles
  if (radio.available()) {
    // Leemos los datos recibidos
    radio.read(&receivedValues, sizeof(receivedValues));

    // Mostramos los valores en el monitor serial
    Serial.print("Valores recibidos: ");
    for (int i = 0; i < 12; i++) {  // Corrección en la condición
      Serial.print("Canal ");
      Serial.print(i);
      Serial.print(" : ");
      Serial.print(receivedValues[i]);
      Serial.print("\t");
    }
    Serial.println();
  }
}
