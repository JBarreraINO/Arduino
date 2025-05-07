#include <Servo.h>  // Librería para controlar los servos

// Pines para las señales PWM de entrada
const int pwmPin1 = 2;
const int pwmPin2 = 3;

// Pines para controlar los servos
const int servoPin1 = 9;
const int servoPin2 = 10;

Servo servo1;
Servo servo2;

void setup() {
  pinMode(pwmPin1, INPUT);
  pinMode(pwmPin2, INPUT);

  servo1.attach(servoPin1); // Inicializa el primer servo
  servo2.attach(servoPin2); // Inicializa el segundo servo
 servo1.writeMicroseconds(1500);
 servo2.writeMicroseconds(1500);
}

void loop() {
  // Leer las señales PWM de entrada
  unsigned long pulse1 = pulseIn(pwmPin1, HIGH);
  unsigned long pulse2 = pulseIn(pwmPin2, HIGH);

  // Calcular la posición para el primer servo
  int servoPosition1;
  if (pulse1 >= 1500 && pulse1 <= 2000) {
    // Mapear de 1500 a 2000 -> 90 a 180 grados
    servoPosition1 = map(pulse1, 1500, 2000, 1500, 2000);
  } else if (pulse1 >= 1000 && pulse1 < 1495) {
    // Mapear de 1000 a 1500 -> 90 a 0 grados
    servoPosition1 = map(pulse1, 1000, 1500, 1000, 1500);
  } else {
    servoPosition1 = 1500; // Neutro si está fuera de rango
  }

  // Calcular la posición para el segundo servo
  int servoPosition2;
 if (pulse2 >= 1550 && pulse2 <= 2000) {
    // Mapear de 1500 a 2000 -> 90 a 180 grados
    servoPosition2 = map(pulse2, 1500, 2000, 1500, 2000);
  } else if (pulse2 >= 1000 && pulse2 < 1495) {
    // Mapear de 1000 a 1500 -> 90 a 0 grados
    servoPosition2 = map(pulse2, 1000, 1500, 1000, 1500);
  } else {
    servoPosition2 = 1500; // Neutro si está fuera de rango
  }

  // Mover los servos a las posiciones calculadas
  servo1.write(servoPosition1);
  servo2.write(servoPosition2);
 delay(1);

}
