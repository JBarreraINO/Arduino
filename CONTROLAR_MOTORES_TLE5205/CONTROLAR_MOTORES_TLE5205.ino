const int IN1_IZQUIERDA = 11;  // Pin de dirección IN1 para motor izquierdo
const int IN2_IZQUIERDA = 10;  // Pin de dirección IN2 para motor izquierdo
const int IN1_DERECHA = 9;  // Pin de dirección IN1 para motor derecho
const int IN2_DERECHA = 3;  // Pin de dirección IN2 para motor derecho

void setup() {
  pinMode(IN1_IZQUIERDA, OUTPUT);
  pinMode(IN2_IZQUIERDA, OUTPUT);
  pinMode(IN1_DERECHA, OUTPUT);
  pinMode(IN2_DERECHA, OUTPUT);
}

void controlarMotores(int velocidadMotorIzquierda, int velocidadMotorDerecha) {
  // Control de la dirección para el motor izquierdo
  if (velocidadMotorIzquierda > 0) {
    digitalWrite(IN1_IZQUIERDA, LOW); // Gira CW
    //digitalWrite(IN2_IZQUIERDA, LOW);
    analogWrite(IN2_IZQUIERDA, abs(velocidadMotorIzquierda));
  } else if (velocidadMotorIzquierda < 0) {
    digitalWrite(IN1_IZQUIERDA, HIGH); // Gira CCW
      //digitalWrite(IN2_IZQUIERDA, HIGH);
      analogWrite(IN2_IZQUIERDA, abs(velocidadMotorIzquierda));
  } else {
    digitalWrite(IN1_IZQUIERDA, HIGH); // Detén el motor izquierdo
    digitalWrite(IN2_IZQUIERDA, HIGH);
  }
  

  // Control de la dirección para el motor derecho
  if (velocidadMotorDerecha > 0) {
    digitalWrite(IN1_DERECHA, LOW); // Gira hacia adelante
    //digitalWrite(IN2_DERECHA, LOW);
    analogWrite(IN2_DERECHA, abs(velocidadMotorDerecha));
  } else if (velocidadMotorDerecha < 0) {
    //digitalWrite(IN2_DERECHA, HIGH);
  digitalWrite(IN1_DERECHA, HIGH); // Gira hacia atrás
    analogWrite(IN2_DERECHA, abs(velocidadMotorDerecha));
  } else {
    digitalWrite(IN1_DERECHA, HIGH); // Detén el motor derecho
    digitalWrite(IN2_DERECHA, HIGH);
  }

}

void loop() {
  // Aumenta la velocidad del motor izquierdo y disminuye la del motor derecho
  
  for (int velocidad = 0; velocidad <= 100; velocidad++) {
    controlarMotores(velocidad, 100 - velocidad);
    delay(50); // Pequeña pausa para suavizar el cambio de velocidad
  }


  // Aumenta la velocidad del motor izquierdo y disminuye la del motor derecho
  for (int velocidad = 0; velocidad <= 100; velocidad++) {
    controlarMotores(100-velocidad,velocidad);
    delay(50); // Pequeña pausa para suavizar el cambio de velocidad
  }



  for (int velocidad = 100; velocidad >= 0; velocidad--) {
    controlarMotores(-velocidad, -(100 - velocidad));
    delay(50); // Pequeña pausa para suavizar el cambio de velocidad
  }
    for (int velocidad = 100; velocidad >= 0; velocidad--) {
    controlarMotores(-(100 - velocidad),-velocidad );
    delay(50); // Pequeña pausa para suavizar el cambio de velocidad
  }


controlarMotores(0,0);


  // Espera 2 segundos con ambos motores detenidos
  delay(5000);
}