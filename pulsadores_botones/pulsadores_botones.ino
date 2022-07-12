
void setup() {
pinMode(10,INPUT);
pinMode(11,INPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);

}

void loop() {
 int button=digitalRead(10);
 int button2=digitalRead(11);
 if (button==LOW)
{ digitalWrite(13,HIGH);
delay(1000);
 digitalWrite(12,HIGH);
delay(1000)

º
digitalWrite(9,HIGH);
delay(1000);
 digitalWrite(8,HIGH);
delay(1000);


}
if (button2==LOW)
{digitalWrite(13,LOW);
digitalWrite(12,LOW);  
digitalWrite(8,LOW);
}digitalWrite(9,LOW);





}
