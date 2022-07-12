#include "sky.h"


sky::sky(){

}
//Funciones de configuracion segun la tarjeta
void sky::Wizard(){//Configuracion del Wizard
/*
Wizard es una tarjeta electronica diseñada para robotica general
contiene las siguientes conexiones:
  *Entradas
    -Boton D14
    -Sensor Bateria A1
    - 7 pines digitales (A11,D16,A0,A9,A6,D7,A8), los A puenden ser analogos
    -Receptor D1 TX
  *Salidas
    -Motor MA(D5-D6)
    -Motor MB(D10-D11)
    -Parlante D0 RX
*/
  //Asignacion de salidas
  //Asignacion de pines de salida Motor A
  pinMode(13,OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  //Asignacion de pines de salida Motor B
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  wizard=1;
}

void sky::Linebot(){//Configuracion del Linebot
/*
Linebot es un robot Seguidor de lineas educativo.
contiene las siguientes conexiones:
  *Entradas
    -1 Boton D12
    -8 sensores de linea Digitales D4, D7, D8, D16, D15, D19,D18
    -1 Led-On habilitador de los sensores D14
  *Salidas
    -1 Motor MA(D5-D6)
    -1 Motor MB(D10-D11)
    -1 LED D13
  *Comunicacion
    -1 Serial Rx D0, Tx D1
    -1 I2C SDA D2, SCL D3
*/
  //Asignacion de salidas
  //LLED 13
  pinMode(13,OUTPUT);
  //Asignacion de pines de salida Motor A
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  //Asignacion de pines de salida Motor B
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  //Asignacion de pines Sensor de línea
  pinMode(14, OUTPUT);//LED_ON
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(15, INPUT);
  pinMode(14, INPUT);
  pinMode(9,  INPUT);
  pinMode(8,  INPUT);
  pinMode(7,  INPUT);
  pinMode(4,  INPUT);
  linebot=1;
}

//Funciones de configuracion segun la tarjeta
void sky::SkyDragon(){//Configuracion del SkyDragon
/*
SkyDragon es una tarjeta electronica diseñada para robotica general
contiene las siguientes conexiones:
  *Entradas
    -Boton D4
    -Sensor Bateria A11
    - 9 pines digitales (A5,A4,A3,A2,A1,A0,D13,D10,D9), 6 pueden ser Analogos, 3 de PWM
  *Salidas
    -Motor MA(D6-D8)
    -Motor MB(D5-D7)
    -LED D11
  *Comunicacion
    -1 Serial Rx D0, Tx D1
    -1 I2C SDA D2, SCL D3
*/
  //Asignacion de salidas
  //LED 11
  pinMode(11,OUTPUT);
  //Asignacion de pines de salida Motor A
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  //Asignacion de pines de salida Motor B
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  skyDragon=1;
}

void sky::LineConfig(int _ns, int _s1, int _s2, int _s3, int _s4, int _s5, int _s6, int _s7, int _s8, int _LEDon){//nsen,s1,s2,s3,s4,s5,s6,s7,s8,LEDon
  ns=_ns, s1=_s1, s2=_s2, s3=_s3, s4=_s4, s5=_s5, s6=_s6, s7=_s7, s8=_s8, LEDon=_LEDon;
  //Convierte a digitales los sensores
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);
  digitalWrite(s8, HIGH);
  digitalWrite(LEDon,HIGH);
}
short sky::Boton(){//Lectura del botón
  if(wizard==1)
    return !digitalRead(14);
  if(linebot==1)
    return !digitalRead(12);
  if(skyDragon==1)
    return !digitalRead(4);
}

float sky::Battery(){//Lectura de la bateria
  //y lo multimplica por 2 ya que son dos baterias en serie.
  if(wizard==1)
    battery = 2*analogRead(A11) * (5.0 / 1023.0);
  if(skyDragon==1)
    battery = 3*analogRead(A11) * (5.0 / 1023.0);
  return battery;
}


float sky::LinePosDigital(){//Lectura del sensor de linea
  line1=digitalRead(s1);
  line2=digitalRead(s2);
  line3=digitalRead(s3);
  line4=digitalRead(s4);
  line5=digitalRead(s5);
  line6=digitalRead(s6);
  line7=digitalRead(s7);
  line8=digitalRead(s8);
  if(line1||line2||line3||line4||line5||line6||line7||line8){
  linePos=line1+ 2*line2+ 3*line3+ 4*line4+ 5*line5+ 6*line6+ 7*line7+ 8*line8;
    if (linePos>0){
    linePos=linePos/(line1+ line2+ line3+ line4+ line5+ line6+ line7+ line8);
    }
  }
  return linePos;
}



void sky::Speeds(int SpeedMA, int SpeedMB){//CONTROL DE MOTORES

  if(skyDragon == 1){//Control para la SkyDragon
    if(SpeedMA<0){
      digitalWrite(8, LOW);
      analogWrite(6, abs(SpeedMA));
    }
    else{
      digitalWrite(8, HIGH);
      analogWrite(6, abs(SpeedMA));
    }

    if(SpeedMB<0){
      digitalWrite(7, LOW);
      analogWrite(5, abs(SpeedMB));
    }
    else{
      digitalWrite(7, HIGH);
      analogWrite(5, abs(SpeedMB));
    }
  }
  else{//Control para las demas tarjetas
    //Orientacion de direccion MA
    if(SpeedMA<0){
      digitalWrite(6, LOW);
      analogWrite(5, abs(SpeedMA));
    }
    else{
      digitalWrite(5, LOW);
      analogWrite(6, abs(SpeedMA));
    }
    delay(1);//Es posible inhabilitarlo
       //Evita cambios bruscos de velocidad
    //Orientacion de direccion MB
    if(SpeedMB<0){
      digitalWrite(11, LOW);
      analogWrite(10, abs(SpeedMB));
    }
    else{
      digitalWrite(10, LOW);
      analogWrite(11, abs(SpeedMB));
    }
    delay(1);//Es posible inhabilitarlo
       //Evita cambios bruscos de velocidad
  }
}
