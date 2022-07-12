const int switch1_aviso1 = 66;
const int switch2_aviso1 = 65;
const int switch3_aviso1 = 64;
const int switch4_aviso1 = 62;
const int switch5_aviso1 = 63;


const int switch3_aviso2 = 69;
const int switch4_aviso2 = 68;
const int switch5_aviso2 = 67;
//SEGMENTO D131 XXXX8
const int relay1_av1_A = 0;
const int relay2_av1_B = 1;
const int relay3_av1_C = 2;
const int relay4_av1_D = 3;
const int relay5_av1_E = 4;
const int relay6_av1_F = 5;
const int relay7_av1_G = 6;
//SEGMENTO D130 XXX8X
const int relay8_av1_A = 7;
const int relay9_av1_B = 8;
const int relay10_av1_C = 9;
const int relay11_av1_D = 10;
const int relay12_av1_E = 11;
const int relay13_av1_F = 12;
const int relay14_av1_G = 13;
//SEGMENTO D129 XX8XX
const int relay15_av1_A = 14;
const int relay16_av1_B = 15;
const int relay17_av1_C = 16;
const int relay18_av1_D = 17;
const int relay19_av1_E = 18;
const int relay20_av1_F = 19;
const int relay21_av1_G = 20;
//SEGMENTO D129 X8XXX
const int relay22_av1_A = 21;
const int relay23_av1_B = 22;
const int relay24_av1_C = 23;
const int relay25_av1_D = 24;
const int relay26_av1_E = 25;
const int relay27_av1_F = 26;
const int relay28_av1_G = 27;

//SEGMENTO D128 8.XXXX PUNTO
const int relayA_av2_A = 28;
const int relayB_av2_B = 29;
const int relayP_av2_P = 30;


//SEGMENTO D136 XXXX8
const int relay1_av2_A = 31;
const int relay2_av2_B = 32;
const int relay3_av2_C = 33;
const int relay4_av2_D = 34;
const int relay5_av2_E = 35;
const int relay6_av2_F = 36;
const int relay7_av2_G = 37;

//SEGMENTO D135 XXX8X
const int relay8_av2_A = 38;
const int relay9_av2_B = 39;
const int relay10_av2_C = 40;
const int relay11_av2_D = 41;
const int relay12_av2_E = 42;
const int relay13_av2_F = 43;
const int relay14_av2_G = 44;

//SEGMENTO D134 XXX8X
const int relay15_av2_A = 45;
const int relay16_av2_B = 46;
const int relay17_av2_C = 47;
const int relay18_av2_D = 48;
const int relay19_av2_E = 49;
const int relay20_av2_F = 50;
const int relay21_av2_G = 51;


//SEGMENTO D133 X8XXX
const int relay22_av2_A = 52;
const int relay23_av2_B = 53;
const int relay24_av2_C = 54;
const int relay25_av2_D = 55;
const int relay26_av2_E = 56;
const int relay27_av2_F = 57;
const int relay28_av2_G = 58;

//SEGMENTO D132 8.XXXX PUNTO
const int relayP1_av2_A = 59;
const int relayP2_av2_B = 60;
const int relayP3_av2_p = 61;



int conrador1_av1 = 0;
int conrador2_av1 = 0;
int conrador3_av1 = 0;
int conrador4_av1 = 0;
int conrador5_av1=0;

int conrador1_av2 = 0;
int conrador2_av2 = 0;
int conrador3_av2 = 0;
int conrador4_av2 = 0;
int conrador5_av2 = 0;

