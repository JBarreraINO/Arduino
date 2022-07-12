int ML1=A1; //Micro Line Sensor Connected to Analog 1
int value; //We declared some variable for storing ML1 output

void setup() {
   Serial.begin(9600);
}

void loop() {
  value=analogRead(ML1); // It will be read between 0 to 1023 by Analog Reading
  Serial.print("Sensor Value: "); //It will write this words to serial monitor
  Serial.println(value); //Controller will send serial monitor to raw value.
  delay(100);  // we are adding 100 ms delay for delay at readings. 
  }

