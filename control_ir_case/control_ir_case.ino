#include <IRremote.h>
int ReceptorIR = 2;
IRrecv irrecv (ReceptorIR);
decode_results Valor;
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  irrecv.enableIRIn();
  
}
void loop() {
  if(irrecv.decode(&Valor)){
    // es para averiguar el valor del botón 1 y 2
    Serial.print("0x");
    Serial.println(Valor.value, HEX);  // Mostrar en el monitor
    
    
    if(Valor.value==0xFFA25D ||Valor.value==0x5448BF41 ){digitalWrite(13,HIGH);}//0x5448BF41, 
     if(Valor.value==0xFF629D ||Valor.value==0x8570FF64 ){digitalWrite(12,HIGH);}//0x8570FF64
      if(Valor.value==0xFFE21D  || Valor.value==0xA8895765 ){digitalWrite(11,HIGH);}//0xA8895765
     if(Valor.value==0xFF22DD){digitalWrite(13,LOW);}
   if(Valor.value==0xFF02FD){digitalWrite(12,LOW);}
   if(Valor.value==0xFFC23D){digitalWrite(11,LOW);}




    
    delay(50);
    irrecv.resume();
  }
}
