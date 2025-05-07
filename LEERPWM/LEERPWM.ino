const int canalPins[] = {3, 10, 11,12,8};  // Pinos de entrada PWM
long canal[8];  // Array para almacenar las lecturas de los pines PWM

void setup() {
  Serial.begin(9600);  // Inicializa la comunicación serial
  
  // Configura los pines como entradas
  for (int i = 0; i < 5; i++) {
    pinMode(canalPins[i], INPUT);
  }

  // Genera una señal PWM de 38 kHz en el pin 9
  pinMode(9, OUTPUT);
  tone(9, 38000);  // Genera una señal de 38 kHz en el pin 9
}

void loop() {
  // Lee los valores de los pines PWM
  canal[0] = pulseIn(canalPins[0], HIGH);
  canal[1] = pulseIn(canalPins[1], HIGH);
  canal[2] = pulseIn(canalPins[2], HIGH);
  canal[3] = pulseIn(canalPins[3], HIGH);
  canal[4] = pulseIn(canalPins[4], HIGH);
  
  // Imprime las lecturas de los canales
  Serial.print(canal[0]);
  Serial.print("   -   ");
  Serial.print(canal[1]);
  Serial.print("    -    ");
  Serial.print(canal[2]);
  Serial.print("  -  ");
  Serial.print(canal[3]);
  Serial.print("  - ");
  Serial.print(canal[4]);
  Serial.println("   -  ");

  delay(100);  // Espera 100ms antes de hacer la siguiente lectura
}
