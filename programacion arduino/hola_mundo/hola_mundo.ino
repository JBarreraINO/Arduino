int led=7;
int p=8;

void setup() {
  // put your setup code here, to run once:
pinMode(led,OUTPUT);
pinMode(p,INPUT);
}

void loop() {
int  estado=digitalRead(p);
  if(estado==1){
digitalWrite(led,HIGH);
delay(300);
digitalWrite(led,LOW);
delay(200);
  }
  
  
}
