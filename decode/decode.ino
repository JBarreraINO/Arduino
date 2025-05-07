#include <IRremote.h>

const int RECV_PIN = 2;  // Pin donde conectamos el receptor IR
IRrecv irrecv(RECV_PIN);
decode_results results;
#define rojo 13
#define verde 12
#define azul 13


void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn();  // Iniciar el receptor IR
    Serial.println("Receptor IR listo...");

    pinMode(verde,OUTPUT);
    pinMode(rojo,OUTPUT);
    pinMode(azul,OUTPUT);


}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.print("Código recibido: ");
        Serial.println(results.value, HEX);  // Imprimir código en hexadecimal
        irrecv.resume();  // Recibir el siguiente código
    }


    if (results.value==0x19DF){
digitalWrite(verde, HIGH);

    }

    
    if (results.value==0x11DE){
digitalWrite(verde, LOW);
digitalWrite(rojo, HIGH);


    }


       if (results.value==0x12DE){
digitalWrite(verde, LOW);
digitalWrite(rojo, LOW);


    }







}