void setup() {
  DDRJ &=~B00001000; 
  DDRJ &=~B00000100;
  pinMode(switch1_aviso1,INPUT);pinMode(switch2_aviso1,INPUT);pinMode(switch3_aviso1,INPUT);pinMode(switch4_aviso1,INPUT); pinMode(switch5_aviso1,INPUT);
 pinMode(switch3_aviso2,INPUT);pinMode(switch4_aviso2,INPUT);

  pinMode(relay1_av1_A,OUTPUT);pinMode(relay2_av1_B,OUTPUT);pinMode(relay3_av1_C,OUTPUT);pinMode(relay4_av1_D,OUTPUT);
  pinMode(relay5_av1_E,OUTPUT);pinMode(relay6_av1_F,OUTPUT);  pinMode(relay7_av1_G,OUTPUT);
  pinMode(relay8_av1_A,OUTPUT);pinMode(relay9_av1_B,OUTPUT);pinMode(relay10_av1_C,OUTPUT);pinMode(relay11_av1_D,OUTPUT);
  pinMode(relay12_av1_E,OUTPUT);pinMode(relay13_av1_F,OUTPUT);pinMode(relay14_av1_G,OUTPUT);
  pinMode(relay15_av1_A,OUTPUT);pinMode(relay16_av1_B,OUTPUT);pinMode(relay17_av1_C,OUTPUT);pinMode(relay18_av1_D,OUTPUT);
  pinMode(relay19_av1_E,OUTPUT);pinMode(relay20_av1_F,OUTPUT);pinMode(relay21_av1_G,OUTPUT);
  pinMode(relay22_av1_A,OUTPUT);pinMode(relay23_av1_B,OUTPUT);pinMode(relay24_av1_C,OUTPUT);pinMode(relay25_av1_D,OUTPUT);
  pinMode(relay26_av1_E,OUTPUT);pinMode(relay27_av1_F,OUTPUT);pinMode(relay28_av1_G,OUTPUT);

  pinMode(relayA_av2_A,OUTPUT);pinMode(relayB_av2_B,OUTPUT);pinMode(relayP_av2_P,OUTPUT);// EL PUNTO
  pinMode(31,OUTPUT);digitalWrite(31,LOW);
  pinMode(32,OUTPUT);digitalWrite(32,LOW);
  pinMode(33,OUTPUT);digitalWrite(33,LOW);
  pinMode(34,OUTPUT);digitalWrite(34,LOW);
  pinMode(35,OUTPUT);digitalWrite(35,LOW);
  pinMode(36,OUTPUT);digitalWrite(36,LOW);
  pinMode(37,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(39,OUTPUT);
  pinMode(40,OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(47,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(49,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
  pinMode(53,OUTPUT);
  pinMode(54,OUTPUT);
  pinMode(55,OUTPUT);
  pinMode(56,OUTPUT);
  pinMode(57,OUTPUT);
  pinMode(58,OUTPUT);
  pinMode(59,OUTPUT);
  pinMode(60,OUTPUT);
  pinMode(61,OUTPUT);
  

  
  pinMode( relayP1_av2_A,OUTPUT);   pinMode( relayP2_av2_B,OUTPUT);   pinMode( relayP3_av2_p,OUTPUT); //PUNTO 2
  
star();
}

void loop() {

digitalWrite(relayP_av2_P ,LOW);
digitalWrite(61,LOW);

  int value1 = digitalRead(switch1_aviso1);
  delay(220);
  if (value1 == HIGH){
    conrador1_av1 +=1;
    if (conrador1_av1 == 10){
      conrador1_av1 = 0;
      }
   case_D0_Av1(conrador1_av1);
   }


  int value2 = digitalRead(switch2_aviso1);
  if (value2 == HIGH){
    conrador2_av1 +=1;
    if (conrador2_av1 == 10){
      conrador2_av1 = 0;
    }
   case_D1_Av1(conrador2_av1);  
  }
  
  int value3 = digitalRead(switch3_aviso1);
  if (value3 == HIGH){
    conrador3_av1 +=1;
    if (conrador3_av1 == 10){
      conrador3_av1 = 0;
    }
   case_D2_Av1(conrador3_av1); 
  }

  int value4 = digitalRead(switch4_aviso1);
  if (value4 == HIGH){
    conrador4_av1 +=1;
    if (conrador4_av1 == 10){
      conrador4_av1 = 0;
    }
  case_D3_Av1(conrador4_av1);
  }


int value5 = digitalRead(switch5_aviso1); 
 if (value5 == HIGH){
     conrador5_av1 +=1;
    if (conrador5_av1 == 2){
      conrador5_av1 = 0;
    }
 P1(conrador5_av1);
  }

  int value25 = digitalRead(switch5_aviso2); 
 if (value25 == HIGH){
     conrador5_av2 +=1;
    if (conrador5_av2 == 2){
      conrador5_av2 = 0;
    }
 P2(conrador5_av2);
  }
 
//ROJO

   //D70
  if (PINJ & B00000100){
    conrador1_av2 +=1;
    if (conrador1_av2 == 10){
      conrador1_av2 = 0;
    }
    case_D5_Av2( conrador1_av2);
    
  }
  
  if (PINJ & B00001000){
    conrador2_av2 +=1;
    if (conrador2_av2 == 10){
      conrador2_av2 = 0;
    }
     case_D4_Av2( conrador2_av2);
   }

   
  int value23 = digitalRead(switch3_aviso2);   
  if (value23 == HIGH){
    conrador3_av2 +=1;
    if (conrador3_av2 == 10){
      conrador3_av2 = 0;
    }
     case_D6_Av2(conrador3_av2);
  }

  int value24 = digitalRead(switch4_aviso2);
  if (value24 == HIGH){
    conrador4_av2 +=1;
    if (conrador4_av2 == 10){
      conrador4_av2 = 0;
    }
    case_D7_Av2( conrador4_av2);
  }
  
}
void P1(int contador){
    switch (contador) {
      case 0:
   
      digitalWrite( relayA_av2_A,HIGH);
       digitalWrite( relayB_av2_B,HIGH);
       
        break;
      case 1:
         digitalWrite( relayA_av2_A,LOW);
       digitalWrite( relayB_av2_B,LOW);
      
        break;
     
      default:
        
        break;
    } 
}
void P2(int contador){
    switch (contador) {
      case 0:
   
      digitalWrite(  relayP1_av2_A,HIGH);
       digitalWrite(  relayP2_av2_B,HIGH);
       
        break;
      case 1:
        digitalWrite(  relayP1_av2_A,LOW);
        digitalWrite(  relayP2_av2_B,LOW);
      
        break;
     
      default:
        
        break;
    } 
}



void case_D0_Av1(int contador){
    switch (contador) {
      case 0:
        cero_D0_Av1();
        break;
      case 1:
        uno_D0_Av1();
        break;
      case 2:
        dos_D0_Av1();
        break;
      case 3:
        tres_D0_Av1();
        break;
      case 4:
        cuatro_D0_Av1();
        break;
      case 5:
        cinco_D0_Av1();
        break;
      case 6:
        seis_D0_Av1();
        break;
      case 7:
        siete_D0_Av1();
        break;
      case 8:
        ocho_D0_Av1();
        break;
      case 9:
        nueve_D0_Av1();
        break;
      default:
      uno_D0_Av1();
        break;
    } 
}

void case_D1_Av1(int contador){
    switch (contador) {
      case 0:
        cero_D1_Av1();
        break;
      case 1:
        uno_D1_Av1();
        break;
      case 2:
        dos_D1_Av1();
        break;
      case 3:
        tres_D1_Av1();
        break;
      case 4:
        cuatro_D1_Av1();
        break;
      case 5:
        cinco_D1_Av1();
        break;
      case 6:
        seis_D1_Av1();
        break;
      case 7:
        siete_D1_Av1();
        break;
      case 8:
        ocho_D1_Av1();
        break;
      case 9:
        nueve_D1_Av1();
        break;
      default:
       uno_D1_Av1();
        break;
    } 
}

void case_D2_Av1(int contador){
    switch (contador) {
      case 0:
        cero_D2_Av1();
        break;
      case 1:
        uno_D2_Av1();
        break;
      case 2:
        dos_D2_Av1();
        break;
      case 3:
        tres_D2_Av1();
        break;
      case 4:
        cuatro_D2_Av1();
        break;
      case 5:
        cinco_D2_Av1();
        break;
      case 6:
        seis_D2_Av1();
        break;
      case 7:
        siete_D2_Av1();
        break;
      case 8:
        ocho_D2_Av1();
        break;
      case 9:
        nueve_D2_Av1();
        break;
      default:
         uno_D2_Av1();
        break;
    } 
}

void case_D3_Av1(int contador){
    switch (contador) {
      case 0:
        cero_D3_Av1();
        break;
      case 1:
        uno_D3_Av1();
        break;
      case 2:
        dos_D3_Av1();
        break;
      case 3:
        tres_D3_Av1();
        break;
      case 4:
        cuatro_D3_Av1();
        break;
      case 5:
        cinco_D3_Av1();
        break;
      case 6:
        seis_D3_Av1();
        break;
      case 7:
        siete_D3_Av1();
        break;
      case 8:
        ocho_D3_Av1();
        break;
      case 9:
        nueve_D3_Av1();
        break;
      default:
          uno_D3_Av1();
        break;
    } 
}

void case_D4_Av2(int contador){
    switch (contador) {
      case 0:
        cero_D4_Av1();
        break;
      case 1:
        uno_D4_Av1();
        break;
      case 2:
        dos_D4_Av1();
        break;
      case 3:
        tres_D4_Av1();
        break;
      case 4:
        cuatro_D4_Av1();
        break;
      case 5:
        cinco_D4_Av1();
        break;
      case 6:
        seis_D4_Av1();
        break;
      case 7:
        siete_D4_Av1();
        break;
      case 8:
        ocho_D4_Av1();
        break;
      case 9:
        nueve_D4_Av1();
        break;
      default:
        uno_D4_Av1();
        break;
    } 
}

void case_D5_Av2(int contador){
    switch (contador) {
      case 0:
        cero_D5_Av1();
        break;
      case 1:
        uno_D5_Av1();
        break;
      case 2:
        dos_D5_Av1();
        break;
      case 3:
        tres_D5_Av1();
        break;
      case 4:
        cuatro_D5_Av1();
        break;
      case 5:
        cinco_D5_Av1();
        break;
      case 6:
        seis_D5_Av1();
        break;
      case 7:
        siete_D5_Av1();
        break;
      case 8:
        ocho_D5_Av1();
        break;
      case 9:
        nueve_D5_Av1();
        break;
      default:
       uno_D5_Av1();
        break;
    } 
}

void case_D6_Av2(int contador){
  
    switch (contador) {
      case 0:
        cero_D6_Av1();
        break;
      case 1:
        uno_D6_Av1();
        break;
      case 2:
        dos_D6_Av1();
        break;
      case 3:
        tres_D6_Av1();
        break;
      case 4:
        cuatro_D6_Av1();
        break;
      case 5:
        cinco_D6_Av1();
        break;
      case 6:
        seis_D6_Av1();
        break;
      case 7:
        siete_D6_Av1();
        break;
      case 8:
        ocho_D6_Av1();
        break;
      case 9:
        nueve_D6_Av1();
        break;
      default:
       uno_D6_Av1();
        break;
    } 
}
void case_D7_Av2(int contador){
    switch (contador) {
      case 0:
        cero_D7_Av1();
        break;
      case 1:
        uno_D7_Av1();
        break;
      case 2:
        dos_D7_Av1();
        break;
      case 3:
        tres_D7_Av1();
        break;
      case 4:
        cuatro_D7_Av1();
        break;
      case 5:
        cinco_D7_Av1();
        break;
      case 6:
        seis_D7_Av1();
        break;
      case 7:
        siete_D7_Av1();
        break;
      case 8:
        ocho_D7_Av1();
        break;
      case 9:
        nueve_D7_Av1();
        break;
      default:
       uno_D7_Av1();
        break;
    } 
}


void cero_D0_Av1(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,LOW);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,HIGH);
  }

void uno_D0_Av1(){
  digitalWrite(relay1_av1_A,HIGH);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,HIGH);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,HIGH);
  digitalWrite(relay7_av1_G,HIGH);
  }

