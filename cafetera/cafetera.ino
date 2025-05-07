#include <Wire.h>
#include <OLED_I2C.h>

OLED myOLED(21, 22);  // Pines SDA y SCL para el ESP32
extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t BigNumbers[];
extern uint8_t MediumNumbers[];

int menuOption = 0;          // Variable para el menú
float simulatedTemp = 72.5;  // Temperatura simulada
bool isRunning = false;      // Estado de la cafetera
unsigned long startTime;     // Hora de inicio
unsigned int brewTime = 60;  // Tiempo de preparación en segundos

const int buttonPin = 12;            // Pin donde se conecta el botón
const int resistencia_cafe = 5;      // Pin donde se conecta el botón
bool lastButtonState = HIGH;         // Estado anterior del botón
unsigned long lastDebounceTime = 0;  // Tiempo de última pulsación
unsigned long debounceDelay = 50;    // Retraso para evitar rebotes



unsigned int idleTime = 60000;   // Tiempo de inactividad antes de suspender (ms)
unsigned long lastActivityTime;  // Última actividad registrada
int cupsServed = 0;              // Contador de tazas servidas
int subMenuOption = 0;

int estadoBotonAnterior = HIGH;  // Estado anterior del botón (activo en HIGH por pull-up)
int estadoBotonActual = HIGH;    // Estado actual del botón
#include <DHT.h>                 //Cargamos la librería DHT
#define DHTTYPE DHT22            //Definimos el modelo del sensor DHT22
#define DHTPIN 4                 // Se define el pin D4 del ESP32 para conectar el sensor DHT22
DHT dht(DHTPIN, DHTTYPE, 22);
void setup() {
  // Inicialización de pantalla OLED

  myOLED.begin();
  myOLED.setFont(SmallFont);
  myOLED.clrScr();

  // Configuración del botón
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(resistencia_cafe, OUTPUT);

  // Inicialización del puerto serial para depuración
  Serial.begin(115200);
  Serial.println("Iniciando sistema...");
  digitalWrite(resistencia_cafe, HIGH);
  // Mensaje de bienvenida
  myOLED.print("Cafetera Inteligente", CENTER, 0);  // Título en la franja superior
  myOLED.print("Iniciando...", CENTER, 20);         // Contenido más abajo
  myOLED.update();
  delay(2000);  // Esperar 2 segundos

  // Limpiar pantalla
  myOLED.clrScr();
}

void loop() {
  handleButtonInput();  // Detectar pulsaciones del botón
  displayMenu();        // Mostrar el menú
  checkInactivity();
}

// Función para mostrar el menú principal
void displayMenu() {
  myOLED.clrScr();  // Limpiar pantalla
  myOLED.setFont(SmallFont);

  // Mostrar título en la franja superior
  myOLED.print("Menu Principal", CENTER, 0);

  // Opciones del menú desplazadas hacia abajo
  myOLED.print((menuOption == 0 ? "> Iniciar Cafe" : "Iniciar Cafe"), 10, 20);
  myOLED.print((menuOption == 1 ? "> Ver Temperatura" : "Ver Temperatura"), 10, 30);
  myOLED.print((menuOption == 2 ? "> Personalizar " : "Personalizar"), 10, 40);
  myOLED.print((menuOption == 3 ? "> Seleccionar Taza" : "SeleccionarTaza"), 10, 50);
  myOLED.update();

  // Mostrar estado en el monitor serial
  Serial.print("Menu Actual: ");
  Serial.println(menuOption);
}

// Función para manejar la interacción con el botón
void handleButtonInput() {
  bool currentButtonState = digitalRead(buttonPin);

  // Mostrar estado del botón en el monitor serial
  Serial.print("Estado del botón: ");
  Serial.println(currentButtonState == LOW ? "Presionado" : "No presionado");
  // Comprobar si el botón cambió de estado (con debounce)

  estadoBotonActual = digitalRead(12);  // Leer el estado actual del botón
  if (estadoBotonActual != estadoBotonAnterior) {
    lastDebounceTime = millis();  // Reiniciar el tiempo de debounce
  }
  // Detectar el momento en que el botón deja de presionarse
  if (estadoBotonAnterior == LOW && estadoBotonActual == HIGH) {
    menuOption++;
    Serial.print("Contador: ");
    Serial.println(menuOption);  // Mostrar el valor del contador
    delay(200);                  // Retardo para evitar rebotes del botón
  }

  estadoBotonAnterior = estadoBotonActual;  // Actualizar el estado anterior

  if (menuOption > 3) { menuOption = 0; }


  if (estadoBotonActual == LOW && millis() - lastDebounceTime > 1000) {
    executeOption();
    lastDebounceTime = millis();  // Evitar ejecuciones repetidas
  }
  // Otros códigos aquí si es necesario
}

