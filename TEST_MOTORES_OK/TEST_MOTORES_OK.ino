int pini = 9;
int pwmi = 5;
int pind = 6;
int pwmd = 3;

int frente = 120;   // Velocidad a la que ira el motor hacia adelante cuando pierda la linea max 255
int reversa = 120;  // Velocidad a la que ira el motor hacia atras cuando pierda la linea    max 255
void setup() {
   pinMode(pini, OUTPUT);
  pinMode(pwmi, OUTPUT);
  pinMode(pind, OUTPUT);
  pinMode(pwmd, OUTPUT);

}

void loop() {
  analogWrite ( pwmd, reversa); digitalWrite ( pind, HIGH);
  analogWrite ( pwmi, frente); digitalWrite ( pini, HIGH);

}