void dos_D0_Av1(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,HIGH);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,LOW);
  digitalWrite(relay6_av1_F,HIGH);
  digitalWrite(relay7_av1_G,LOW);
  }

void tres_D0_Av1(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,HIGH);
  digitalWrite(relay7_av1_G,LOW);
  }

void cuatro_D0_Av1(){
  digitalWrite(relay1_av1_A,HIGH);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,HIGH);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
  }

void  cinco_D0_Av1(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,HIGH);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
  }

void  seis_D0_Av1(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,HIGH);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,LOW);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
  }

void  siete_D0_Av1(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,HIGH);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,HIGH);
  digitalWrite(relay7_av1_G,HIGH);
  }

void  ocho_D0_Av1(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,LOW);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
}

void  nueve_D0_Av1(){
  digitalWrite(relay1_av1_A,LOW);
  digitalWrite(relay2_av1_B,LOW);
  digitalWrite(relay3_av1_C,LOW);
  digitalWrite(relay4_av1_D,LOW);
  digitalWrite(relay5_av1_E,HIGH);
  digitalWrite(relay6_av1_F,LOW);
  digitalWrite(relay7_av1_G,LOW);
}


void cero_D1_Av1(){
  digitalWrite(relay8_av1_A,LOW);
  digitalWrite(relay9_av1_B,LOW);
  digitalWrite(relay10_av1_C,LOW);
  digitalWrite(relay11_av1_D,LOW);
  digitalWrite(relay12_av1_E,LOW);
  digitalWrite(relay13_av1_F,LOW);
  digitalWrite(relay14_av1_G,HIGH);
  }

void uno_D1_Av1(){
  digitalWrite(relay8_av1_A,HIGH);
  digitalWrite(relay9_av1_B,LOW);
  digitalWrite(relay10_av1_C,LOW);
  digitalWrite(relay11_av1_D,HIGH);
  digitalWrite(relay12_av1_E,HIGH);
  digitalWrite(relay13_av1_F,HIGH);
  digitalWrite(relay14_av1_G,HIGH);
  }

void dos_D1_Av1(){
  digitalWrite(relay8_av1_A,LOW);
  digitalWrite(relay9_av1_B,LOW);
  digitalWrite(relay10_av1_C,HIGH);
  digitalWrite(relay11_av1_D,LOW);
  digitalWrite(relay12_av1_E,LOW);
  digitalWrite(relay13_av1_F,HIGH);
  digitalWrite(relay14_av1_G,LOW);
  }

void tres_D1_Av1(){
  digitalWrite(relay8_av1_A,LOW);
  digitalWrite(relay9_av1_B,LOW);
  digitalWrite(relay10_av1_C,LOW);
  digitalWrite(relay11_av1_D,LOW);
  digitalWrite(relay12_av1_E,HIGH);
  digitalWrite(relay13_av1_F,HIGH);
  digitalWrite(relay14_av1_G,LOW);
  }

