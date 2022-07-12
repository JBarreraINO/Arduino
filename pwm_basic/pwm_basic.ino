int digPin = 5; // pin digital 10
int incomingByte = 0;
void setup() 
{
 Serial.begin(9600); 
pinMode(10,OUTPUT);      
pinMode(13,OUTPUT);    // no se declara el modo del pin 
   analogWrite(10,0);delay(5000);             //como salida analógica
}

void loop() {
 analogWrite(10,0);
   analogWrite(10,255); // Señal PWM a 50% en el PIN 10
   digitalWrite(13,HIGH);
  
}
