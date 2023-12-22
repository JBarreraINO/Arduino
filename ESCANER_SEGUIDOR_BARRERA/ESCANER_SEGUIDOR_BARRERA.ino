#include <Servo.h>
Servo fan;
int velocidad = 150;  // Velocidad crucero de robot max 255


int incomingByte = 0;  // for incoming serial data
char c;
String dataIn;
int velocidad1;
int8_t indexOfA, indexOfB;
int velocidadfan;

int LEDS = 13;
#define s0 A0  // Sensor Selection pins.
#define s1 A1  // Sensor Selection pins.
#define s2 A2  // Sensor Selection pins.
#define s3 A3  // Sensor Selection pins.
#define OM A4  // Sensor Selection pins.
int led = 13;  // Led default de Arduino

int pini = 11;
int pwmi = 12;
int pind = 9;
int pwmd = 10;
//int pini = 11;
//int pwmi = 12;
//int pind = 10;
//int pwmd = A2;
//int pini = 9;
//int pwmi = 5;
//int pind = 6;
//int pwmd = 3;

int go = 8;  // Puerto donde se conecta el arrancador ( si el modulo no esta conectado, debe ponerse una resistencia pull-down)
int rdy = 12;
int boton_izq = 4;  // boton izquierdo
int boton_der = 7;  // boton derecho
bool valor7 = false, valor4 = false, valorgo = false, valorrdy = false;
uint16_t sensores[16];


void setup() {
  Serial.begin(115200);  // opens serial port, sets data rate to 9600 bps
  pinMode(LEDS, OUTPUT);
  fan.attach(6);
  fan.writeMicroseconds(1000);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(OM, INPUT);
  pinMode(go, INPUT);
  pinMode(boton_izq, INPUT);
  pinMode(boton_der, INPUT);
  pinMode(rdy, INPUT);
  pinMode(pini, OUTPUT);
  pinMode(pwmi, OUTPUT);
  pinMode(pind, OUTPUT);
  pinMode(pwmd, OUTPUT);

}

void loop() {
  // reply only when you receive data:

  serialdata();
  if (c == '\n') {
    parse();
    c = 0;
    dataIn = "";
  }
  botones();
  lectura();
  Serial.print((String) sensores[0]+"A"+sensores[1]+"B"+sensores[2]+"C" + sensores[3]+"D"+sensores[4]+"E"+sensores[5]+"F"+sensores[6]+"G"+sensores[7]+"H"+sensores[8]+"I" +sensores[9]+"J"+sensores[10]+"K"+sensores[11]+"L" +sensores[12]+"M"+sensores[13]+"N" +sensores[14]+"O"+sensores[15]+"P"+ valor7+"Q"+ valor4+"R"+ valorrdy+"S"+valorgo+"T"+ velocidadfan+"U"  "\n");
 fan.writeMicroseconds(velocidadfan);
  switch (c)

  {
    case '1':
      digitalWrite(LEDS, HIGH);



      break;
    case '2':
      digitalWrite(pini, HIGH);
      analogWrite(pwmi, velocidad1);
      delay(1000);
      digitalWrite(pini, LOW);
      analogWrite(pwmi, velocidad1);
      delay(1000);
      break;
    case '3':
      analogWrite(pwmi, 0);
      analogWrite(pwmd, 0);
      break;
    case '4':
      digitalWrite(pind, HIGH);
      analogWrite(pwmd, velocidad1);
      delay(1000);
      digitalWrite(pind, LOW);
      analogWrite(pwmd, velocidad1);
      delay(1000);
      break;
    case '5':
      digitalWrite(LEDS, LOW);
      break;

      case'6':
      
      break;
      case'7':
      fan.writeMicroseconds(0);
     
      break;
      case'8':
      fan.writeMicroseconds(2000);
       delay(2000);
       fan.writeMicroseconds(1000);
       delay(5000);
      break;

  }
}

void serialdata() {
  while (Serial.available() > 0) {
    c = Serial.read();
    if (c == '\n') {
      break;
    } else {
      dataIn += c;
    }
  }
}

