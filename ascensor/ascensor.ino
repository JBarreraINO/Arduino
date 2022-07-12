
int vel = 0; // Velocidad de los motores (0-255)

void setup()  { 
  pinMode(8, INPUT);
    pinMode(9, INPUT);
      pinMode(10, INPUT);
    pinMode(6, OUTPUT);
    pinMode(3, OUTPUT);
    
 } 
 
void loop()  { 
  S1=analogRead(A0);
    S2=analogRead(A1);
      S3=analogRead(A2);
      
 if(digitalRead(4) == LOW){
  
 while(S1== 100){
  digitalWrite(6,HIGH);
  analogWrite(3,155);
  
 }


  
 analogWrite(3,155);
 delay(255);
  digitalWrite(6,LOW);
 }
  
}
