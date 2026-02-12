
#define SERIAL_COM_BAUD_RATE 115200

void consoleInit() {
  if (isConsoleMode) {
    Serial.begin(SERIAL_COM_BAUD_RATE);
    Serial.println();
    Serial.println("======================================================");
    Serial.println("======================================================");
  }
}

void serialComStop() {
  Serial.end();
}