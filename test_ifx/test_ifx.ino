// ----------------------------
// Control de 2 motores IFX9201 en modo DIR
// Creado por Barrera.ino
// ----------------------------

// Motor A
#define DIR_A  32   // Pin dirección Motor A
#define PWM_A  33   // Pin PWM Motor A

// Motor B
#define DIR_B  27   // Pin dirección Motor B
#define PWM_B  26   // Pin PWM Motor B

// ============================
// Función DIR para dos motores
// ============================
// velocidadA: -255 a 255
// velocidadB: -255 a 255
void motorDIR(int velocidadA, int velocidadB) {
  // ---- Motor A ----
  if (velocidadA > 0) {                // CW
    digitalWrite(DIR_A, HIGH);
    analogWrite(PWM_A, velocidadA);
  } 
  else if (velocidadA < 0) {           // CCW
    digitalWrite(DIR_A, LOW);
    analogWrite(PWM_A, -velocidadA);   // Magnitud
  } 
  else {                               // Stop
    analogWrite(PWM_A, 0);
  }

  // ---- Motor B ----
  if (velocidadB > 0) {                // CW
    digitalWrite(DIR_B, HIGH);
    analogWrite(PWM_B, velocidadB);
  } 
  else if (velocidadB < 0) {           // CCW
    digitalWrite(DIR_B, LOW);
    analogWrite(PWM_B, -velocidadB);
  } 
  else {                               // Stop
    analogWrite(PWM_B, 0);
  }
}

void setup() {
  pinMode(DIR_A, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  // Frenar ambos motores al inicio
  motorDIR(0, 0);
}

void loop() {
  // Ejemplo: ambos motores CW
  motorDIR(200, 200);
  delay(2000);

  // Ejemplo: ambos motores CCW
  motorDIR(-150, -150);
  delay(2000);

  // Ejemplo: un motor CW y otro CCW
  motorDIR(200, -200);
  delay(2000);

  // Frenar
  motorDIR(0, 0);
  delay(2000);
}