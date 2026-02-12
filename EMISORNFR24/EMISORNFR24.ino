#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#include <Bluepad32.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
ControllerPtr myControllers[BP32_MAX_GAMEPADS];
#define CE_PIN 4
#define CSN_PIN 5
#define BUTTON_PIN 2
#define LED_PIN 13
#define POWER_PIN 17

int contador = 0;  // Variable del contador

int estado_pulsador_asc = 0;  // estado actual del pulsador
int lastButtonState_asc = 1;  // estado anterior del pulsador

const char* ssid = "BARRERA_RF_CONFIG";
const char* password = "12345678";
//const int analogPins[] = { 13, 15, 2, 21, 22, 14, 27, 12, 34, 35, 32, 33, 25, 26 };
const int analogPins[] = { 2, 25, 12, 27, 14, 26, 36, 39, 34, 35, 15 };
const int numSensors = sizeof(analogPins) / sizeof(analogPins[0]);
int sensorValues[numSensors];

int channel = 45;
int powerLevel = 3;
bool systemActive = true;
bool buttonHeld = false;
const byte address[6] = "00001";
RF24 radio(CE_PIN, CSN_PIN);
AsyncWebServer server(80);
Preferences preferences;
// HTML de la interfaz web
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Barrera RF - Configuracion</title>
  <style>
    body { 
      font-family: Arial; 
      text-align: center; 
      margin: 20px;
      background-color: #000000;
      color: #FFD700;
    }
    .header {
      background-color: #FFD700;
      color: #000000;
      padding: 20px;
      margin-bottom: 30px;
    }
    input, select {
      margin: 10px;
      padding: 8px;
      border: 2px solid #FFD700;
      background-color: #000000;
      color: #FFD700;
    }
    button {
      padding: 12px 25px;
      background-color: #FFD700;
      color: #000000;
      border: none;
      cursor: pointer;
      font-weight: bold;
      margin: 10px;
    }
    .instructions {
      border: 2px solid #FFD700;
      padding: 15px;
      margin: 20px auto;
      max-width: 500px;
      text-align: left;
    }
  </style>
</head>
<body>
  <div class="header">
    <h1>BARRERA RF PRO</h1>
    <h3>Sistema de Gestion Inalambrica</h3>
  </div>
  
  <form action="/save">
    <h2>Configuracion de Transmision</h2>
    <label>Canal (0-125):</label><br>
    <input type="number" name="channel" min="0" max="125" value="%CHANNEL%"><br>
    
    <label>Potencia de Transmision:</label><br>
    <select name="power">
      <option value="0" %P0%>Minima</option>
      <option value="1" %P1%>Baja</option>
      <option value="2" %P2%>Alta</option>
      <option value="3" %P3%>Maxima</option>
    </select><br>

    <label>Modo de Operacion:</label><br>
    <select name="mode">
      <option value="0" %MODE0%>Modo RC</option>
      <option value="1" %MODE1%>Modo Juego</option>
    </select><br>
    
    <button type="submit">Guardar Configuracion</button>
  </form>
  
  <div class="instructions">
    <h3>Instrucciones de Uso:</h3>
    <ul>
      <li>Canal: Seleccione entre 0 y 125 para evitar interferencias</li>
      <li>Potencia: Mayor potencia = Mayor alcance y consumo</li>
      <li>El sistema se reiniciara despues de guardar</li>
    </ul>
  </div>
  
  <form action="/apagar" onsubmit="return confirm('¿Apagar el sistema?');">
    <button type="submit" style="background-color:#ff0000;">APAGAR SISTEMA</button>
  </form>
</body>
</html>
)rawliteral";
bool configMode = false;
bool gameMode = false;  // Variable para guardar el modo seleccionado

int operationMode = 0;  // 0 = Modo RC, 1 = Modo Juego

void loadSettings() {
  preferences.begin("nrf24", true);
  channel = preferences.getInt("channel", 45);
  powerLevel = preferences.getInt("power", 3);
  operationMode = preferences.getInt("mode", 0);  // Cargar el modo de operación
  preferences.end();
  Serial.print("Canal guardado en EEPROM: ");
  Serial.println(channel);
  Serial.print("Potencia guardada en EEPROM: ");
  Serial.println(powerLevel);
  Serial.print("Modo de operacion: ");
  Serial.println(operationMode == 0 ? "Modo RC" : "Modo Juego");
}

void saveSettings(int ch, int pw, int mode) {
  preferences.begin("nrf24", false);
  preferences.putInt("channel", ch);
  preferences.putInt("power", pw);
  preferences.putInt("mode", mode);  // Guardar el modo de operación
  preferences.end();
  Serial.println("Configuracion guardada en EEPROM.");
}

