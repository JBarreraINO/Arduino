#include <Arduino.h>
#line 1
#line 1 "C:\\Users\\tiche\\Downloads\\Lectura_sensores_Barrera.ino2\\Lectura_sensores_Barrera.ino2.ino"

#define s0 A0 // Sensor Selection pins.
#define s1 A1
#define s2 A2
#define s3 A3
#define OM A4
int sensores[16];
#line 8 "C:\\Users\\tiche\\Downloads\\Lectura_sensores_Barrera.ino2\\Lectura_sensores_Barrera.ino2.ino"
void setup();
#line 16 "C:\\Users\\tiche\\Downloads\\Lectura_sensores_Barrera.ino2\\Lectura_sensores_Barrera.ino2.ino"
void loop();
#line 8
void setup() {
Serial.begin(115200);
pinMode(s0,OUTPUT);
pinMode(s1,OUTPUT);
pinMode(s2,OUTPUT);
pinMode(s3,OUTPUT);
}

void loop() {


for(int i=0;i<16;i++){

  digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,0);sensores[0]=analogRead(OM);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,0);sensores[1]=analogRead(OM);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,0);sensores[2]=analogRead(OM);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,0);sensores[3]=analogRead(OM);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,0);sensores[4]=analogRead(OM);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,0);sensores[5]=analogRead(OM);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,0);sensores[6]=analogRead(OM);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,0);sensores[7]=analogRead(OM);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,1);sensores[8]=analogRead(OM);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,1);sensores[9]=analogRead(OM);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,1);sensores[10]=analogRead(OM);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,1);sensores[11]=analogRead(OM);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,1);sensores[12]=analogRead(OM);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,1);sensores[13]=analogRead(OM);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,1);sensores[14]=analogRead(OM);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,1);sensores[15]=analogRead(OM);
Serial.print(sensores[i]);
Serial.flush();
Serial.print("\t");
  }
  Serial.println(" ");

}

