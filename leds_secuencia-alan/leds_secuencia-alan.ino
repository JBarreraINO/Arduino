// Pines de los LEDs
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

// Pin del pulsador
const int buttonPin = 7;

// Variables para el estado del sistema
int currentState = 0;             // Estado inicial (0 = LED 1)
int lastButtonState = HIGH;       // Comienza en alto debido a INPUT_PULLUP
bool ledOn = false;
unsigned long ledOnTime = 0;      // Tiempo en que el LED fue encendido
unsigned long ledDuration = 5000; // Duración del LED encendido en milisegundos

void setup() {
  // Configuramos los pines de los LEDs como salida
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Configuramos el pin del pulsador como entrada con pullup
  pinMode(buttonPin, INPUT_PULLUP);

  // Inicializamos los LEDs apagados
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop() {
  // Leemos el estado del pulsador
  int reading = digitalRead(buttonPin);

  // Detectamos un cambio de estado en el botón
  if (reading == LOW && lastButtonState == HIGH) { 
    currentState++;
    if (currentState > 2) {
      currentState = 0;
    }

    // Encendemos el LED correspondiente y guardamos el tiempo de encendido
    if (currentState == 0) {
      encenderLed(led1);
    } else if (currentState == 1) {
      encenderLed(led2);
    } else if (currentState == 2) {
      encenderLed(led3);
    }
  }

  // Si el LED está encendido y han pasado los 5 segundos, apagamos el LED
  if (ledOn && (millis() - ledOnTime >= ledDuration)) {
    apagarLeds();
    ledOn = false;
  }

  // Guardamos el último estado del botón
  lastButtonState = reading;
}

void encenderLed(int led) {
  apagarLeds();                // Apagamos todos los LEDs antes de encender el siguiente
  digitalWrite(led, HIGH);      // Encendemos el LED actual
  ledOn = true;
  ledOnTime = millis();         // Guardamos el tiempo en que se encendió el LED
}

void apagarLeds() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}