void parse() {

  String str_velocidad, str_velocidadfan;

  indexOfA = dataIn.indexOf("A");
  indexOfB = dataIn.indexOf("B");
  if (indexOfA > -1) {
    str_velocidad = dataIn.substring(0, indexOfA);
    velocidad1 = str_velocidad.toInt();
  }
  if (indexOfB > -1) {
    str_velocidadfan = dataIn.substring(indexOfA + 1, indexOfB);
    velocidadfan = str_velocidadfan.toInt();
  }
}
void lectura() {


  for (int i = 0; i < 16; i++) {

    digitalWrite(s0, 0);
    digitalWrite(s1, 0);
    digitalWrite(s2, 0);
    digitalWrite(s3, 0);
    sensores[0] = analogRead(OM);
    digitalWrite(s0, 1);
    digitalWrite(s1, 0);
    digitalWrite(s2, 0);
    digitalWrite(s3, 0);
    sensores[1] = analogRead(OM);
    digitalWrite(s0, 0);
    digitalWrite(s1, 1);
    digitalWrite(s2, 0);
    digitalWrite(s3, 0);
    sensores[2] = analogRead(OM);
    digitalWrite(s0, 1);
    digitalWrite(s1, 1);
    digitalWrite(s2, 0);
    digitalWrite(s3, 0);
    sensores[3] = analogRead(OM);
    digitalWrite(s0, 0);
    digitalWrite(s1, 0);
    digitalWrite(s2, 1);
    digitalWrite(s3, 0);
    sensores[4] = analogRead(OM);
    digitalWrite(s0, 1);
    digitalWrite(s1, 0);
    digitalWrite(s2, 1);
    digitalWrite(s3, 0);
    sensores[5] = analogRead(OM);
    digitalWrite(s0, 0);
    digitalWrite(s1, 1);
    digitalWrite(s2, 1);
    digitalWrite(s3, 0);
    sensores[6] = analogRead(OM);
    digitalWrite(s0, 1);
    digitalWrite(s1, 1);
    digitalWrite(s2, 1);
    digitalWrite(s3, 0);
    sensores[7] = analogRead(OM);
    digitalWrite(s0, 0);
    digitalWrite(s1, 0);
    digitalWrite(s2, 0);
    digitalWrite(s3, 1);
    sensores[8] = analogRead(OM);
    digitalWrite(s0, 1);
    digitalWrite(s1, 0);
    digitalWrite(s2, 0);
    digitalWrite(s3, 1);
    sensores[9] = analogRead(OM);
    digitalWrite(s0, 0);
    digitalWrite(s1, 1);
    digitalWrite(s2, 0);
    digitalWrite(s3, 1);
    sensores[10] = analogRead(OM);
    digitalWrite(s0, 1);
    digitalWrite(s1, 1);
    digitalWrite(s2, 0);
    digitalWrite(s3, 1);
    sensores[11] = analogRead(OM);
    digitalWrite(s0, 0);
    digitalWrite(s1, 0);
    digitalWrite(s2, 1);
    digitalWrite(s3, 1);
    sensores[12] = analogRead(OM);
    digitalWrite(s0, 1);
    digitalWrite(s1, 0);
    digitalWrite(s2, 1);
    digitalWrite(s3, 1);
    sensores[13] = analogRead(OM);
    digitalWrite(s0, 0);
    digitalWrite(s1, 1);
    digitalWrite(s2, 1);
    digitalWrite(s3, 1);
    sensores[14] = analogRead(OM);
    digitalWrite(s0, 1);
    digitalWrite(s1, 1);
    digitalWrite(s2, 1);
    digitalWrite(s3, 1);
    sensores[15] = analogRead(OM);
  }
}


void botones() {
  valor7 = digitalRead(boton_der);
  valor4 = digitalRead(boton_izq);
  valorrdy = digitalRead(rdy);
  valorgo = digitalRead(go);
}