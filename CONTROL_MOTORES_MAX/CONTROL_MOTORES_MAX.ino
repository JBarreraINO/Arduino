 #include <IngenieroMakerMax.h>
 //CREO EL OBJETO Control
 motores Control;
#define LED     13
#define GO  7 //10
#define BOTON 4 //12


void setup() {
  
 pinMode(LED   , OUTPUT);
  pinMode(GO, INPUT);
  pinMode(BOTON, INPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  
  WaitBoton();  
   Control.Motorde(30);
     Control.Motoriz(30);
   
}
void WaitBoton() {
  while (digitalRead(BOTON));
}
