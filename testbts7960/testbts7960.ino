// Definir los pines PWM para los motores
const int pwmMotor1A = 26;
const int pwmMotor1B = 27;
const int pwmMotor2A = 32;
const int pwmMotor2B = 33;

void setup() {
  // Configurar los pines PWM como salidas
  pinMode(pwmMotor1A, OUTPUT);
  pinMode(pwmMotor1B, OUTPUT);
  pinMode(pwmMotor2A, OUTPUT);
  pinMode(pwmMotor2B, OUTPUT);
}

void loop() {
  // Ejemplo de control de motor 1
  // Hacer que el motor 1 gire en una dirección
  analogWrite(pwmMotor1A, 255);  // Velocidad máxima
  analogWrite(pwmMotor1B, 0);
  delay(2000); // Girar por 2 segundos
  
  // Hacer que el motor 1 gire en la dirección opuesta
  analogWrite(pwmMotor1A, 0);
  analogWrite(pwmMotor1B, 255);  // Velocidad máxima
  delay(2000); // Girar por 2 segundos

  // Detener el motor 1
  analogWrite(pwmMotor1A, 0);
  analogWrite(pwmMotor1B, 0);
  delay(1000); // Pausa de 1 segundo

  // Ejemplo de control de motor 2
  // Hacer que el motor 2 gire en una dirección
  analogWrite(pwmMotor2A, 255);  // Velocidad máxima
  analogWrite(pwmMotor2B, 0);
  delay(2000); // Girar por 2 segundos
  
  // Hacer que el motor 2 gire en la dirección opuesta
  analogWrite(pwmMotor2A, 0);
  analogWrite(pwmMotor2B, 255);  // Velocidad máxima
  delay(2000); // Girar por 2 segundos

  // Detener el motor 2
  analogWrite(pwmMotor2A, 0);
  analogWrite(pwmMotor2B, 0);
  delay(1000); // Pausa de 1 segundo
}