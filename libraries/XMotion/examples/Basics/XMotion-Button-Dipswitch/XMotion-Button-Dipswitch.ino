#define DipSwitch1 5 // Dipswitch 1 tied to Digital 5
#define DipSwitch2 6 // Dipswitch 2 tied to Digital 6
#define DipSwitch3 7 // Dipswitch 3 tied to Digital 7
#define Start 10 // Button tied to Digital 10

void setup() {
  pinMode(DipSwitch1, INPUT); //Dipswitch 1 Declared as Input
  pinMode(DipSwitch2, INPUT); //Dipswitch 2 Declared as Input
  pinMode(DipSwitch3, INPUT); //Dipswitch 3 Declared as Input
  pinMode(Start, INPUT); //Button Declared as Input

  digitalWrite(DipSwitch1, HIGH); // Dipswitch Inputs are High (Pull-up made)
  digitalWrite(DipSwitch2, HIGH);
  digitalWrite(DipSwitch3, HIGH);

  Serial.begin(9600); //Serial Interface started with 9600 bits per sec.
}

void loop() {
  Serial.print("Button State:"); //We are writing this statement to serial Monitor
  Serial.print(digitalRead(Start)); //digital reading of button
  Serial.print("  ");
  Serial.print("Dipswitch Inputs:"); 
  Serial.print(digitalRead(DipSwitch1)); // digital reading of dipswitches
  Serial.print(digitalRead(DipSwitch2));
  Serial.println(digitalRead(DipSwitch3));
  delay(100);
}
