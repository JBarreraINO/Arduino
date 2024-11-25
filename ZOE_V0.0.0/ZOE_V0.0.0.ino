#include <WiFi.h>

// Configuración de la red
const char *ssid = "ESP32_AP";
const char *password = "qwerty12345";

const int ledRojo = 18;
const int ledVerde = 5;
const int ledAzul = 17;
// Pines del motor paso a paso
const int dirPin = 12;
const int stepPin = 14;
const int enablePin = 32;
int home=0;
// Pin del sensor de efecto Hall
const int hallSensorPin = 22;
// Definir estados

const int brightnessPin = 16; // Pin para el MOSFET
// setting PWM properties
const int freq = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int brightnessChannel = 3; // Canal PWM para el MOSFET
const int resolution = 8;

  int invertedRojo = 0;
   int invertedVerde =0;
   int invertedAzul = 0;
   
float brilloinverted=0000.1;

String wavelength;
int numero;
String r, g, b,n = "";

WiFiServer server(80);


enum State {
  FIND_HOME,
  MOVE_TO_TARGET,
  IDLE
};

void setup() {
  Serial.begin(115200);

  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  ledcSetup(brightnessChannel, freq, resolution);

  // Asigna los canales PWM a los pines correspondientes
  ledcAttachPin(ledRojo, redChannel);
  ledcAttachPin(ledVerde, greenChannel);
  ledcAttachPin(ledAzul, blueChannel);
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

  // Configurar el ESP32 como punto de acceso
  WiFi.softAP(ssid, password);
  Serial.println("Punto de acceso configurado.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
   mColor(0, 0, 0,0);

}

void mColor(int rojo, int verde, int azul, float brillo) {

if(brillo ==0 ) {brillo=1;}

brilloinverted=(brillo/255);

invertedRojo = rojo*brilloinverted;
invertedAzul= azul*brilloinverted;
invertedVerde = verde*brilloinverted;

   invertedRojo =round(255-invertedRojo);

   invertedVerde =round(255-invertedVerde);
   invertedAzul =round(255-invertedAzul);


  ledcWrite(redChannel, invertedRojo);
  ledcWrite(greenChannel, invertedVerde);
  ledcWrite(blueChannel, invertedAzul);
Serial.print("invertedRojo:");
Serial.println(invertedRojo);
Serial.print("verde:");
Serial.println(invertedVerde);
Serial.print("azul:");
Serial.println(invertedAzul);
Serial.print("brillo:");
Serial.println(brillo);
Serial.print("brilloINVERTED:");
Serial.println(brilloinverted);

}

void calcularRGB(float lambda) {
  float r, v, a, k = 255;
  //lambda = (float)(lambda1);

  if ((lambda >= 380) && (lambda <= 439)) {
    r = -1 * ((lambda - 440) / (440 - 380));
    v = 0;
    a = 1;
  }
  if ((lambda >= 440) && (lambda <= 489)) {
    r = 0;
    v = ((lambda - 440) / (490 - 440));
    a = 1;
  }
  if ((lambda >= 490) && (lambda <= 509)) {
    r = 0;
    v = 1;
    a = -1 * ((lambda - 510) / (510 - 490));
  }
  if ((lambda >= 510) && (lambda <= 579)) {
    r = ((lambda - 510) / (580 - 510));
    v = 1;
    a = 0;
  }
  if ((lambda >= 580) && (lambda <= 644)) {
    r = 1;
    v = -1 * ((lambda - 645) / (645 - 580));
    a = 0;
  }
  if ((lambda >= 645) && (lambda <= 780)) {
    r = 1;
    v = 0;
    a = 0;
  }

  mColor(k * r, k * v, k * a,n.toInt());
}


void loop() {
  WiFiClient client = server.available();  // Esperar a que un cliente se conecte
  if (client) {
    
              client.print("OK");
    // Continuar leyendo datos mientras el cliente esté conectado
    while (client.connected()) {
      if (client.available()) {
        char startChar = client.read();

        if (startChar == '%') {
          String request = "";  // Inicializar una cadena vacía para el mensaje real
          

          // Leer hasta encontrar otro '%'
          while (client.connected()) {
            if (client.available()) {
              char c = client.read();
              if (c == '%') {
                break;
              }
              request += c;
            }
          }

    Serial.println(request);
          ////////////////////////////////
          switch (request[0]) {

            case 'G':
              Serial.println(request);
              break;

            case 'R':
              findHome();
              break;

               case'1':
              findHome();
              home=0;
              digitalWrite(dirPin, LOW);
              home=1;
              moveSteps(2700);
              break;

               case'2':
              findHome();
              digitalWrite(dirPin, HIGH);
              home=2;
              moveSteps(2700);
              break;

            case 'M':
              wavelength = request.substring(1, 4);
              n = request.substring(10, 14);
              numero = wavelength.toInt();
              calcularRGB(numero);
              break;

            case 'A':
              r = request.substring(1, 4);
              g = request.substring(4, 7);
              b = request.substring(7, 10);
              n = request.substring(10, 14);
              mColor(r.toInt(), g.toInt(), b.toInt(),n.toInt());
              break;

            case 'W':
             n = request.substring(10, 14);
              mColor(255, 255, 100,n.toInt());
              break;
          }

          /////////////////////////////////////
           client.print("OK");
          // Enviar respuesta "OK" al cliente
        }
      }
    }
    // Cerrar la conexión con el cliente
    client.stop();
     mColor(0, 0, 0,0);
    Serial.println("Cliente desconectado.");
  }
}




void findHome() {
 while (1){
 Serial.println("buscando home");
  // Configurar dirección hacia home
  if(home==0) {  digitalWrite(dirPin, HIGH);}
  if(home==1) {  digitalWrite(dirPin, HIGH);}
    if(home==2) {  digitalWrite(dirPin,LOW);}



  
  int Hall= digitalRead(hallSensorPin);
  // Mover el motor hasta que el sensor de efecto Hall esté en estado bajo (LOW)
  if (Hall == HIGH ) {

  for (int i = 0; i < 200; i++) {
   Serial.println("motor");
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
    //home=1;
  }
    
    // Depuración: imprimir estado del sensor

  } 
  else if (Hall==LOW){
  
    Serial.println("Posición inicial (home) encontrada.");

    break;
   //currentState = MOVE_TO_TARGET;
  }
  }
}

void moveSteps(int steps) {


  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  // Mover el número especificado de pasos



}