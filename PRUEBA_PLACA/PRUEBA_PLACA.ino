const int switch1_aviso1 = 63;

const int relay1_av1_A = 0;
const int relay2_av1_B = 1;
const int relay3_av1_C = 2;
const int relay4_av1_D = 3;
const int relay5_av1_E = 4;
const int relay6_av1_F = 5;
const int relay7_av1_G = 6;

int conrador1_av1 = 0;

void setup() {
  pinMode(switch1_aviso1,INPUT);
  
  pinMode(relay1_av1_A,OUTPUT);pinMode(relay2_av1_B,OUTPUT);pinMode(relay3_av1_C,OUTPUT);pinMode(relay4_av1_D,OUTPUT);
  pinMode(relay5_av1_E,OUTPUT);pinMode(relay6_av1_F,OUTPUT);  pinMode(relay7_av1_G,OUTPUT);

}

void loop() {
   int value = digitalRead(switch1_aviso1);
   delay(220);
   if (value == HIGH){
    conrador1_av1 +=1;
    if (conrador1_av1 ==10 ){
      conrador1_av1 = 0;
    }
   }

  switch (conrador1_av1) {
  case 0:
   resetear();
    cero();
    break;
  case 1:
   resetear();
    uno();
    break;
  case 2:
   resetear();
    dos();
    break;
  case 3:
   resetear();
    tres();
    break;
  case 4:
   resetear();
    cuatro();
    break;
  case 5:
   resetear();
    cinco();
    break;
  case 6:
   resetear();
    seis();
    break;
  case 7:
   resetear();
    siete();
    break;
  case 8:
   resetear();
    ocho();
    break;
  case 9:
   resetear();
    nueve();
    break;
  default:
    resetear();
    break;
}
}
void resetear(){
  digitalWrite(relay1_av1_A,HIGH);
  digitalWrite(relay2_av1_B,HIGH);
  digitalWrite(relay3_av1_C,HIGH);
  digitalWrite(relay4_av1_D,HIGH);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,HIGH);
  digitalWrite(relay7_av1_G,HIGH);}

  
void cero(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,LOW);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,HIGH);
  }

void uno(){
  digitalWrite(relay1_av1_A,HIGH);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,HIGH);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,HIGH);
  digitalWrite(relay7_av1_G,HIGH);
  }

void dos(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,HIGH);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,LOW);
  digitalWrite(relay6_av1_F,HIGH);
  digitalWrite(relay7_av1_G,LOW);
  }

void tres(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,HIGH);
  digitalWrite(relay7_av1_G,LOW);
  }

void cuatro(){
  digitalWrite(relay1_av1_A,HIGH);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,HIGH);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
  }

void  cinco(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,HIGH);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
  }

void  seis(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,HIGH);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,LOW);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
  }

void  siete(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,HIGH);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,HIGH);
  digitalWrite(relay7_av1_G,HIGH);
  }

void  ocho(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,LOW);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
}

void  nueve(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
}
