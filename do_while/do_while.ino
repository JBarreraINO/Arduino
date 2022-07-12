int x=0;
int led=13;
void setup() {

Serial.begin(9600);
 pinMode(led,OUTPUT);
}

void loop() {

while(x<10){
 digitalWrite(led,HIGH);
 delay(10);
 digitalWrite(led,LOW);
 delay(100);
 x++;

}
 
  Serial.println(x);

}