void cuatro_D1_Av1(){
  digitalWrite(relay8_av1_A,HIGH);
  digitalWrite(relay9_av1_B,LOW);
  digitalWrite(relay10_av1_C,LOW);
  digitalWrite(relay11_av1_D,HIGH);
  digitalWrite(relay12_av1_E,HIGH);
  digitalWrite(relay13_av1_F,LOW);
  digitalWrite(relay14_av1_G,LOW);
  }

void  cinco_D1_Av1(){
  digitalWrite(relay8_av1_A,LOW);
  digitalWrite(relay9_av1_B,HIGH);
  digitalWrite(relay10_av1_C,LOW);
  digitalWrite(relay11_av1_D,LOW);
  digitalWrite(relay12_av1_E,HIGH);
  digitalWrite(relay13_av1_F,LOW);
  digitalWrite(relay14_av1_G,LOW);
  }

void  seis_D1_Av1(){
  digitalWrite(relay8_av1_A,LOW);
  digitalWrite(relay9_av1_B,HIGH);
  digitalWrite(relay10_av1_C,LOW);
  digitalWrite(relay11_av1_D,LOW);
  digitalWrite(relay12_av1_E,LOW);
  digitalWrite(relay13_av1_F,LOW);
  digitalWrite(relay14_av1_G,LOW);
  }

void  siete_D1_Av1(){
  digitalWrite(relay8_av1_A,LOW);
  digitalWrite(relay9_av1_B,LOW);
  digitalWrite(relay10_av1_C,LOW);
  digitalWrite(relay11_av1_D,HIGH);
  digitalWrite(relay12_av1_E,HIGH);
  digitalWrite(relay13_av1_F,HIGH);
  digitalWrite(relay14_av1_G,HIGH);
  }

void  ocho_D1_Av1(){
  digitalWrite(relay8_av1_A,LOW);
  digitalWrite(relay9_av1_B,LOW);
  digitalWrite(relay10_av1_C,LOW);
  digitalWrite(relay11_av1_D,LOW);
  digitalWrite(relay12_av1_E,LOW);
  digitalWrite(relay13_av1_F,LOW);
  digitalWrite(relay14_av1_G,LOW);
}

void  nueve_D1_Av1(){
  digitalWrite(relay8_av1_A,LOW);
  digitalWrite(relay9_av1_B,LOW);
  digitalWrite(relay10_av1_C,LOW);
  digitalWrite(relay11_av1_D,LOW);
  digitalWrite(relay12_av1_E,HIGH);
  digitalWrite(relay13_av1_F,LOW);
  digitalWrite(relay14_av1_G,LOW);
}
 
void cero_D2_Av1(){
  digitalWrite(relay15_av1_A,LOW);
  digitalWrite(relay16_av1_B,LOW);
  digitalWrite(relay17_av1_C,LOW);
  digitalWrite(relay18_av1_D,LOW);
  digitalWrite(relay19_av1_E,LOW);
  digitalWrite(relay20_av1_F,LOW);
  digitalWrite(relay21_av1_G,HIGH);
  }

void uno_D2_Av1(){
  digitalWrite(relay15_av1_A,HIGH);
  digitalWrite(relay16_av1_B,LOW);
  digitalWrite(relay17_av1_C,LOW);
  digitalWrite(relay18_av1_D,HIGH);
  digitalWrite(relay19_av1_E,HIGH);
  digitalWrite(relay20_av1_F,HIGH);
  digitalWrite(relay21_av1_G,HIGH);
  }

void dos_D2_Av1(){
  digitalWrite(relay15_av1_A,LOW);
  digitalWrite(relay16_av1_B,LOW);
  digitalWrite(relay17_av1_C,HIGH);
  digitalWrite(relay18_av1_D,LOW);
  digitalWrite(relay19_av1_E,LOW);
  digitalWrite(relay20_av1_F,HIGH);
  digitalWrite(relay21_av1_G,LOW);
  }

void tres_D2_Av1(){
  digitalWrite(relay15_av1_A,LOW);
  digitalWrite(relay16_av1_B,LOW);
  digitalWrite(relay17_av1_C,LOW);
  digitalWrite(relay18_av1_D,LOW);
  digitalWrite(relay19_av1_E,HIGH);
  digitalWrite(relay20_av1_F,HIGH);
  digitalWrite(relay21_av1_G,LOW);
  }

void cuatro_D2_Av1(){
  digitalWrite(relay15_av1_A,HIGH);
  digitalWrite(relay16_av1_B,LOW);
  digitalWrite(relay17_av1_C,LOW);
  digitalWrite(relay18_av1_D,HIGH);
  digitalWrite(relay19_av1_E,HIGH);
  digitalWrite(relay20_av1_F,LOW);
  digitalWrite(relay21_av1_G,LOW);
  }

void  cinco_D2_Av1(){
  digitalWrite(relay15_av1_A,LOW);
  digitalWrite(relay16_av1_B,HIGH);
  digitalWrite(relay17_av1_C,LOW);
  digitalWrite(relay18_av1_D,LOW);
  digitalWrite(relay19_av1_E,HIGH);
  digitalWrite(relay20_av1_F,LOW);
  digitalWrite(relay21_av1_G,LOW);
  }

void  seis_D2_Av1(){
  digitalWrite(relay15_av1_A,LOW);
  digitalWrite(relay16_av1_B,HIGH);
  digitalWrite(relay17_av1_C,LOW);
  digitalWrite(relay18_av1_D,LOW);
  digitalWrite(relay19_av1_E,LOW);
  digitalWrite(relay20_av1_F,LOW);
  digitalWrite(relay21_av1_G,LOW);
  }

void  siete_D2_Av1(){
  digitalWrite(relay15_av1_A,LOW);
  digitalWrite(relay16_av1_B,LOW);
  digitalWrite(relay17_av1_C,LOW);
  digitalWrite(relay18_av1_D,HIGH);
  digitalWrite(relay19_av1_E,HIGH);
  digitalWrite(relay20_av1_F,HIGH);
  digitalWrite(relay21_av1_G,HIGH);
  }

void  ocho_D2_Av1(){
  digitalWrite(relay15_av1_A,LOW);
  digitalWrite(relay16_av1_B,LOW);
  digitalWrite(relay17_av1_C,LOW);
  digitalWrite(relay18_av1_D,LOW);
  digitalWrite(relay19_av1_E,LOW);
  digitalWrite(relay20_av1_F,LOW);
  digitalWrite(relay21_av1_G,LOW);
}

