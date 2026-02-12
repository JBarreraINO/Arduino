// --- CONFIG TIMER2 para PWM en pin 11 ---
void setup() {
  pinMode(11, OUTPUT);

  // Reset registros Timer2
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  // Fast PWM con TOP en OCR2A
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  TCCR2B |= (1 << WGM22);

  // Clear OC2B on compare match
  TCCR2A |= (1 << COM2A1);

  // Prescaler 1024
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);

  // TOP para 50Hz (20ms)
  OCR2A = 312;

  // --- CALIBRACIÓN DEL ESC ---
  Serial.begin(9600);
  Serial.println("Iniciando calibracion ESC...");

  // Paso 1: mandar señal máxima
  OCR2B = 32;   // ~2000us
  Serial.println("Señal MAXIMA enviada, conecta la bateria del ESC ahora!");
  delay(6000);  // espera pitido

  // Paso 2: mandar señal mínima
  OCR2B = 16;   // ~1000us
  Serial.println("Señal MINIMA enviada, esperando confirmacion...");
  delay(3000);  // espera pitido
  Serial.println("Calibracion completada.");
}

void loop() {
  // Aquí puedes manejar el ESC normalmente
  // Ejemplo: poner en neutro
  OCR2B = 24;  // ~1500us

  delay(2000);

  // Acelerar
  OCR2B = 28;  // ~1750us
  delay(2000);

  // Detener
  OCR2B = 16;  // ~1000us
  delay(2000);
}
