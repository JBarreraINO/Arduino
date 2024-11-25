// Definición de los pines
const int pinBrillo = 16;
const int pinAzul = 17;
const int pinVerde = 5;
const int pinRojo = 18;

// Función para configurar los pines
void setup() {
  // Configuración de los pines como salidas
  pinMode(pinBrillo, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinRojo, OUTPUT);
  
  // Inicializar los pines en HIGH (apagado)
  digitalWrite(pinBrillo, HIGH);
  digitalWrite(pinAzul, HIGH);
  digitalWrite(pinVerde, HIGH);
  digitalWrite(pinRojo, HIGH);
}


// Función principal que se ejecuta en bucle
void loop() {
  // Encender Rojo con brillo, apagar Verde y Azul
digitalWrite(pinBrillo, HIGH);
digitalWrite(pinAzul, HIGH);
digitalWrite(pinVerde, HIGH);
digitalWrite(pinRojo, HIGH);
delay(5000);

digitalWrite(pinBrillo, LOW);
digitalWrite(pinAzul, HIGH);
digitalWrite(pinVerde, HIGH);
digitalWrite(pinRojo, HIGH);
delay(5000);


digitalWrite(pinBrillo, LOW);
digitalWrite(pinAzul, LOW);
digitalWrite(pinVerde, LOW);
digitalWrite(pinRojo, LOW);
delay(5000);

digitalWrite(pinBrillo, LOW);
digitalWrite(pinAzul, LOW);
digitalWrite(pinVerde, HIGH);
digitalWrite(pinRojo, HIGH);
delay(5000);


digitalWrite(pinBrillo, LOW);
digitalWrite(pinAzul, HIGH);
digitalWrite(pinVerde, HIGH);
digitalWrite(pinRojo, LOW);
delay(5000);

digitalWrite(pinBrillo, LOW);
digitalWrite(pinAzul, HIGH);
digitalWrite(pinVerde, LOW);
digitalWrite(pinRojo, HIGH);
delay(5000);


}