void  nueve_D2_Av1(){
  digitalWrite(relay15_av1_A,LOW);
  digitalWrite(relay16_av1_B,LOW);
  digitalWrite(relay17_av1_C,LOW);
  digitalWrite(relay18_av1_D,LOW);
  digitalWrite(relay19_av1_E,HIGH);
  digitalWrite(relay20_av1_F,LOW);
  digitalWrite(relay21_av1_G,LOW);
}
 
void cero_D3_Av1(){
  digitalWrite(relay22_av1_A,LOW);
  digitalWrite(relay23_av1_B,LOW);
  digitalWrite(relay24_av1_C,LOW);
  digitalWrite(relay25_av1_D,LOW);
  digitalWrite(relay26_av1_E,LOW);
  digitalWrite(relay27_av1_F,LOW);
  digitalWrite(relay28_av1_G,HIGH);
  }

void uno_D3_Av1(){
  digitalWrite(relay22_av1_A,HIGH);
  digitalWrite(relay23_av1_B,LOW);
  digitalWrite(relay24_av1_C,LOW);
  digitalWrite(relay25_av1_D,HIGH);
  digitalWrite(relay26_av1_E,HIGH);
  digitalWrite(relay27_av1_F,HIGH);
  digitalWrite(relay28_av1_G,HIGH);
  }

void dos_D3_Av1(){
  digitalWrite(relay22_av1_A,LOW);
  digitalWrite(relay23_av1_B,LOW);
  digitalWrite(relay24_av1_C,HIGH);
  digitalWrite(relay25_av1_D,LOW);
  digitalWrite(relay26_av1_E,LOW);
  digitalWrite(relay27_av1_F,HIGH);
  digitalWrite(relay28_av1_G,LOW);
  }

void tres_D3_Av1(){
  digitalWrite(relay22_av1_A,LOW);
  digitalWrite(relay23_av1_B,LOW);
  digitalWrite(relay24_av1_C,LOW);
  digitalWrite(relay25_av1_D,LOW);
  digitalWrite(relay26_av1_E,HIGH);
  digitalWrite(relay27_av1_F,HIGH);
  digitalWrite(relay28_av1_G,LOW);
  }

void cuatro_D3_Av1(){
  digitalWrite(relay22_av1_A,HIGH);
  digitalWrite(relay23_av1_B,LOW);
  digitalWrite(relay24_av1_C,LOW);
  digitalWrite(relay25_av1_D,HIGH);
  digitalWrite(relay26_av1_E,HIGH);
  digitalWrite(relay27_av1_F,LOW);
  digitalWrite(relay28_av1_G,LOW);
  }

void  cinco_D3_Av1(){
  digitalWrite(relay22_av1_A,LOW);
  digitalWrite(relay23_av1_B,HIGH);
  digitalWrite(relay24_av1_C,LOW);
  digitalWrite(relay25_av1_D,LOW);
  digitalWrite(relay26_av1_E,HIGH);
  digitalWrite(relay27_av1_F,LOW);
  digitalWrite(relay28_av1_G,LOW);
  }

void  seis_D3_Av1(){
  digitalWrite(relay22_av1_A,LOW);
  digitalWrite(relay23_av1_B,HIGH);
  digitalWrite(relay24_av1_C,LOW);
  digitalWrite(relay25_av1_D,LOW);
  digitalWrite(relay26_av1_E,LOW);
  digitalWrite(relay27_av1_F,LOW);
  digitalWrite(relay28_av1_G,LOW);
  }

void  siete_D3_Av1(){
  digitalWrite(relay22_av1_A,LOW);
  digitalWrite(relay23_av1_B,LOW);
  digitalWrite(relay24_av1_C,LOW);
  digitalWrite(relay25_av1_D,HIGH);
  digitalWrite(relay26_av1_E,HIGH);
  digitalWrite(relay27_av1_F,HIGH);
  digitalWrite(relay28_av1_G,HIGH);
  }

void  ocho_D3_Av1(){
  digitalWrite(relay22_av1_A,LOW);
  digitalWrite(relay23_av1_B,LOW);
  digitalWrite(relay24_av1_C,LOW);
  digitalWrite(relay25_av1_D,LOW);
  digitalWrite(relay26_av1_E,LOW);
  digitalWrite(relay27_av1_F,LOW);
  digitalWrite(relay28_av1_G,LOW);
}

void  nueve_D3_Av1(){
  digitalWrite(relay22_av1_A,LOW);
  digitalWrite(relay23_av1_B,LOW);
  digitalWrite(relay24_av1_C,LOW);
  digitalWrite(relay25_av1_D,LOW);
  digitalWrite(relay26_av1_E,HIGH);
  digitalWrite(relay27_av1_F,LOW);
  digitalWrite(relay28_av1_G,LOW);
}


void cero_D4_Av1(){
  digitalWrite(31,LOW);
  digitalWrite(32,LOW);
  digitalWrite(33,LOW);
  digitalWrite(34,LOW);
  digitalWrite(35,LOW);
  digitalWrite(36,LOW);
  digitalWrite(37,HIGH);
  }

