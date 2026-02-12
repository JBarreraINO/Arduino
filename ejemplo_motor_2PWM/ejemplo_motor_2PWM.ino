// ----------------------------
// Control de 2 motores en modo Phase/Enable (PWM dual)
// Ejemplo compatible con BTS7960, TLE5206, DRV8870, etc.
// Creado por Barrera.ino
// ----------------------------

// Motor A
#define PWM_A1  26   // PWM sentido 1 Motor A
#define PWM_A2  27   // PWM sentido 2 Motor A

// Motor B
#define PWM_B1  32   // PWM sentido 1 Motor B
#define PWM_B2  33   // PWM sentido 2 Motor B

// ============================
// Función PHASE_ENABLE
// ============================
// velocidadA: -255 a 255
// velocidadB: -255 a 255
void motorPHEN(int velocidadA, int velocidadB) {
  // ---- Motor A ----
  if (velocidadA > 0) {                 // CW
    analogWrite(PWM_A1, velocidadA);
    analogWrite(PWM_A2, 0);
  } 
  else if (velocidadA < 0) {            // CCW
    analogWrite(PWM_A1, 0);
    analogWrite(PWM_A2, -velocidadA);   // Magnitud
  } 
  else {                                // Stop
    analogWrite(PWM_A1, 0);
    analogWrite(PWM_A2, 0);
  }

  // ---- Motor B ----
  if (velocidadB > 0) {                 // CW
    analogWrite(PWM_B1, velocidadB);
    analogWrite(PWM_B2, 0);
  } 
  else if (velocidadB < 0) {            // CCW
    analogWrite(PWM_B1, 0);
    analogWrite(PWM_B2, -velocidadB);
  } 
  else {                                // Stop
    analogWrite(PWM_B1, 0);
    analogWrite(PWM_B2, 0);
  }
}

void setup() {
  pinMode(PWM_A1, OUTPUT);
  pinMode(PWM_A2, OUTPUT);
  pinMode(PWM_B1, OUTPUT);
  pinMode(PWM_B2, OUTPUT);

  // Parar motores al inicio
  motorPHEN(0, 0);
}

void loop() {
  // Ambos motores CW
  motorPHEN(200, 200);
  delay(2000);

  // Ambos motores CCW
  motorPHEN(-150, -150);
  delay(2000);

  // Un motor CW y otro CCW
  motorPHEN(200, -200);
  delay(2000);

  // Stop
  motorPHEN(0, 0);
  delay(2000);
}