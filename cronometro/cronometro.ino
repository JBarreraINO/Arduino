
#include "LedControl.h"

// CRONÃ“METRO PARA ROBOTS VELOCISTAS
// AUTOR: ALEJANDRO TORRES
// FACEBOOK: AT ROBÃ“TICA 

#define inPin 7  //Pin de entrada sensor E18-D80NK
#define inPin2 4  //Pin de entrada sensor E18-D80NK
#define BUZZ A2   //Pin de entrada sensor E18-D80NK
#define LED1 A4   //Pin de entrada sensor E18-D80NK
#define LED2 A3   //Pin de entrada sensor E18-D80NK
#define tAR 200  //Tiempo de antirrebote, se debe configurar para evitar que se detenga el cronometro antes de que el robot de la vuelta completa [milisegundos]
#define tAct 10   //Periodo de envÃ­o de tiempo por puerto serial para evitar saturaciÃ³n [milisegundos]

LedControl lc=LedControl(12,11,10,1);

void setup() {
  pinMode (inPin, INPUT_PULLUP);
    pinMode (inPin2, INPUT_PULLUP);
  pinMode (13, OUTPUT);
    pinMode (LED1, OUTPUT);
      pinMode (LED2, OUTPUT);
        pinMode (BUZZ, OUTPUT);
  Serial.begin (9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,10);
  lc.clearDisplay(0);
}

bool contando = false;
long tInicial = 0;
float segundos = 0;
String cadena = "";

void reset (){
  segundos = 0;
  tInicial = millis ();
}

void loop() {

// CICLO MIENTRAS NO ESTA CORRIENDO EL TIEMPO
  while (contando == 0) {
    digitalWrite (LED2, HIGH);
    digitalWrite (LED1, LOW); 
    digitalWrite (BUZZ, LOW);
    display7();
    if (!digitalRead (inPin2)) {
      digitalWrite (BUZZ, HIGH);
      reset ();
      contando = true;
      delay (tAR);
      digitalWrite (BUZZ, LOW);
      break;
    }
  }

// CORRIENDO EL TIEMPO
  while (contando == 1) {
     
    digitalWrite (LED1, HIGH);
        digitalWrite (LED2, LOW);
    segundos =  (float) (millis () - tInicial) / 1000;
    display7();
    if (!digitalRead (inPin)) {
      digitalWrite (BUZZ, HIGH);
      delay (tAR);
      contando = false;
      digitalWrite (BUZZ, LOW);
      break;
    }
  }
}

int value = 0;
void display7(){
  String sec = String (segundos,3);
  if (segundos < 10){
    sec = "0"+sec;
  }
  int tam = sec.length();
  if (tam>0){
    lc.clearDisplay(0);
    int e = 0;
    for (int i=0; i<tam; i++){
      if (sec.charAt(i)!='.'){
        String v = "";
        v+= sec.charAt(i);
        value = v.toInt ();
        lc.setDigit(0,6-e,value,false);
        e++;
      }else{
        lc.setDigit(0,6-e+1,value,true);
      }
    }
  }
}
