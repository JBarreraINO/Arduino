#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0, 1); // RX | TX

void setup(){
  pinMode(9, OUTPUT);  // Este pin tirará del pin del Módulo BT 34 (pin de la llave) ALTO para cambiar el módulo al modo AT
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("SERINSY Somos la mejor empresa en el área de impresión 3D y tecnología");
  Serial.println("Ingrese sus comandos AT");
  BTSerial.begin(9600);  // su propia velocidad predeterminada de BT Module en el comando AT más
}

void loop(){

  // Sigue leyendo desde el Módulo BT y envíalo al Monitor Serial Arduino
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Sigue leyendo desde Arduino Serial Monitor y envíalo al módulo BT
  if (Serial.available())
    BTSerial.write(Serial.read());
}
