#define NUM_CHANNELS 4

int pwmPins[NUM_CHANNELS] = {2, 3, 4, 5}; // Pines donde se reciben las señales PWM
int ppmPin = 6; // Pin donde se genera la señal PPM
unsigned int ppmValues[NUM_CHANNELS];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_CHANNELS; i++) {
    pinMode(pwmPins[i], INPUT);
  }
  pinMode(ppmPin, OUTPUT);
}

void loop() {
  // Leer los anchos de pulso de las señales PWM
  for (int i = 0; i < NUM_CHANNELS; i++) {
    ppmValues[i] = pulseIn(pwmPins[i], HIGH, 25000); // Timeout de 25 ms
  }

  // Generar la señal PPM
  digitalWrite(ppmPin, HIGH);
  delayMicroseconds(300); // Pausa para el pulso largo (inicio de la trama)
  
  for (int i = 0; i < NUM_CHANNELS; i++) {
    analogWrite(ppmPin, ppmValues[i]); // Generar pulsos PPM
    delayMicroseconds(300); // Pausa entre pulsos
  }

  digitalWrite(ppmPin, LOW); // Finalizar la trama
  delay(20); // Pausa antes de empezar la siguiente trama
}