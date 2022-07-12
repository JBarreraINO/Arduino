#include <IRremote.h>
int ReceptorIR = 2;
IRrecv irrecv (ReceptorIR);
decode_results Valor;
int MotorA1=3;
int MotorA2=5;
int MotorB1=10;
int MotorB2=11;
void setup() {
  Serial.begin(9600);
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2,OUTPUT);
  pinMode(MotorB1,OUTPUT);
  pinMode(MotorB2,OUTPUT);
  irrecv.enableIRIn();
  
}
void loop() {
  
  if(irrecv.decode(&Valor)){
    // es para averiguar el valor del botón 1 y 2
    Serial.print("0x");
    Serial.println(Valor.value, HEX);  // Mostrar en el monitor   
    
    if(Valor.value==0xFF18E7 || Valor.value==0x5448BF41 )
    {analogWrite(MotorA1,255 );
     analogWrite(MotorB1,255 );
     analogWrite(MotorA2,0);
     analogWrite(MotorB2,0);
     delay(1000);
   }
   
  

    irrecv.resume();
  
}
}//loop
