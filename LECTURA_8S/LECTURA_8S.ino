// ----------------------------
// Lectura de barra de 8 sensores multiplexada
// Formato de impresión en tabla
// Creado por Barrera.ino
// ----------------------------

#define s0      A0
#define s1      A1
#define s2      A2
#define OM      A3

int sensores[8];

void setup() {
  Serial.begin(115200);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);

}

void loop() {
  // ===== LECTURA DE LOS 8 SENSORES =====
  for (int i = 0; i < 8; i++) {
    digitalWrite(s0, i & 0x01);
    digitalWrite(s1, i & 0x02);
    digitalWrite(s2, i & 0x04);
    delayMicroseconds(5);
    sensores[i] = analogRead(OM);
  }

  // ===== IMPRESIÓN EN TABLA =====
  Serial.print("| ");
  for (int i = 0; i < 8; i++) {
    char buffer[12];
    sprintf(buffer, "S%d:%4d | ", i, sensores[i]); // %4d = ancho fijo 4
    Serial.print(buffer);
  }
  Serial.println();


}
