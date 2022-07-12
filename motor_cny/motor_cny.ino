float piso1 = A0, piso2 = A1, piso3 = A2;
// pines para el motor
int der = 10;
int izq = 11;

void setup() {

  // para los infrarrojos CNY70
  pinMode (piso1,INPUT); 
  pinMode (piso2,INPUT);
  pinMode (piso3,INPUT);
  
  // pines motor
  pinMode (der,OUTPUT);
  pinMode (izq,OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  
// distancias detctadas por los sensores
float dis_piso1 = analogRead(piso1);
float dis_piso2 = analogRead(piso2);
float dis_piso3 = analogRead(piso3);

Serial.println(dis_piso1);
Serial.println(dis_piso2);
Serial.println(dis_piso3);
delay(1000);
if(dis_piso1 < 50 ){
  digitalWrite(der,LOW);
  digitalWrite(izq,LOW);
  delay(1000);
  }
else{
  digitalWrite(der,LOW);
  digitalWrite(izq,LOW);
  delay(1000);
  
  }

}
