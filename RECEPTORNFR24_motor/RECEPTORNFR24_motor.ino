#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Definimos los pines CE y CSN para el NRF24L01
#define CE_PIN 4  // D4 en ESP32
#define CSN_PIN 5 // D5 en ESP32

// Pines del puente H para motores
const int MOTOR1_IN1 = 27;  // Motor izquierdo
const int MOTOR1_IN2 = 26;  
const int MOTOR2_IN1 = 32;  // Motor derecho
const int MOTOR2_IN2 = 33;  

// Configuración de PWM
const int frecuencia = 5000;
const int resolucion = 8;
const int velMIN = 0;
const int velMAX = 1023;  // Valor máximo de PWM (10 bits)

// Creamos el objeto radio
RF24 radio(CE_PIN, CSN_PIN);

// Dirección de comunicación
const byte address[6] = "00001";

// Array para almacenar los valores recibidos
int receivedValues[14]; // Ajusta el tamaño según el número de datos enviados

void setup() {


  // Iniciamos el módulo NRF24L01
  if (!radio.begin()) {
    Serial.println("Error al iniciar el NRF24L01");
    while (1);
  }
  
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(45);
  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("Receptor listo");

  // Configurar canales PWM en ESP32
  ledcSetup(0, frecuencia, resolucion);
  ledcSetup(1, frecuencia, resolucion);
  ledcSetup(2, frecuencia, resolucion);
  ledcSetup(3, frecuencia, resolucion);

  ledcAttachPin(MOTOR1_IN1, 0);
  ledcAttachPin(MOTOR1_IN2, 1);
  ledcAttachPin(MOTOR2_IN1, 2);
  ledcAttachPin(MOTOR2_IN2, 3);
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedValues, sizeof(receivedValues));

    // Extraer el valor de velocidad desde el array recibido
    int velocidad = receivedValues[6];  // Valor del transmisor (ajusta si es otro índice)

    // Mapear la velocidad (-255 a 255) a valores PWM del ESP32 (0-1023)
    int velIzq = map(velocidad, 0, 4095, -255, 255);
    int velDer = velIzq;  // Se puede cambiar para diferenciar izquierda/derecha

    // Controlar los motores con los valores recibidos
    controlarMotores(velIzq, velDer);
  }
}

// Función para controlar los motores
void controlarMotores(int velIzq, int velDer) {
  ledcWrite(0, velIzq > 0 ? velIzq : 0);
  ledcWrite(1, velIzq < 0 ? -velIzq : 0);
  ledcWrite(2, velDer > 0 ? velDer : 0);
  ledcWrite(3, velDer < 0 ? -velDer : 0);
}
