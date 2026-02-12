#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

// Pines
const int sensorPin = 34;
const int relePin   = 14;
const int ledPin    = 2;

// EEPROM
#define EEPROM_SIZE 16
#define ADDR_UMB_BAJO 0
#define ADDR_UMB_ALTO 4

// Variables de umbral
int umbralBajo;
int umbralAlto;

// Estados
bool bombaActiva = false;
bool modoAutomatico = true;
unsigned long tiempoInicioEstable = 0;
const unsigned long TIEMPO_ESTABLE_MS = 10000; // 10 segundos

bool dentroRangoEstable = false;
// Web Server
WebServer server(80);

// Red Wi-Fi AP
const char* ssid = "ESP32-BOMBA";
const char* password = "12345678";

// =========== FUNCIÓN DE PROMEDIO ===========
int leerPromedioSensor(int muestras) {
  long suma = 0;
  for (int i = 0; i < muestras; i++) {
    suma += analogRead(sensorPin);
    delay(5);
  }
  return suma / muestras;
}

// =========== HTML ===========
String generarPagina() {
  int valor = leerPromedioSensor(10);
  String estadoBomba = bombaActiva ? "ACTIVA" : "INACTIVA";
  String modo = modoAutomatico ? "Automático" : "Manual";

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Control de Bomba</title>";
  html += "<style>body{font-family:Arial;text-align:center;}button,input{padding:10px;margin:5px;}</style></head><body>";
  html += "<h2>ESP32 - Control de Bomba</h2>";
  html += "<p><strong>Modo:</strong> " + modo + "</p>";
  html += "<p><strong>Sensor:</strong> " + String(valor) + "</p>";
  html += "<p><strong>Estado de Bomba:</strong> " + estadoBomba + "</p>";
  html += "<p><strong>Umbral Bajo:</strong> " + String(umbralBajo) + "</p>";
  html += "<p><strong>Umbral Alto:</strong> " + String(umbralAlto) + "</p>";

  html += "<form action='/modo'><button>Cambiar Modo</button></form>";

  if (!modoAutomatico) {
    html += "<form action='/encender'><button>Encender Bomba</button></form>";
    html += "<form action='/apagar'><button>Apagar Bomba</button></form>";
  }

  html += "<hr><h3>Calibrar Umbrales</h3>";
  html += "<form action='/calibrar' method='POST'>";
  html += "Bajo: <input type='number' name='bajo' value='" + String(umbralBajo) + "'><br>";
  html += "Alto: <input type='number' name='alto' value='" + String(umbralAlto) + "'><br>";
  html += "<button type='submit'>Guardar</button></form>";

  html += "</body></html>";
  return html;
}

// =========== HANDLERS ===========
void handleRoot() {
  server.send(200, "text/html", generarPagina());
}

void handleModo() {
  modoAutomatico = !modoAutomatico;
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleEncender() {
  if (!modoAutomatico) {
    bombaActiva = true;
    digitalWrite(relePin, LOW);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleApagar() {
  if (!modoAutomatico) {
    bombaActiva = false;
    digitalWrite(relePin, HIGH);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void guardarUmbralesEEPROM(int bajo, int alto) {
  EEPROM.put(ADDR_UMB_BAJO, bajo);
  EEPROM.put(ADDR_UMB_ALTO, alto);
  EEPROM.commit();
}

void cargarUmbralesEEPROM() {
  EEPROM.get(ADDR_UMB_BAJO, umbralBajo);
  EEPROM.get(ADDR_UMB_ALTO, umbralAlto);

  if (umbralBajo < 100 || umbralBajo > 4000) umbralBajo = 2000;
  if (umbralAlto < 100 || umbralAlto > 4000) umbralAlto = 2300;
}

void handleCalibrar() {
  if (server.hasArg("bajo") && server.hasArg("alto")) {
    umbralBajo = server.arg("bajo").toInt();
    umbralAlto = server.arg("alto").toInt();
    guardarUmbralesEEPROM(umbralBajo, umbralAlto);
    Serial.println("Nuevos umbrales guardados en EEPROM");
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

// =========== SETUP ===========
void setup() {
  Serial.begin(115200);

  pinMode(relePin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH); delay(200);
    digitalWrite(ledPin, LOW); delay(200);
  }

  EEPROM.begin(EEPROM_SIZE);
  cargarUmbralesEEPROM();

  WiFi.softAP(ssid, password);
  Serial.println("Red AP iniciada");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/modo", handleModo);
  server.on("/encender", handleEncender);
  server.on("/apagar", handleApagar);
  server.on("/calibrar", handleCalibrar);
  server.begin();


   digitalWrite(relePin, HIGH);
      bombaActiva = false;
}

// =========== LOOP ===========
void loop() {
  server.handleClient();

  if (modoAutomatico) {
    int valor = leerPromedioSensor(10);

    int RANGO_CENTRAL_MIN = umbralBajo - 100;
    int RANGO_CENTRAL_MAX = umbralBajo + 100;

    // Control por umbrales
    if (!bombaActiva && valor < umbralBajo) {
      digitalWrite(relePin, LOW);
      bombaActiva = true;
    } else if (bombaActiva && valor > umbralAlto) {
      digitalWrite(relePin, HIGH);
      bombaActiva = false;
      tiempoInicioEstable = 0;
    }

    // Activación por estabilidad cercana al umbral bajo
    if (valor >= RANGO_CENTRAL_MIN && valor <= RANGO_CENTRAL_MAX) {
      if (!dentroRangoEstable) {
        dentroRangoEstable = true;
        tiempoInicioEstable = millis();
      } else if (millis() - tiempoInicioEstable >= TIEMPO_ESTABLE_MS && !bombaActiva) {
        digitalWrite(relePin, LOW);
        bombaActiva = true;
      }
20
      
    } else {
      dentroRangoEstable = false;
      tiempoInicioEstable = 0;
    }
  }
}