String processor(const String& var) {
  if (var == "CHANNEL") return String(channel);
  else if (var == "P0") return (powerLevel == 0) ? "selected" : "";
  else if (var == "P1") return (powerLevel == 1) ? "selected" : "";
  else if (var == "P2") return (powerLevel == 2) ? "selected" : "";
  else if (var == "P3") return (powerLevel == 3) ? "selected" : "";
  else if (var == "MODE0") return (operationMode == 0) ? "selected" : "";
  else if (var == "MODE1") return (operationMode == 1) ? "selected" : "";
  return "";
}

void setupRadio() {
  radio.begin();

  if (radio.begin()) {
    Serial.println("iniciado correctamente");
  }

  if (!radio.begin()) {
    Serial.println("Error al iniciar el NRF24L01");
    while (1)
      ;
  }
  radio.setChannel(channel);
  radio.setPALevel((rf24_pa_dbm_e)powerLevel);
  radio.setDataRate(RF24_2MBPS);  // Velocidad de transmisión más alta (2 Mbps)
  radio.openWritingPipe(address);
  radio.stopListening();
}

// Procesador de plantillas HTML


void enterSleepMode() {
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(POWER_PIN, HIGH);  // Activa el pin de apagado
  Serial.println("Sistema en modo reposo");
  BP32.forgetBluetoothKeys();
  Serial.print("dispositivo olvidado");
  // Deshabilitar periféricos
  radio.powerDown();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  // Entrar en modo deep sleep
  esp_deep_sleep_start();
}

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  pinMode(LED_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(POWER_PIN, LOW);
  loadSettings();
  Serial.begin(115200);
  delay(3000);

  if (digitalRead(BUTTON_PIN) == LOW) {

    buttonHeld = true;
    operationMode = 0;
  }

  if (buttonHeld) {
    BP32.setup(&onConnectedController, &onDisconnectedController);
    configMode = true;
    digitalWrite(LED_PIN, HIGH);
    WiFi.softAP(ssid, password);
    Serial.println("\nModo Configuración Activado");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->send_P(200, "text/html", index_html, processor);
    });

    server.on("/save", HTTP_GET, [](AsyncWebServerRequest* request) {
      if (request->hasParam("channel")) channel = request->getParam("channel")->value().toInt();
      if (request->hasParam("power")) powerLevel = request->getParam("power")->value().toInt();
      if (request->hasParam("mode")) operationMode = request->getParam("mode")->value().toInt();
      saveSettings(channel, powerLevel, operationMode);
      request->send(200, "text/html", "<meta http-equiv='refresh' content='3;url=/' /><p>Configuración guardada. Reiniciando...</p>");
      delay(1000);
      ESP.restart();
    });

    server.on("/apagar", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->send(200, "text/html", "<meta http-equiv='refresh' content='3;url=/' /><p>El sistema se está apagando...</p>");
      delay(1000);
      enterSleepMode();
    });

    server.begin();
  } else if (operationMode == 1) {
    enterSleepMode();  // Entrar en modo de sueño si está en Modo Juego
  } else {
    loadSettings();
    setupRadio();
    Serial.println("Modo Transmision Activado");
    digitalWrite(LED_PIN, HIGH);
    configMode = false;
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);
  }
}

void loop() {
  static unsigned long lastBlink = 0;
  if (configMode) {
    if (millis() - lastBlink > 500) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      lastBlink = millis();
    }
  }

  if (!configMode) {


    if (millis() - lastBlink > 10) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      lastBlink = millis();
    }


    sensorValues[0] = analogRead(36);
    sensorValues[1] = analogRead(39);
    sensorValues[2] = analogRead(34);
    sensorValues[3] = analogRead(25);
    sensorValues[4] = analogRead(35);
    sensorValues[5] = analogRead(12);
    sensorValues[6] = analogRead(32);
    sensorValues[7] = analogRead(27);
    sensorValues[8] = analogRead(14);
    sensorValues[9] = analogRead(33);
    sensorValues[10] = analogRead(15);
    sensorValues[11] = analogRead(26);


    radio.write(&sensorValues, sizeof(sensorValues));

    //    Serial.println(ok ? "Datos enviados correctamente" : "Error al enviar los datos");
  }
}


void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
      // Additionally, you can get certain gamepad properties like:
      // Model, VID, PID, BTAddr, flags, etc.
      ControllerProperties properties = ctl->getProperties();
      Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                    properties.product_id);
      myControllers[i] = ctl;
      foundEmptySlot = true;
      break;
    }
  }
  if (!foundEmptySlot) {
    Serial.println("CALLBACK: Controller connected, but could not found empty slot");
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  bool foundController = false;

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
      myControllers[i] = nullptr;
      foundController = true;
      break;
    }
  }

  if (!foundController) {
    Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
  }
}
