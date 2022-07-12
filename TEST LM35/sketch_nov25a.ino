const int sensor = A2;
const int ledrojo = 5;
const int ledazul = 6;

long milivolts;
long temperatura;

void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  milivolts = (analogRead (sensor)*5000L) / 1023;
  temperatura=milivolts/10;

  Serial.print("Temperatura: ");
  Serial.print (temperatura);
  Serial.println(" grados");
  delay (200);

}
