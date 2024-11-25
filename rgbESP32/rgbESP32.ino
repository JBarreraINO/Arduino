const int redPin = 18;
const int greenPin = 5;
const int bluePin = 17;
const int brightnessPin = 16; // Pin para el MOSFET
// Definir los canales PWM para cada color y el brillo
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int brightnessChannel = 3; // Canal PWM para el MOSFET

const int freq = 5000; // Frecuencia PWM
const int resolution = 8; // Resolución PWM (8 bits: valores de 0 a 255)

// Pines del motor paso a paso
const int dirPin = 12;
const int stepPin = 14;
const int enablePin = 32;

// Pin del sensor de efecto Hall
const int hallSensorPin = 22;
// Definir estados
enum State {
  FIND_HOME,
  MOVE_TO_TARGET,
  IDLE
};

State currentState = FIND_HOME;
void setup() {
  // Configura los canales PWM
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  ledcSetup(brightnessChannel, freq, resolution);

  // Asigna los canales PWM a los pines correspondientes
  ledcAttachPin(redPin, redChannel);
  ledcAttachPin(greenPin, greenChannel);
  ledcAttachPin(bluePin, blueChannel);
  ledcAttachPin(brightnessPin, brightnessChannel);

  // Configura los pines del motor paso a paso
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
    pinMode(2, OUTPUT);

  // Configura el pin del sensor de efecto Hall
  pinMode(hallSensorPin, INPUT);

  // Habilita el motor paso a paso
  digitalWrite(enablePin, LOW);
 Serial.begin(9600);
}



void loop() {


  // Prueba de color RGB con el brillo máximo


  // Control del motor paso a paso
  

    switch (currentState) {
    case FIND_HOME:
      findHome();
  
  setBrightness(0); // Brillo máximo (0 es máximo brillo)
  setColor(0, 0, 100); // Rojo
      break;
    case MOVE_TO_TARGET:
  moveSteps(5400);
  digitalWrite(enablePin, HIGH);
delay(3000);
  digitalWrite(enablePin, LOW);
  currentState=IDLE;
      break;
    case IDLE:
  setBrightness(100); // Brillo máximo (0 es máximo brillo)
  setColor(255, 255, 100); // Rojo
  delay(2500);
 currentState=FIND_HOME;
      break;
  }
}

void setColor(int red, int green, int blue) {
  // Ajusta el brillo de cada color usando PWM
  ledcWrite(redChannel, red);
  ledcWrite(greenChannel, green);
  ledcWrite(blueChannel, blue);
}

void setBrightness(int brightness) {
  // Ajusta el brillo general de la tira LED usando el MOSFET
  // Invertir el valor de brillo
  ledcWrite(brightnessChannel, 255 - brightness);
}



void moveSteps(int steps) {


  // Configurar dirección de movimiento
  digitalWrite(dirPin, HIGH);

  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  // Mover el número especificado de pasos

       digitalWrite(2, HIGH);
    delay(100);
            digitalWrite(2, LOW);
    delay(100);
  Serial.println("Movimiento completado.");
}



void findHome() {
 

  // Configurar dirección hacia home
  digitalWrite(dirPin, HIGH);
  int Hall= digitalRead(hallSensorPin);
  // Mover el motor hasta que el sensor de efecto Hall esté en estado bajo (LOW)
  if (Hall == HIGH) {
 Serial.println("Buscando la posición inicial (home)...");
  for (int i = 0; i < 200; i++) {
  
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  
  }
    
    // Depuración: imprimir estado del sensor
    Serial.print("Sensor de efecto Hall: ");
    Serial.println(digitalRead(hallSensorPin));
  } 
  else {
    Serial.println("Posición inicial (home) encontrada.");
        digitalWrite(2, HIGH);
    delay(100);
            digitalWrite(2, LOW);
    delay(100);
           digitalWrite(2, HIGH);
    delay(100);
            digitalWrite(2, LOW);
    delay(100);
   currentState = MOVE_TO_TARGET;
  }
}





