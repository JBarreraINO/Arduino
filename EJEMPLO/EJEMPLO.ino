#define s0 A0 
#define s1 A1
#define s2 A2
#define s3 A3
#define OM A4 
int sensores[16];
void setup() {
Serial.begin(115200);
pinMode(s0,OUTPUT);
pinMode(s1,OUTPUT);
pinMode(s2,OUTPUT);
pinMode(s3,OUTPUT);
}

void loop() {
  for(int i=0;i<16;i++){
    
  digitalWrite(s0,LOW);   digitalWrite(s1,LOW);   digitalWrite(s2,LOW);   digitalWrite(s3,LOW);   sensores[0]=analogRead(OM);
   digitalWrite(s0,HIGH);   digitalWrite(s1,LOW);   digitalWrite(s2,LOW);   digitalWrite(s3,LOW);   sensores[1]=analogRead(OM);
    digitalWrite(s0,LOW);   digitalWrite(s1,HIGH);   digitalWrite(s2,LOW);   digitalWrite(s3,LOW);   sensores[2]=analogRead(OM);
     digitalWrite(s0,HIGH);   digitalWrite(s1,HIGH);   digitalWrite(s2,LOW);   digitalWrite(s3,LOW);   sensores[3]=analogRead(OM);
      digitalWrite(s0,LOW);   digitalWrite(s1,LOW);   digitalWrite(s2,HIGH);   digitalWrite(s3,LOW);   sensores[4]=analogRead(OM);
       digitalWrite(s0,HIGH);   digitalWrite(s1,LOW);   digitalWrite(s2,HIGH);   digitalWrite(s3,LOW);   sensores[5]=analogRead(OM);
        digitalWrite(s0,LOW);   digitalWrite(s1,HIGH);   digitalWrite(s2,HIGH);   digitalWrite(s3,LOW);   sensores[6]=analogRead(OM);
         digitalWrite(s0,HIGH);   digitalWrite(s1,HIGH);   digitalWrite(s2,HIGH);   digitalWrite(s3,LOW);   sensores[7]=analogRead(OM);
          digitalWrite(s0,LOW);   digitalWrite(s1,LOW);   digitalWrite(s2,LOW);   digitalWrite(s3,HIGH);   sensores[8]=analogRead(OM);
           digitalWrite(s0,HIGH);   digitalWrite(s1,LOW);   digitalWrite(s2,LOW);   digitalWrite(s3,HIGH);   sensores[9]=analogRead(OM);
            digitalWrite(s0,LOW);   digitalWrite(s1,HIGH);   digitalWrite(s2,LOW);   digitalWrite(s3,HIGH);   sensores[10]=analogRead(OM);
             digitalWrite(s0,HIGH);   digitalWrite(s1,HIGH);   digitalWrite(s2,LOW);   digitalWrite(s3,HIGH);   sensores[11]=analogRead(OM);
              digitalWrite(s0,LOW);   digitalWrite(s1,LOW);   digitalWrite(s2,HIGH);   digitalWrite(s3,HIGH);   sensores[12]=analogRead(OM);
               digitalWrite(s0,HIGH);   digitalWrite(s1,LOW);   digitalWrite(s2,HIGH);   digitalWrite(s3,HIGH);   sensores[13]=analogRead(OM);
                digitalWrite(s0,LOW);   digitalWrite(s1,HIGH);   digitalWrite(s2,HIGH);   digitalWrite(s3,HIGH);   sensores[14]=analogRead(OM);
                 digitalWrite(s0,HIGH);   digitalWrite(s1,HIGH);   digitalWrite(s2,HIGH);   digitalWrite(s3,HIGH);   sensores[15]=analogRead(OM);
                 Serial.print(sensores[i]);
                 Serial.print("\t");
         

  
    
    }
   
Serial.println("");
}
