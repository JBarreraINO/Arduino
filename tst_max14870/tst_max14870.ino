

int pini = 9;
int pwmi = 5;
int pind = 6;
int pwmd = 3;
void setup() {
pinMode( pini ,OUTPUT);
pinMode(  pwmi ,OUTPUT);
pinMode(  pind ,OUTPUT);
pinMode( pwmd ,OUTPUT);
}

void loop() {

analogWrite(pini,125);
analogWrite(pwmi,0);
delay(5000);

analogWrite(pini,0);
analogWrite(pwmi,70);

delay(5000);


  

}