void uno_D4_Av1(){
   digitalWrite(31,HIGH);
  digitalWrite(32,LOW);
  digitalWrite(33,LOW);
  digitalWrite(34,HIGH);
  digitalWrite(35,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(37,HIGH);
 
  }

void dos_D4_Av1(){
  
  digitalWrite(31,LOW);
  digitalWrite(32,LOW);
  digitalWrite(33,HIGH);
  digitalWrite(34,LOW);
  digitalWrite(35,LOW);
  digitalWrite(36,HIGH);
  digitalWrite(37,LOW);
  }

void tres_D4_Av1(){
  digitalWrite(31,LOW);
  digitalWrite(32,LOW);
  digitalWrite(33,LOW);
  digitalWrite(34,LOW);
  digitalWrite(35,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(37,LOW);
  }

void cuatro_D4_Av1(){
  digitalWrite(31,HIGH);
  digitalWrite(32,LOW);
  digitalWrite(33,LOW);
  digitalWrite(34,HIGH);
  digitalWrite(35,HIGH);
  digitalWrite(36,LOW);
  digitalWrite(37,LOW);
  }

void  cinco_D4_Av1(){
  digitalWrite(31,LOW);
  digitalWrite(32,HIGH);
  digitalWrite(33,LOW);
  digitalWrite(34,LOW);
  digitalWrite(35,HIGH);
  digitalWrite(36,LOW);
  digitalWrite(37,LOW);
  }

void  seis_D4_Av1(){
  digitalWrite(31,LOW);
  digitalWrite(32,HIGH);
  digitalWrite(33,LOW);
  digitalWrite(34,LOW);
  digitalWrite(35,LOW);
  digitalWrite(36,LOW);
  digitalWrite(relay7_av2_G,LOW);
  }

void  siete_D4_Av1(){
  digitalWrite(relay1_av2_A,LOW);
  digitalWrite(relay2_av2_B,LOW);
  digitalWrite(relay3_av2_C,LOW);
  digitalWrite(relay4_av2_D,HIGH);
  digitalWrite(relay5_av2_E,HIGH);
  digitalWrite(relay6_av2_F,HIGH);
  digitalWrite(relay7_av2_G,HIGH);
  }

void  ocho_D4_Av1(){
  digitalWrite(relay1_av2_A,LOW);
  digitalWrite(relay2_av2_B,LOW);
  digitalWrite(relay3_av2_C,LOW);
  digitalWrite(relay4_av2_D,LOW);
  digitalWrite(relay5_av2_E,LOW);
  digitalWrite(relay6_av2_F,LOW);
  digitalWrite(relay7_av2_G,LOW);
}

void  nueve_D4_Av1(){
  digitalWrite(relay1_av2_A,LOW);
  digitalWrite(relay2_av2_B,LOW);
  digitalWrite(relay3_av2_C,LOW);
  digitalWrite(relay4_av2_D,LOW);
  digitalWrite(relay5_av2_E,HIGH);
  digitalWrite(relay6_av2_F,LOW);
  digitalWrite(relay7_av2_G,LOW);
}




void cero_D5_Av1(){
  digitalWrite(relay8_av2_A,LOW);
  digitalWrite(relay9_av2_B,LOW);
  digitalWrite(relay10_av2_C,LOW);
  digitalWrite(relay11_av2_D,LOW);
  digitalWrite(relay12_av2_E,LOW);
  digitalWrite(relay13_av2_F,LOW);
  digitalWrite(relay14_av2_G,HIGH);
  }

void uno_D5_Av1(){
  digitalWrite(relay8_av2_A,HIGH);
  digitalWrite(relay9_av2_B,LOW);
  digitalWrite(relay10_av2_C,LOW);
  digitalWrite(relay11_av2_D,HIGH);
  digitalWrite(relay12_av2_E,HIGH);
  digitalWrite(relay13_av2_F,HIGH);
  digitalWrite(relay14_av2_G,HIGH);
  }

void dos_D5_Av1(){
  digitalWrite(relay8_av2_A,LOW);
  digitalWrite(relay9_av2_B,LOW);
  digitalWrite(relay10_av2_C,HIGH);
  digitalWrite(relay11_av2_D,LOW);
  digitalWrite(relay12_av2_E,LOW);
  digitalWrite(relay13_av2_F,HIGH);
  digitalWrite(relay14_av2_G,LOW);
  }

void tres_D5_Av1(){
  digitalWrite(relay8_av2_A,LOW);
  digitalWrite(relay9_av2_B,LOW);
  digitalWrite(relay10_av2_C,LOW);
  digitalWrite(relay11_av2_D,LOW);
  digitalWrite(relay12_av2_E,HIGH);
  digitalWrite(relay13_av2_F,HIGH);
  digitalWrite(relay14_av2_G,LOW);
  }

void cuatro_D5_Av1(){
  digitalWrite(relay8_av2_A,HIGH);
  digitalWrite(relay9_av2_B,LOW);
  digitalWrite(relay10_av2_C,LOW);
  digitalWrite(relay11_av2_D,HIGH);
  digitalWrite(relay12_av2_E,HIGH);
  digitalWrite(relay13_av2_F,LOW);
  digitalWrite(relay14_av2_G,LOW);
  }

void  cinco_D5_Av1(){
  digitalWrite(relay8_av2_A,LOW);
  digitalWrite(relay9_av2_B,HIGH);
  digitalWrite(relay10_av2_C,LOW);
  digitalWrite(relay11_av2_D,LOW);
  digitalWrite(relay12_av2_E,HIGH);
  digitalWrite(relay13_av2_F,LOW);
  digitalWrite(relay14_av2_G,LOW);
  }

void  seis_D5_Av1(){
  digitalWrite(relay8_av2_A,LOW);
  digitalWrite(relay9_av2_B,HIGH);
  digitalWrite(relay10_av2_C,LOW);
  digitalWrite(relay11_av2_D,LOW);
  digitalWrite(relay12_av2_E,LOW);
  digitalWrite(relay13_av2_F,LOW);
  digitalWrite(relay14_av2_G,LOW);
  }

void  siete_D5_Av1(){
  digitalWrite(relay8_av2_A,LOW);
  digitalWrite(relay9_av2_B,LOW);
  digitalWrite(relay10_av2_C,LOW);
  digitalWrite(relay11_av2_D,HIGH);
  digitalWrite(relay12_av2_E,HIGH);
  digitalWrite(relay13_av2_F,HIGH);
  digitalWrite(relay14_av2_G,HIGH);
  }

void  ocho_D5_Av1(){
  digitalWrite(relay8_av2_A,LOW);
  digitalWrite(relay9_av2_B,LOW);
  digitalWrite(relay10_av2_C,LOW);
  digitalWrite(relay11_av2_D,LOW);
  digitalWrite(relay12_av2_E,LOW);
  digitalWrite(relay13_av2_F,LOW);
  digitalWrite(relay14_av2_G,LOW);
}

void  nueve_D5_Av1(){
  digitalWrite(relay8_av2_A,LOW);
  digitalWrite(relay9_av2_B,LOW);
  digitalWrite(relay10_av2_C,LOW);
  digitalWrite(relay11_av2_D,LOW);
  digitalWrite(relay12_av2_E,HIGH);
  digitalWrite(relay13_av2_F,LOW);
  digitalWrite(relay14_av2_G,LOW);
}




 void cero_D6_Av1(){
  digitalWrite(relay15_av2_A,LOW);
  digitalWrite(relay16_av2_B,LOW);
  digitalWrite(relay17_av2_C,LOW);
  digitalWrite(relay18_av2_D,LOW);
  digitalWrite(relay19_av2_E,LOW);
  digitalWrite(relay20_av2_F,LOW);
  digitalWrite(relay21_av2_G,HIGH);
  }

void uno_D6_Av1(){
  digitalWrite(relay15_av2_A,HIGH);
  digitalWrite(relay16_av2_B,LOW);
  digitalWrite(relay17_av2_C,LOW);
  digitalWrite(relay18_av2_D,HIGH);
  digitalWrite(relay19_av2_E,HIGH);
  digitalWrite(relay20_av2_F,HIGH);
  digitalWrite(relay21_av2_G,HIGH);
  }

void dos_D6_Av1(){
  digitalWrite(relay15_av2_A,LOW);
  digitalWrite(relay16_av2_B,LOW);
  digitalWrite(relay17_av2_C,HIGH);
  digitalWrite(relay18_av2_D,LOW);
  digitalWrite(relay19_av2_E,LOW);
  digitalWrite(relay20_av2_F,HIGH);
  digitalWrite(relay21_av2_G,LOW);
  }

void tres_D6_Av1(){
  digitalWrite(relay15_av2_A,LOW);
  digitalWrite(relay16_av2_B,LOW);
  digitalWrite(relay17_av2_C,LOW);
  digitalWrite(relay18_av2_D,LOW);
  digitalWrite(relay19_av2_E,HIGH);
  digitalWrite(relay20_av2_F,HIGH);
  digitalWrite(relay21_av2_G,LOW);
  }

void cuatro_D6_Av1(){
  digitalWrite(relay15_av2_A,HIGH);
  digitalWrite(relay16_av2_B,LOW);
  digitalWrite(relay17_av2_C,LOW);
  digitalWrite(relay18_av2_D,HIGH);
  digitalWrite(relay19_av2_E,HIGH);
  digitalWrite(relay20_av2_F,LOW);
  digitalWrite(relay21_av2_G,LOW);
  }

void  cinco_D6_Av1(){
  digitalWrite(relay15_av2_A,LOW);
  digitalWrite(relay16_av2_B,HIGH);
  digitalWrite(relay17_av2_C,LOW);
  digitalWrite(relay18_av2_D,LOW);
  digitalWrite(relay19_av2_E,HIGH);
  digitalWrite(relay20_av2_F,LOW);
  digitalWrite(relay21_av2_G,LOW);
  }

void  seis_D6_Av1(){
  digitalWrite(relay15_av2_A,LOW);
  digitalWrite(relay16_av2_B,HIGH);
  digitalWrite(relay17_av2_C,LOW);
  digitalWrite(relay18_av2_D,LOW);
  digitalWrite(relay19_av2_E,LOW);
  digitalWrite(relay20_av2_F,LOW);
  digitalWrite(relay21_av2_G,LOW);
  }

void  siete_D6_Av1(){
  digitalWrite(relay15_av2_A,LOW);
  digitalWrite(relay16_av2_B,LOW);
  digitalWrite(relay17_av2_C,LOW);
  digitalWrite(relay18_av2_D,HIGH);
  digitalWrite(relay19_av2_E,HIGH);
  digitalWrite(relay20_av2_F,HIGH);
  digitalWrite(relay21_av2_G,HIGH);
  }

void  ocho_D6_Av1(){
  digitalWrite(relay15_av2_A,LOW);
  digitalWrite(relay16_av2_B,LOW);
  digitalWrite(relay17_av2_C,LOW);
  digitalWrite(relay18_av2_D,LOW);
  digitalWrite(relay19_av2_E,LOW);
  digitalWrite(relay20_av2_F,LOW);
  digitalWrite(relay21_av2_G,LOW);
}

void  nueve_D6_Av1(){
  digitalWrite(relay15_av2_A,LOW);
  digitalWrite(relay16_av2_B,LOW);
  digitalWrite(relay17_av2_C,LOW);
  digitalWrite(relay18_av2_D,LOW);
  digitalWrite(relay19_av2_E,HIGH);
  digitalWrite(relay20_av2_F,LOW);
  digitalWrite(relay21_av2_G,LOW);
}

///

 void cero_D7_Av1(){
  digitalWrite(relay22_av2_A,LOW);
  digitalWrite(relay23_av2_B,LOW);
  digitalWrite(relay24_av2_C,LOW);
  digitalWrite(relay25_av2_D,LOW);
  digitalWrite(relay26_av2_E,LOW);
  digitalWrite(relay27_av2_F,LOW);
  digitalWrite(relay28_av2_G,HIGH);
  }

void uno_D7_Av1(){
  digitalWrite(relay22_av2_A,HIGH);
  digitalWrite(relay23_av2_B,LOW);
  digitalWrite(relay24_av2_C,LOW);
  digitalWrite(relay25_av2_D,HIGH);
  digitalWrite(relay26_av2_E,HIGH);
  digitalWrite(relay27_av2_F,HIGH);
  digitalWrite(relay28_av2_G,HIGH);
  }

void dos_D7_Av1(){
  digitalWrite(relay22_av2_A,LOW);
  digitalWrite(relay23_av2_B,LOW);
  digitalWrite(relay24_av2_C,HIGH);
  digitalWrite(relay25_av2_D,LOW);
  digitalWrite(relay26_av2_E,LOW);
  digitalWrite(relay27_av2_F,HIGH);
  digitalWrite(relay28_av2_G,LOW);
  }

void tres_D7_Av1(){
  digitalWrite(relay22_av2_A,LOW);
  digitalWrite(relay23_av2_B,LOW);
  digitalWrite(relay24_av2_C,LOW);
  digitalWrite(relay25_av2_D,LOW);
  digitalWrite(relay26_av2_E,HIGH);
  digitalWrite(relay27_av2_F,HIGH);
  digitalWrite(relay28_av2_G,LOW);
  }

void cuatro_D7_Av1(){
  digitalWrite(relay22_av2_A,HIGH);
  digitalWrite(relay23_av2_B,LOW);
  digitalWrite(relay24_av2_C,LOW);
  digitalWrite(relay25_av2_D,HIGH);
  digitalWrite(relay26_av2_E,HIGH);
  digitalWrite(relay27_av2_F,LOW);
  digitalWrite(relay28_av2_G,LOW);
  }

void  cinco_D7_Av1(){
  digitalWrite(relay22_av2_A,LOW);
  digitalWrite(relay23_av2_B,HIGH);
  digitalWrite(relay24_av2_C,LOW);
  digitalWrite(relay25_av2_D,LOW);
  digitalWrite(relay26_av2_E,HIGH);
  digitalWrite(relay27_av2_F,LOW);
  digitalWrite(relay28_av2_G,LOW);
  }

void  seis_D7_Av1(){
  digitalWrite(relay22_av2_A,LOW);
  digitalWrite(relay23_av2_B,HIGH);
  digitalWrite(relay24_av2_C,LOW);
  digitalWrite(relay25_av2_D,LOW);
  digitalWrite(relay26_av2_E,LOW);
  digitalWrite(relay27_av2_F,LOW);
  digitalWrite(relay28_av2_G,LOW);
  }

void  siete_D7_Av1(){
  digitalWrite(relay22_av2_A,LOW);
  digitalWrite(relay23_av2_B,LOW);
  digitalWrite(relay24_av2_C,LOW);
  digitalWrite(relay25_av2_D,HIGH);
  digitalWrite(relay26_av2_E,HIGH);
  digitalWrite(relay27_av2_F,HIGH);
  digitalWrite(relay28_av2_G,HIGH);
  }

void  ocho_D7_Av1(){
  digitalWrite(relay22_av2_A,LOW);
  digitalWrite(relay23_av2_B,LOW);
  digitalWrite(relay24_av2_C,LOW);
  digitalWrite(relay25_av2_D,LOW);
  digitalWrite(relay26_av2_E,LOW);
  digitalWrite(relay27_av2_F,LOW);
  digitalWrite(relay28_av2_G,LOW);
}

void  nueve_D7_Av1(){
  digitalWrite(relay22_av2_A,LOW);
  digitalWrite(relay23_av2_B,LOW);
  digitalWrite(relay24_av2_C,LOW);
  digitalWrite(relay25_av2_D,LOW);
  digitalWrite(relay26_av2_E,HIGH);
  digitalWrite(relay27_av2_F,LOW);
  digitalWrite(relay28_av2_G,LOW);
}






 void star(){
  digitalWrite(0,HIGH);
digitalWrite(1,HIGH);
digitalWrite(2,HIGH);
digitalWrite(3,HIGH);
digitalWrite(4,HIGH);
digitalWrite(5,HIGH);
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
digitalWrite(10,HIGH);
digitalWrite(11,HIGH);
digitalWrite(12,HIGH);
digitalWrite(13,HIGH);
digitalWrite(14,HIGH);
digitalWrite(15,HIGH);
digitalWrite(16,HIGH);
digitalWrite(17,HIGH);
digitalWrite(18,HIGH);
digitalWrite(19,HIGH);
digitalWrite(20,HIGH);
digitalWrite(21,HIGH);
digitalWrite(22,HIGH);
digitalWrite(23,HIGH);
digitalWrite(24,HIGH);
digitalWrite(25,HIGH);
digitalWrite(26,HIGH);
digitalWrite(27,HIGH);
digitalWrite(28,HIGH);
digitalWrite(29,HIGH);
digitalWrite(30,HIGH);
digitalWrite(31,HIGH);
digitalWrite(32,HIGH);
digitalWrite(33,HIGH);
digitalWrite(34,HIGH);
digitalWrite(35,HIGH);
digitalWrite(36,HIGH);
digitalWrite(37,HIGH);
digitalWrite(38,HIGH);
digitalWrite(39,HIGH);
digitalWrite(40,HIGH);
digitalWrite(41,HIGH);
digitalWrite(42,HIGH);
digitalWrite(43,HIGH);
digitalWrite(44,HIGH);
digitalWrite(45,HIGH);
digitalWrite(46,HIGH);
digitalWrite(47,HIGH);
digitalWrite(48,HIGH);
digitalWrite(49,HIGH);
digitalWrite(50,HIGH);
digitalWrite(51,HIGH);
digitalWrite(52,HIGH);
digitalWrite(53,HIGH);
digitalWrite(54,HIGH);
digitalWrite(55,HIGH);
digitalWrite(56,HIGH);
digitalWrite(57,HIGH);
digitalWrite(58,HIGH);
digitalWrite(59,HIGH);
digitalWrite(60,HIGH);
 /*
  *  for (int i = 0; i<61; i++){
    digitalWrite(i,HIGH);
    delay(10);
  }
digitalWrite(0,LOW);
digitalWrite(1,HIGH);
digitalWrite(2,HIGH);
digitalWrite(3,HIGH);
digitalWrite(4,LOW);
digitalWrite(5,LOW);
digitalWrite(6,HIGH);
digitalWrite(7,LOW);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
digitalWrite(10,HIGH);
digitalWrite(11,LOW);
digitalWrite(12,LOW);
digitalWrite(13,HIGH);
digitalWrite(14,LOW);
digitalWrite(15,LOW);
digitalWrite(16,LOW);
digitalWrite(17,HIGH);
digitalWrite(18,LOW);
digitalWrite(19,LOW);
digitalWrite(20,LOW);
digitalWrite(21,LOW);
digitalWrite(22,LOW);
digitalWrite(23,LOW);
digitalWrite(24,LOW);
digitalWrite(25,LOW);
digitalWrite(26,LOW);
digitalWrite(27,LOW);
digitalWrite(28,HIGH);
digitalWrite(29,HIGH);
digitalWrite(30,HIGH);
digitalWrite(31,HIGH);
digitalWrite(32,HIGH);
digitalWrite(33,HIGH);
digitalWrite(34,HIGH);
digitalWrite(35,HIGH);
digitalWrite(36,HIGH);
digitalWrite(37,HIGH);
digitalWrite(38,LOW);
digitalWrite(39,LOW);
digitalWrite(40,LOW);
digitalWrite(41,LOW);
digitalWrite(42,LOW);
digitalWrite(43,LOW);
digitalWrite(44,HIGH);
digitalWrite(45,LOW);
digitalWrite(46,LOW);
digitalWrite(47,LOW);
digitalWrite(48,HIGH);
digitalWrite(49,LOW);
digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
digitalWrite(54,LOW);
digitalWrite(55,HIGH);
digitalWrite(56,HIGH);
digitalWrite(57,HIGH);
digitalWrite(58,HIGH);
digitalWrite(59,HIGH);
digitalWrite(60,HIGH);
*/}
