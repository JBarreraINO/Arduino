/*
#define s0 A2  // Sensor Selection pin S0.
#define s1 5   // Sensor Selection pin S1.
#define s2 6   // Sensor Selection pin S2.
#define s3 7   // Sensor Selection pin S3.
#define s4 8   // Sensor Selection pin S4.
#define OM A5  // Output pin of the multiplexer.
*/

#define s0 8  // Sensor Selection pin S0.
#define s1 7   // Sensor Selection pin S1.
#define s2 6   // Sensor Selection pin S2.
#define s3 5   // Sensor Selection pin S3.
#define s4 4   // Sensor Selection pin S4.
#define OM A5  // Output pin of the multiplexer.

int sensores[28];

void setup() {
  Serial.begin(115200);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
}

void loop() {
  for (int i = 0; i < 28; i++) {
    // Set the multiplexer channel
    digitalWrite(s0, (i & 0x01) ? HIGH : LOW);
    digitalWrite(s1, (i & 0x02) ? HIGH : LOW);
    digitalWrite(s2, (i & 0x04) ? HIGH : LOW);
    digitalWrite(s3, (i & 0x08) ? HIGH : LOW);
    digitalWrite(s4, (i & 0x10) ? HIGH : LOW);

    // Read the sensor value
    sensores[i] = analogRead(OM);

    // Print the sensor value
    Serial.print(sensores[i]);
    Serial.print("\t");
  }

  // Print a new line after printing all sensor values
  Serial.println(" ");
}