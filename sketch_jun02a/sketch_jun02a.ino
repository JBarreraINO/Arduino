void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
int  current = millis();
  while (millis() < current + 2000)
  { 
    digitalWrite(13, HIGH); 
  }
  while (millis() < current + 2 * 2000)
  { 
    digitalWrite(13, LOW); 
  }
}

void loop() {
  // put your main code here, to run repeatedly:



}
