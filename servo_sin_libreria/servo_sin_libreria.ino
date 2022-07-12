
int servo =10;
void setup() {
 pinMode (servo, OUTPUT);
 Serial.begin(9600);
 // {==[=======> (0°) <=======]==}
 for (int Hz =0; Hz < 50 ;Hz++){      // repetimos la instruccion 50 veces
digitalWrite (servo,HIGH);
delayMicroseconds(700);                // llevamos a 0°
digitalWrite (servo,LOW);
delay(20);
Serial.println(Hz);  
 }
 delay(2000);
}
void loop() {
 //  {==[=======> (180°) <=======]==}
 for (int Hz =0; Hz < 50 ;Hz++){      // repetimos la instruccion 50 veces
digitalWrite (servo,HIGH); 
delayMicroseconds(2300);               // llevamos a 180°
digitalWrite (servo,LOW);
delay(18);
Serial.println(Hz);
 }
delay(2000);                          // retardo


}
