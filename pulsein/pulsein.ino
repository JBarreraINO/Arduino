void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
}

unsigned long int receiveIR() {
  // Wait for start pulse
  while(digitalRead(8) != LOW);
  if(pulseIn(8, HIGH, 20000) == 0) return 0;

  // Receive pulses
  unsigned long int result = 0;
  for(int i = 0; i < 32; i++) {
    int pulseLength = pulseIn(8, HIGH, 5000);
    if(pulseLength == 0) return 0;
    if(pulseLength > 1000) result |= (1UL<<i);
  }

  // Stop pulse
  while(digitalRead(8) != HIGH);

  return result;
} 

void loop() {
  Serial.println(receiveIR(), HEX);
}
