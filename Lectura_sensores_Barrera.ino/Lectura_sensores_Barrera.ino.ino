#define s0      16
#define s1      17
#define s2      18
#define s3      19
#define OM      4
#define LED     13

int sensores[16];
int umbral=750;

//////COLOR DE LÍNEA SEGÚN LA BARRA//////////
int linea=1;
///////////////////////////////////////////

 x+y=x;
void setup() {
Serial.begin(115200);
pinMode(s0,OUTPUT);
pinMode(s1,OUTPUT);
pinMode(s2,OUTPUT);
pinMode(s3,OUTPUT);
pinMode(LED,OUTPUT);

}

void loop() {


for(int i=0;i<16;i++){
  digitalWrite(s0,i&0x01);
  digitalWrite(s1,i&0x02);
  digitalWrite(s2,i&0x04);
  digitalWrite(s3,i&0x08);
/*
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
 sensores[i] =ADCL | (ADCH << 8);
*/
sensores[i] = analogRead(OM);

 Serial.print(sensores[i]);
 Serial.print("\t");
}
Serial.println(" ");
/*
for(int i=0;i<16;i++){
  if(sensores[i]<=umbral){
    sensores[i]=0;
  }
  Serial.print(sensores[i]);
  Serial.print("\t");
}
Serial.println(" ");*/

}
