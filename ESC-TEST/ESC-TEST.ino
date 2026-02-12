#include <Servo.h>

Servo esc;
const int escPin = 2;  // Señal del ESC en el pin D9
int velocidad = 1000;  // Valor inicial (reposo)

void setup() {
  esc.attach(escPin);                // Asignar pin al objeto
  esc.writeMicroseconds(velocidad); // Enviar señal inicial de reposo
  Serial.begin(9600);
  Serial.println("Escribe un valor entre 1000 y 2000 para controlar el ESC:");
  delay(3000); // Espera para armado del ESC
}

void loop() {
  if (Serial.available()) {
    int entrada = Serial.parseInt(); // Lee valor enviado por Serial

    if (entrada >= 1000 && entrada <= 2000) {
      velocidad = entrada;
      esc.writeMicroseconds(velocidad);
      Serial.print("PWM enviado: ");
      Serial.println(velocidad);
    } else {
      Serial.println("Valor fuera de rango (1000-2000)");
    }
  }
}
