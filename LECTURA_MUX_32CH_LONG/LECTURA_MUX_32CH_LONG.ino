/*


#define s0 8  // Sensor Selection pin S0.
#define s1 7   // Sensor Selection pin S1.
#define s2 6   // Sensor Selection pin S2.
#define s3 5   // Sensor Selection pin S3.
#define s4 4   // Sensor Selection pin S4.
#define OM A5  // Output pin of the multiplexer.
*/


#define s0 A2  // Sensor Selection pin S0.
#define s1 5   // Sensor Selection pin S1.
#define s2 6   // Sensor Selection pin S2.
#define s3 7   // Sensor Selection pin S3.
#define s4 8   // Sensor Selection pin S4.
#define OM A5  // Output pin of the multiplexer.


int sensores[27];

void setup() {
  Serial.begin(115200);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
}

void loop() {
  for (int i = 0; i < 27; i++) {
    // Set the multiplexer channel
digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, LOW); digitalWrite(s4, LOW); sensores[0] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, LOW); digitalWrite(s4, LOW); sensores[1] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, HIGH); digitalWrite(s2, LOW); digitalWrite(s3, LOW); digitalWrite(s4, LOW); sensores[2] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, HIGH); digitalWrite(s2, LOW); digitalWrite(s3, LOW); digitalWrite(s4, LOW); sensores[3] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, HIGH); digitalWrite(s3, LOW); digitalWrite(s4, LOW); sensores[4] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, LOW); digitalWrite(s2, HIGH); digitalWrite(s3, LOW); digitalWrite(s4, LOW); sensores[5] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, HIGH); digitalWrite(s2, HIGH); digitalWrite(s3, LOW); digitalWrite(s4, LOW); sensores[6] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, HIGH); digitalWrite(s2, HIGH); digitalWrite(s3, LOW); digitalWrite(s4, LOW); sensores[7] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, HIGH); digitalWrite(s4, LOW); sensores[8] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, HIGH); digitalWrite(s4, LOW); sensores[9] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, HIGH); digitalWrite(s2, LOW); digitalWrite(s3, HIGH); digitalWrite(s4, LOW); sensores[10] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, HIGH); digitalWrite(s2, LOW); digitalWrite(s3, HIGH); digitalWrite(s4, LOW); sensores[11] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, HIGH); digitalWrite(s3, HIGH); digitalWrite(s4, LOW); sensores[12] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, LOW); digitalWrite(s2, HIGH); digitalWrite(s3, HIGH); digitalWrite(s4, LOW); sensores[13] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, HIGH); digitalWrite(s2, HIGH); digitalWrite(s3, HIGH); digitalWrite(s4, LOW); sensores[14] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, HIGH); digitalWrite(s2, HIGH); digitalWrite(s3, HIGH); digitalWrite(s4, LOW); sensores[15] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, LOW); digitalWrite(s4, HIGH); sensores[16] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, LOW); digitalWrite(s4, HIGH); sensores[17] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, HIGH); digitalWrite(s2, LOW); digitalWrite(s3, LOW); digitalWrite(s4, HIGH); sensores[18] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, HIGH); digitalWrite(s2, LOW); digitalWrite(s3, LOW); digitalWrite(s4, HIGH); sensores[19] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, HIGH); digitalWrite(s3, LOW); digitalWrite(s4, HIGH); sensores[20] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, LOW); digitalWrite(s2, HIGH); digitalWrite(s3, LOW); digitalWrite(s4, HIGH); sensores[21] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, HIGH); digitalWrite(s2, HIGH); digitalWrite(s3, LOW); digitalWrite(s4, HIGH); sensores[22] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, HIGH); digitalWrite(s2, HIGH); digitalWrite(s3, LOW); digitalWrite(s4, HIGH); sensores[23] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, HIGH); digitalWrite(s4, HIGH); sensores[24] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, HIGH); digitalWrite(s4, HIGH); sensores[25] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, HIGH); digitalWrite(s2, LOW); digitalWrite(s3, HIGH); digitalWrite(s4, HIGH); sensores[26] = analogRead(OM);
digitalWrite(s0, HIGH); digitalWrite(s1, HIGH); digitalWrite(s2, LOW); digitalWrite(s3, HIGH); digitalWrite(s4, HIGH); sensores[27] = analogRead(OM);
digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, HIGH); digitalWrite(s3, HIGH); digitalWrite(s4, HIGH); sensores[28] = analogRead(OM);


    // Read the sensor value
    sensores[i] = analogRead(OM);

    // Print the sensor value
    Serial.print(sensores[i]);
    Serial.print("\t");
  }

  // Print a new line after printing all sensor values
  Serial.println(" ");
}