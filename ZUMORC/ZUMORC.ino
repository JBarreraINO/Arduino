
//DEFINICIONES
#include <Wire.h>
#include <OLED_I2C.h>
OLED myOLED(21, 22);
extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t BigNumbers[];
extern uint8_t MediumNumbers[];
extern uint8_t logo[];
// Configuración PWM
const int frecuencia = 5000;
const int resolucion = 8;
const int velMIN = 0;

// Declaración pines motores
int MOTOR1_IN1 = 27;  // PWM izquierdo
int MOTOR1_IN2 = 26;  // PWM izquierdo
int MOTOR2_IN1 = 32;  // PWM derecho
int MOTOR2_IN2 = 33;  // PWM derecho
bool receptorActivo = false; // <--- NUEVA VARIABLE DE ESTADO
const int canalMovimiento = 13; // Canal 2 del receptor (adelante/atrás)
const int canalDireccion = 25;  // Canal 1 del receptor (giro izquierda/derecha)

// Constantes del rango PWM
const int PWM_MIN = 1000;
const int PWM_NEUTRO = 1500;
const int PWM_MAX = 2000;

void setup() {
  controlarMotores(0, 0);
  Wire.begin();
  pinMode(canalMovimiento, INPUT);
  pinMode(canalDireccion, INPUT);
  myOLED.begin();
  myOLED.clrScr();
  myOLED.drawBitmap(0, 0, logo, 128, 64);
  myOLED.update();
  myOLED.setFont(SmallFont);
  Serial.begin(9600);
  // Configurar PWM para motores
  ledcSetup(0, frecuencia, resolucion);
  ledcSetup(1, frecuencia, resolucion);
  ledcSetup(2, frecuencia, resolucion);
  ledcSetup(3, frecuencia, resolucion);

  ledcAttachPin(MOTOR1_IN1, 0);
  ledcAttachPin(MOTOR1_IN2, 1);
  ledcAttachPin(MOTOR2_IN1, 2);
  ledcAttachPin(MOTOR2_IN2, 3);

    while (!receptorActivo) {
      controlarMotores(0, 0);
    int sMovimiento = pulseIn(canalMovimiento, HIGH, 25000); // timeout 25ms
    int sDireccion = pulseIn(canalDireccion, HIGH, 25000);

    if (sMovimiento >= PWM_MIN && sMovimiento <= PWM_MAX &&
        sDireccion >= PWM_MIN && sDireccion <= PWM_MAX) {
      receptorActivo = true;
      Serial.println("Receptor detectado. Iniciando...");
      myOLED.clrScr();
      myOLED.print("Receptor OK", CENTER, 28);
      myOLED.update();
      delay(1000);
    } else {
      Serial.println("Esperando receptor...");
      myOLED.clrScr();
      myOLED.print("Esperando", CENTER, 28);
      myOLED.update();
      delay(500);
    }
  }
}

void controlarMotores(int velIzq, int velDer) {
  ledcWrite(0, velIzq > 0 ? velIzq : 0);
  ledcWrite(1, velIzq < 0 ? -velIzq : 0);
  ledcWrite(2, velDer > 0 ? velDer : 0);
  ledcWrite(3, velDer < 0 ? -velDer : 0);
  /*
  myOLED.setFont(TinyFont);
  myOLED.print("     ", LEFT, 32);
  myOLED.print("     ", RIGHT, 32);
  myOLED.printNumI(velIzq, LEFT, 32);
  myOLED.printNumI(velDer, RIGHT, 32);
  myOLED.update();*/
}

int leerPWM(int pin) {
  unsigned long pulso = pulseIn(pin, HIGH); // Leer pulso PWM
  if (pulso < PWM_MIN) pulso = PWM_MIN;
   if (pulso >PWM_MAX) pulso = PWM_MAX;
  if (pulso >= PWM_MIN && pulso <= PWM_MAX) {
    return map(pulso, PWM_MIN, PWM_MAX, -255, 255); // Mapear de PWM a rango de velocidad
  }
  return 0; // Si no está dentro del rango, retorna 0
}

void loop() {
  // Leer señales PWM del receptor
  int velocidad = leerPWM(canalMovimiento); // Canal de movimiento adelante/atrás
  int direccion = leerPWM(canalDireccion);  // Canal de dirección izquierda/derecha

  // Calcular velocidad de cada motor para mezclar movimiento y giro
  int velIzq = velocidad + direccion; // Motor izquierdo
  int velDer = velocidad - direccion; // Motor derecho

  // Limitar velocidades dentro del rango permitido
  velIzq = constrain(velIzq, -255, 255);
  velDer = constrain(velDer, -255, 255);

  // Controlar los motores
  controlarMotores(velIzq, velDer);

  delay(1); // Pequeño retraso para suavizar la respuesta
}