// Función para ejecutar la opción seleccionada
void executeOption() {
  Serial.print("Ejecutando opción: ");
  Serial.println(menuOption);

  switch (menuOption) {
    case 0:  // Iniciar preparación
      startBrewing();
      break;
    case 1:  // Mostrar temperatura
      displayTemperature();
      break;
    case 2:  // Configurar tiempo
      configureBrewTime();
      break;
    case 3:  // Configurar tiempo
      selectCupSize();
      break;
  }
}

// Función para iniciar la preparación de café
void startBrewing() {
  myOLED.clrScr();
  float t = dht.readTemperature();
  myOLED.print("Temp:", LEFT, 0);
  myOLED.print(String(t) + "C", CENTER, 0);
  myOLED.print("Preparando Cafe...", CENTER, 20);
  myOLED.print("Tiempo: " + String(brewTime) + "s", CENTER, 35);
  myOLED.update();

  Serial.println("Preparando café...");
  isRunning = true;
  startTime = millis();
  while (millis() - startTime < brewTime * 1000) {

    digitalWrite(resistencia_cafe, LOW);
    // Temporizador visual
    unsigned int remainingTime = brewTime - (millis() - startTime) / 1000;
    myOLED.print(String(remainingTime) + "s restantes", CENTER, 45);
    myOLED.update();
    estadoBotonActual = digitalRead(buttonPin);  // Leer el estado actual del botón

    // Comprobar si el botón cambió de estado (con debounce)
    if (estadoBotonActual != estadoBotonAnterior) {
      lastDebounceTime = millis();  // Reiniciar el tiempo de debounce
    }


    // Detectar el momento en que el botón deja de presionarse
    if (estadoBotonAnterior == LOW && estadoBotonActual == HIGH) {

      Serial.print("Contador: ");
      Serial.println(brewTime);  // Mostrar el valor del contador
    }

    estadoBotonAnterior = estadoBotonActual;  // Actualizar el estado anterior



    // Si el botón se mantiene presionado más de 1 segundo, salir de la configuración
    if (estadoBotonActual == LOW && millis() - lastDebounceTime > 3000) {
      Serial.print("Configuración guardada. Tiempo final: ");
      Serial.println(brewTime);
      digitalWrite(resistencia_cafe, HIGH);



subMenuOption = 0;
menuOption = 0;          // Variable para el menú

      break;  // Salir del bucle para finalizar la configuración
    }


    estadoBotonAnterior = estadoBotonActual;  // Actualizar el estado anterior del botón
  }

  myOLED.clrScr();
  myOLED.print("Cafe Listo!", CENTER, 25);
  myOLED.update();
  Serial.println("Café listo.");
  digitalWrite(resistencia_cafe, HIGH);
  subMenuOption = 0;
  menuOption = 0;          // Variable para el menú
  cupsServed +=1;              // Contador de tazas servidas
  isRunning = false;
  delay(2000);

}

// Función para mostrar la temperatura simulada
void displayTemperature() {
  myOLED.clrScr();
  float t = dht.readTemperature();          //
  myOLED.print("Temperatura:", CENTER, 0);  // Título en la franja superior
  myOLED.setFont(BigNumbers);
  myOLED.print(String(t), CENTER, 25);  // Datos desplazados hacia abajo
  myOLED.print("C", 120, 25);           // Datos desplazados hacia abajo
  myOLED.update();
  Serial.print("Temperatura simulada: ");
  Serial.println(t);
  delay(3000);
}

