/*This example reads XMotion's Bottom Analog inputs
   There are A1 - A2 - A4 - A5
   Can be developed for other XMotion element readings
   www.Jsumo.com/xmotion
*/

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A4);
  int sensorValue4 = analogRead(A5);
  // print out the value you read:
  Serial.print("A1: ");
  Serial.print(sensorValue);
  Serial.print("         ");
  Serial.print("A2: ");
  Serial.print(sensorValue2);
  Serial.print("         ");
  Serial.print("A4: ");
  Serial.print(sensorValue3);
  Serial.print("         ");
  Serial.print("A5: ");
  Serial.println(sensorValue4);
  delay(100);        // delay in between reads for stability
}
