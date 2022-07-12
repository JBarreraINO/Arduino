int LedBlink = 2;
int analogPin = A0;
int analogPin1 = A1;
long Strobo = 0;
long Strobo1 = 0;
void setup() {
  pinMode(LedBlink , OUTPUT);
    Serial.begin(9600);
}

void loop() {
  Strobo = analogRead(analogPin);
    Strobo1 = analogRead(analogPin1);
  digitalWrite(LedBlink , HIGH);   
  delay(Strobo1); 
  Serial.print("APAGADO = ");
  Serial.print(Strobo1);
  
  digitalWrite(LedBlink , LOW);  
  delay(Strobo); 
  Serial.print(" ENCENDIDO  = ");
  Serial.println(Strobo);
}
