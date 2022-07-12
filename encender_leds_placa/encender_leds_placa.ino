const int switch1_aviso1 = 0;
const int switch2_aviso1 = 1;
const int switch3_aviso1 = 2;
const int switch4_aviso1 = 3;

const int switch1_aviso2 = 4;
const int switch2_aviso2 = 5;
const int switch3_aviso2 = 6;
const int switch4_aviso2 = 7;

const int relay1_av1_A= 8;
const int relay2_av1_B = 9;
const int relay3_av1_C = 10;
const int relay4_av1_D = 11;
const int relay5_av1_E= 12;
const int relay6_av1_F = 13;
const int relay7_av1_G = 14;

const int relay8_av1_A= 15;
const int relay9_av1_B= 16;
const int relay10_av1_C = 17;
const int relay11_av1_D= 18;
const int relay12_av1_E = 19;
const int relay13_av1_F = 20;
const int relay14_av1_G = 21;

const int relay15_av1_A = 22;
const int relay16_av1_B = 23;
const int relay17_av1_C = 24;
const int relay18_av1_D = 25;
const int relay19_av1_E = 26;
const int relay20_av1_F = 26;
const int relay21_av1_G = 27;

const int relay22_av1_A = 28;
const int relay23_av1_B = 29;
const int relay24_av1_C = 30;
const int relay25_av1_D = 31;
const int relay26_av1_E = 32;
const int relay27_av1_F = 33;
const int relay28_av1_G = 34;

const int relay1_av2_A = 35;
const int relay2_av2_B = 36;
const int relay3_av2_C = 37;
const int relay4_av2_D = 38;
const int relay5_av2_E = 39;
const int relay6_av2_F = 40;
const int relay7_av2_G = 41;

const int relay8_av2_A= 42;
const int relay9_av2_B = 43;
const int relay10_av2_C = 44;
const int relay11_av2_D = 45;
const int relay12_av2_E = 46;
const int relay13_av2_F = 47;
const int relay14_av2_G = 48;

const int relay15_av2_A = 49;
const int relay16_av2_B = 50;
const int relay17_av2_C = 51;
const int relay18_av2_D = 52;
const int relay19_av2_E = 53;
const int relay20_av2_F = A0;
const int relay21_av2_G = A1;

const int relay22_av2_A = A2;
const int relay23_av2_B = A3;
const int relay24_av2_C = A4;
const int relay25_av2_D = A5;
const int relay26_av2_E = A6;
const int relay27_av2_F = A7;
const int relay28_av2_G = A8;

int conrador1_av1 = 0;
int conrador2_av1 = 0;
int conrador3_av1 = 0;
int conrador4_av1 = 0;

int conrador1_av2 = 0;
int conrador2_av2 = 0;
int conrador3_av2 = 0;
int conrador4_av2 = 0;

void setup() {
  pinMode(switch1_aviso1,OUTPUT);pinMode(switch2_aviso1,OUTPUT);pinMode(switch3_aviso1,OUTPUT);pinMode(switch4_aviso1,OUTPUT);
  pinMode(switch1_aviso2,OUTPUT);pinMode(switch2_aviso2,OUTPUT);pinMode(switch3_aviso2,OUTPUT);pinMode(switch4_aviso2,OUTPUT);

  pinMode(relay1_av1_A,OUTPUT);pinMode(relay2_av1_B,OUTPUT);pinMode(relay3_av1_C,OUTPUT);pinMode(relay4_av1_D,OUTPUT);
  pinMode(relay5_av1_E,OUTPUT);pinMode(relay6_av1_F,OUTPUT);pinMode(relay7_av1_G,OUTPUT);
  pinMode(relay8_av1_A,OUTPUT);pinMode(relay9_av1_B,OUTPUT);pinMode(relay10_av1_C,OUTPUT);pinMode(relay11_av1_D,OUTPUT);
  pinMode(relay12_av1_E,OUTPUT);pinMode(relay13_av1_F,OUTPUT);pinMode(relay14_av1_G,OUTPUT);
  pinMode(relay15_av1_A,OUTPUT);pinMode(relay16_av1_B,OUTPUT);pinMode(relay17_av1_C,OUTPUT);pinMode(relay18_av1_D,OUTPUT);
  pinMode(relay19_av1_E,OUTPUT);pinMode(relay20_av1_F,OUTPUT);pinMode(relay21_av1_G,OUTPUT);
  pinMode(relay22_av1_A,OUTPUT);pinMode(relay23_av1_B,OUTPUT);pinMode(relay24_av1_C,OUTPUT);pinMode(relay25_av1_D,OUTPUT);
  pinMode(relay26_av1_E,OUTPUT);pinMode(relay27_av1_F,OUTPUT);pinMode(relay28_av1_G,OUTPUT);

  pinMode(relay1_av2_A,OUTPUT);pinMode(relay2_av2_B,OUTPUT);pinMode(relay3_av2_C,OUTPUT);pinMode(relay4_av2_D,OUTPUT);
  pinMode(relay5_av2_E,OUTPUT);pinMode(relay6_av2_F,OUTPUT);  pinMode(relay7_av2_G,OUTPUT);
  pinMode(relay8_av2_A,OUTPUT);pinMode(relay9_av2_B,OUTPUT);pinMode(relay10_av2_C,OUTPUT);pinMode(relay11_av2_D,OUTPUT);
  pinMode(relay12_av2_E,OUTPUT);pinMode(relay13_av2_F,OUTPUT);pinMode(relay14_av2_G,OUTPUT);
  pinMode(relay15_av2_A,OUTPUT);pinMode(relay16_av2_B,OUTPUT);pinMode(relay17_av2_C,OUTPUT);pinMode(relay18_av2_D,OUTPUT);
  pinMode(relay19_av2_E,OUTPUT);pinMode(relay20_av2_F,OUTPUT);pinMode(relay21_av2_G,OUTPUT);
  pinMode(relay22_av2_A,OUTPUT);pinMode(relay23_av2_B,OUTPUT);pinMode(relay24_av2_C,OUTPUT);pinMode(relay25_av2_D,OUTPUT);
  pinMode(relay26_av2_E,OUTPUT);pinMode(relay27_av2_F,OUTPUT);pinMode(relay28_av2_G,OUTPUT);
}

void loop() {
  digitalWrite(0,LOW);
   digitalWrite(1,LOW);
    digitalWrite(2,LOW);
     
  
 /* for (int i = 1; i<30; i++){
    digitalWrite(i,HIGH);
    delay(500);

  }
  
*/


}
