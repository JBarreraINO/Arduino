#define s0      A0
#define s1      A1
#define s2      A2
#define s3      A3
#define AI      A4
#define LED_ON  11
#define LED     13
#define BOTON    9
int sensores[16];
int umbral=750;

//////COLOR DE LÍNEA SEGÚN LA BARRA//////////
//I.M BLANCA=1 NEGRA=0
//PHOENIX BLANCA=0 NEGRA=1
int linea=1;
///////////////////////////////////////////


void setup() {
Serial.begin(115200);
pinMode(s0,OUTPUT);
pinMode(s1,OUTPUT);
pinMode(s2,OUTPUT);
pinMode(s3,OUTPUT);
pinMode(LED,OUTPUT);
pinMode(LED_ON,OUTPUT);
pinMode(BOTON,INPUT);
digitalWrite(LED_ON,1);
}

void loop() {

/*digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,0);sensores[0]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,0);sensores[1]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,0);sensores[2]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,0);sensores[3]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,0);sensores[4]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,0);sensores[5]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,0);sensores[6]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,0);sensores[7]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,1);sensores[8]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,1);sensores[9]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,1);sensores[10]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,1);sensores[11]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,1);sensores[12]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,1);sensores[13]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,1);sensores[14]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,1);sensores[15]=analogRead(AI);*/
for(int i=0;i<16;i++){
  digitalWrite(s0,i&0x01);
  digitalWrite(s1,i&0x02);
  digitalWrite(s2,i&0x04);
  digitalWrite(s3,i&0x08);

  ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
 sensores[i] =ADCL | (ADCH << 8);


 //Serial.print(sensores[i]);
  Serial.print("\t");
}
Serial.println(" ");

for(int i=0;i<16;i++){
  if(sensores[i]<=umbral){
    sensores[i]=0;
  }
  Serial.print(sensores[i]);
  Serial.print("\t");
}
Serial.println(" ");

}