// Función para configurar el tiempo de preparación
void configureBrewTime() {
  myOLED.clrScr();
  myOLED.print("Tiempo Actual:", CENTER, 0);         // Título en la franja superior
  myOLED.print(String(brewTime) + "s", CENTER, 20);  // Datos desplazados hacia abajo
  myOLED.print("Mantén presionado", CENTER, 40);
  myOLED.update();

  Serial.print("Tiempo actual de preparación: ");
  Serial.println(brewTime);
  delay(1000);
  while (true) {
    estadoBotonActual = digitalRead(buttonPin);  // Leer el estado actual del botón

    // Comprobar si el botón cambió de estado (con debounce)
    if (estadoBotonActual != estadoBotonAnterior) {
      lastDebounceTime = millis();  // Reiniciar el tiempo de debounce
    }


    // Detectar el momento en que el botón deja de presionarse
    if (estadoBotonAnterior == LOW && estadoBotonActual == HIGH) {
      brewTime += 10;
      Serial.print("Contador: ");
      Serial.println(brewTime);  // Mostrar el valor del contador
    }

    estadoBotonAnterior = estadoBotonActual;  // Actualizar el estado anterior



    // Si el botón se mantiene presionado más de 1 segundo, salir de la configuración
    if (estadoBotonActual == LOW && millis() - lastDebounceTime > 2000) {
      Serial.print("Configuración guardada. Tiempo final: ");
      Serial.println(brewTime);
      break;  // Salir del bucle para finalizar la configuración
    }


    estadoBotonAnterior = estadoBotonActual;  // Actualizar el estado anterior del botón

    // Actualizar la pantalla OLED con el nuevo tiempo
    myOLED.clrScr();
    myOLED.print("Nuevo Tiempo:", CENTER, 0);
    myOLED.print(String(brewTime) + "s", CENTER, 20);
    myOLED.update();
  }
}

// Función para seleccionar el tamaño de la taza
void selectCupSize() {

  estadoBotonActual = digitalRead(buttonPin);  // Leer el estado actual del botón
  myOLED.clrScr();
  myOLED.print("Seleccionar Taza", CENTER, 0);
  myOLED.print((subMenuOption == 0 ? "> Corto" : "  Corto"), 10, 20);
  myOLED.print((subMenuOption == 1 ? "> Medio" : "  Medio"), 10, 30);
  myOLED.print((subMenuOption == 2 ? "> Largo" : "  Largo"), 10, 40);
  myOLED.update();



  while (true) {

    myOLED.print("Seleccionar Taza", CENTER, 0);
    myOLED.print((subMenuOption == 0 ? "> Corto" : "  Corto"), 10, 20);
    myOLED.print((subMenuOption == 1 ? "> Medio" : "  Medio"), 10, 30);
    myOLED.print((subMenuOption == 2 ? "> Largo" : "  Largo"), 10, 40);
    myOLED.update();

    estadoBotonActual = digitalRead(buttonPin);  // Leer el estado actual del botón

    // Comprobar si el botón cambió de estado (con debounce)
    if (estadoBotonActual != estadoBotonAnterior) {
      lastDebounceTime = millis();  // Reiniciar el tiempo de debounce
    }


    // Detectar el momento en que el botón deja de presionarse
    if (estadoBotonAnterior == LOW && estadoBotonActual == HIGH) {
      subMenuOption++;
      if (subMenuOption > 2) subMenuOption = 0;
      delay(200);
      Serial.print("Contador: ");
      Serial.println(brewTime);  // Mostrar el valor del contador
    }

    estadoBotonAnterior = estadoBotonActual;  // Actualizar el estado anterior



    // Si el botón se mantiene presionado más de 1 segundo, salir de la configuración
    if (estadoBotonActual == LOW && millis() - lastDebounceTime > 2000) {
      Serial.print("Configuración guardada. Tiempo final: ");
      Serial.println(brewTime);
        myOLED.clrScr();
         myOLED.update();
  setBrewTime(subMenuOption);
      break;  // Salir del bucle para finalizar la configuración
    }
  }
 
}

// Función para establecer el tiempo según el tamaño de la taza
void setBrewTime(int option) {
  switch (option) {
    case 0: brewTime = 30; break;  // Café corto
    case 1: brewTime = 60; break;  // Café medio
    case 2: brewTime = 90; break;  // Café largo
  }
  startBrewing();
}
void checkInactivity() {
  if (millis() - lastActivityTime > idleTime) {
      float t = dht.readTemperature(); 
      myOLED.clrScr();
      myOLED.print("Temperatura Actual", CENTER, 0);   // Mensaje principal
      myOLED.printNumF(t, 1, CENTER, 30); // Mostrar temperatura con 1 decimal
      myOLED.print("C", CENTER + 20, 30);             // Unidad de temperatura
      myOLED.update();
      delay(3000);

    myOLED.clrScr();
    myOLED.print("Cafetera Suspendida", CENTER, 0);  // Mensaje principal
    myOLED.print("Tazas totales: ", CENTER, 30);     // Etiqueta para tazas
    myOLED.printNumI(cupsServed , CENTER, 45);         // Número de tazas totales
    myOLED.update();
  
    delay(3000);




    while (digitalRead(buttonPin) == HIGH) {
      // Esperar actividad para salir de suspensión
    }
    lastActivityTime = millis();  // Reiniciar el tiempo de actividad
  }
}
