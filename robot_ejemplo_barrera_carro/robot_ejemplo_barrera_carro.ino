#include <Barreraino.h>
barrera Robot; // Declaración del objeto
#include <BarreraTB6612.h>
motores Control;

const int Trigger = 12; // Pin digital 12 para el Trigger del sensor
const int Echo = 13; // Pin digital 13 para el Echo del sensor
const int valorUmbral = 8; // Distancia mínima
const int s1 = A1; // Sensor 1
const int s2 = A2; // Sensor 2
const int sensorMetalA0 = A0; // Sensor inductivo A0
const int sensorMetalA3 = A3; // Sensor inductivo A3
const int buzzerPin = 9; // Pin para el buzzer

void setup() {
  // put your setup code here, to run once:
  Robot.unoBarrera();
  // Configuración de la consola serial
  Serial.begin(9600);
  
  pinMode(Trigger, OUTPUT); // Pin como salida
  pinMode(Echo, INPUT); // Pin como entrada
  digitalWrite(Trigger, LOW); // Inicializamos el pin con 0
  
  pinMode(s1, INPUT); // Pin como entrada
  pinMode(s2, INPUT); // Pin como entrada
  pinMode(sensorMetalA0, INPUT); // Pin del sensor inductivo A0
  pinMode(sensorMetalA3, INPUT); // Pin del sensor inductivo A3
  pinMode(buzzerPin, OUTPUT); // Pin del buzzer como salida
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Robot.Boton1()) {
    while (true) {
      long t; // Tiempo que demora en llegar el eco
      long d; // Distancia en centímetros
      
      digitalWrite(Trigger, HIGH);
      delayMicroseconds(10); // Enviamos un pulso de 10us
      digitalWrite(Trigger, LOW);
      
      t = pulseIn(Echo, HIGH); // Obtenemos el ancho del pulso
      d = t / 59; // Escalamos el tiempo a una distancia en cm
      
      int s1state = digitalRead(s1);
      int s2state = digitalRead(s2);
      int metalStateA0 = digitalRead(sensorMetalA0);
      int metalStateA3 = digitalRead(sensorMetalA3);

      Serial.println(s2state);
      
      // Comprobar si se detecta metal
      if (metalStateA0 == LOW || metalStateA3 == LOW) {
        digitalWrite(buzzerPin, HIGH); // Activar buzzer
      } else {
        digitalWrite(buzzerPin, LOW); // Desactivar buzzer
      }
      
      if (d > valorUmbral && s2state == HIGH) {
        Control.Motor(180, 180); // Controlar motor B y motor A
        delay(200);
      } 
      else if (d < valorUmbral || s2state == LOW) {
        Serial.println(s2state);
        Control.Motor(-180, -180); // Controlar motor B y motor A
        delay(500);
        Control.Motor(180, -180); // Controlar motor B y motor A
        delay(500);
      }
      else if (d < valorUmbral && s1state == HIGH) {
        Control.Motor(-80, -80); // Controlar motor B y motor A
        delay(500);
        Control.Motor(-180, 180); // Controlar motor B y motor A
        delay(500);
      }
      else if (d < valorUmbral && s1state == LOW) {
        if (random(0, 2) == 0) {
          Control.Motor(-180, 180); // Controlar motor B y motor A
        } else {
          Control.Motor(180, -180); // Controlar motor B y motor A
        }
      }
    }
  }
}