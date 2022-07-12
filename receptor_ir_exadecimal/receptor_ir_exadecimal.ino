#include <IRremote.h>
int ReceptorIR = 7;
IRrecv irrecv (ReceptorIR);
decode_results Valor;
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // Inicializa el receptor
}
void loop() {
  if(irrecv.decode(&Valor)){
    // es para averiguar el valor del botón 1 y 2
    Serial.print("0x");
    Serial.println(Valor.value, HEX);  // Mostrar en el monitor
    delay(50);
    irrecv.resume(); // Se prepara para recibir el siguiente dato
  }
}
