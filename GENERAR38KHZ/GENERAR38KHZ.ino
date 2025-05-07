// Configuración para generar 38 kHz en el pin 9 y leer los estados de los pines 4 y 8
void setup() {
  // Configuración del pin 9 como salida (para la señal de 38 kHz)
  pinMode(9, OUTPUT);
  
  // Configuración de los pines 4 y 8 como entradas (para sensores)
  pinMode(4, INPUT);
  pinMode(8, INPUT);

  // Configuración de Timer 1 para generar una señal de 38 kHz
  TCCR1A = _BV(COM1A0);  // Toggle OC1A (Pin 9) en cada comparación
  TCCR1B = _BV(WGM12) | _BV(CS10); // Modo CTC con prescaler 1
  OCR1A = 210; // Define el valor de comparación (16 MHz / (38 kHz * 2) - 1)

  // Inicia la comunicación serial para monitorear los pines 4 y 8
  Serial.begin(9600);
}

void loop() {
  // Lee el estado del pin 4 (HIGH o LOW)
  int pin4State = digitalRead(4);

  // Lee el estado del pin 8 (HIGH o LOW)
  int pin8State = digitalRead(8);

  // Envía el estado de los pines 4 y 8 al Serial Monitor
  Serial.print("Pin 4: ");
  Serial.print(pin4State);
  Serial.print(" | Pin 8: ");
  Serial.println(pin8State);

  // Agrega un pequeño retardo para evitar saturar el Serial Monitor
  delay(10);
}
