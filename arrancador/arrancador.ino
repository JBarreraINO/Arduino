#include <IRremote.h>
IRrecv irrecv(2);
decode_results Valor;
int rdy = 0;
int go = 1;
int Lpb3 = 3;
int Lpb4 = 4;
void setup() {

  pinMode(rdy, OUTPUT);
  pinMode(go, OUTPUT);
  pinMode(Lpb3, OUTPUT);
  pinMode(Lpb4, OUTPUT);
  irrecv.enableIRIn();
  digitalWrite(Lpb4, HIGH);
}
void loop() {
  if (irrecv.decode(&Valor)) {

    if (Valor.value == 0x8570FF64)     //RDY
    {
      digitalWrite(go, LOW);
      digitalWrite(rdy, LOW);
      digitalWrite(Lpb3, LOW);
      digitalWrite(Lpb4, HIGH);
    } else if (Valor.value == 0x5448BF41 )  //RST 
    {
      digitalWrite(go, LOW);
      digitalWrite(rdy, HIGH);
      digitalWrite(Lpb3, HIGH);
      digitalWrite(Lpb4, HIGH);
    } else if (Valor.value == 0xA8895765)  //GO
    {
      digitalWrite(go, HIGH);
      digitalWrite(rdy, LOW);
      digitalWrite(Lpb3, HIGH);
      digitalWrite(Lpb4, LOW);
    }

    irrecv.resume();
  }
}