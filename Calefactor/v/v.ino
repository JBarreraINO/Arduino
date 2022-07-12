int NIVEL =A4;
int presion =A3;
int presion1=0;
int nivelvajo=0;
int llama=0;
int electrogas=4;
int g=8;
int sensorllama= A2;
int nive2=A5;
int nivelalto=0;
int chispero=3;
int electroagua=7;

void setup() {
  

Serial.begin(9600);

pinMode(presion , INPUT);
pinMode(nive2 , INPUT);
pinMode(NIVEL , INPUT);
pinMode(electrogas , OUTPUT);
pinMode(g , OUTPUT);
pinMode(sensorllama , INPUT);

 rutina1: if(nivelvajo==HIGH){
    digitalWrite(electroagua,HIGH);
    goto rutina2;
  }
    rutina2: if (nivelalto==HIGH){
      digitalWrite(electrogas,HIGH);
  digitalWrite(chispero,HIGH);
  delay(5000);
  digitalWrite(chispero,LOW);
  digitalWrite(electroagua,LOW);
  delay(100);
//  goto rutina3;
    }

}


void loop() {
 presion1 =digitalRead(presion);
 
 nivelvajo =digitalRead(NIVEL);

nivelalto=digitalRead(nive2);
 llama=digitalRead(sensorllama);

 rutina3:
 if ( presion1||nivelvajo||llama==HIGH){
  digitalWrite(electrogas,LOW);
  delay(300);

  
}
if(presion1==LOW){
  
prender(HIGH,HIGH);
}
if(nivelvajo==LOW){
  
prender(HIGH,HIGH);
}
if(llama==LOW){
  
prender(HIGH,HIGH);
}
}
void prender(int chispero, int electrogas){
  digitalWrite(electrogas,HIGH);
  digitalWrite(chispero,HIGH);
  delay(5000);
  digitalWrite(chispero,LOW);
  
}
