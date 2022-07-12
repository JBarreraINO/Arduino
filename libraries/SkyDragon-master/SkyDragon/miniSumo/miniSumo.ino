/*
Programa Minisumo Wizard

Conexiones Necesarias:
*Wizard
  -Parlante D0
  -Motores MA Y MB
  -Boton D14
*Bateria 74.V
*Cable MicroUSB

*/

#include <sky.h>  //Libreria Skybots
sky Motors;       //Declaracion de los motores MA y MB

  int mem;         //Memoria de los sensores
  int sensorValue1;//A6 Sensor de distancia de la derecha 
  int sensorValue2;//A9 Sensor de distancia frontal a la derecha
  int sensorValue3;//A0 Sensor de distancia forntal a la izquierda
  int sensorValue4;//A11 Sensor de distancia de la izquierda
  
void setup() {//configuracion den entradas y salidas

  pinMode(7, INPUT);    //Sensor de linea de la derecha
  pinMode(16, INPUT);   //Sensor de linea de la izquerda
  digitalWrite(7,HIGH); //Configura la resistencia de puesta a vcc
  digitalWrite(16,HIGH);//Configura la resistencia de puesta a vcc
  
    while(digitalRead(14)==0){//espera a que se presione el boton 14
  }
  delay(5000);//Retardo de 5 segundos
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValueA1 = analogRead(A6);//A6 Sensor de distancia de la derecha 
  int sensorValueA2 = analogRead(A9);//A9 Sensor de distancia frontal a la derecha
  int sensorValueA3 = analogRead(A0);//A0 Sensor de distancia forntal a la izquierda
  int sensorValueA4 = analogRead(A11);//A11 Sensor de distancia de la izquierda
  
  //conversor analogo-digital del Sensor de distancia de la derecha 
  if(sensorValueA1> 450)//asigna un 1 si el objeto esta cerca
    sensorValue1=1;
  else//o asigna un 0 si el objeto esta lejos
  sensorValue1=0;
  
  //conversor analogo-digital del Sensor de distancia frontal a la derecha
  if(sensorValueA2> 450)//asigna un 1 si el objeto esta cerca
    sensorValue2=1;
  else//o asigna un 0 si el objeto esta lejos
  sensorValue2=0;
  
  //conversor analogo-digital del Sensor de distancia frontal a la izquierda
  if(sensorValueA3> 450)
    sensorValue3=1;
  else//o asigna un 0 si el objeto esta lejos
  sensorValue3=0;
  
  //conversor analogo-digital del Sensor de distancia de la izquierda
  if(sensorValueA4> 450)
    sensorValue4=1;
  else//o asigna un 0 si el objeto esta lejos
  sensorValue4=0;
  
  //Suma de todos los sensores para conocer la ubicacion del contrincante y la convierte en un numero entero 0-15
  int sensorValue= sensorValue1+ sensorValue2*2+ sensorValue3*4+ sensorValue4*8;
  //Serial.println(sensorValue);
  if(digitalRead(16)==1 && digitalRead(7)==1){//si esta dentro de doyo lucha
    switch (sensorValue){//sensorVulue es la variable de posicion del objeto
      case 1://objeto a la derecha
        Motors.Speeds(-0,255);// Giro derecha
        mem=0;//recuerda que vio el robot a la derecha
      break;
      
      case 2://objeto diagonal derecha
        Motors.Speeds(150,255);//Ataca Diagonal Derecha
      break;
      case 4://objeto diagonal izquierda
        Motors.Speeds(255,150);//Ataca Diagonal Izquierda
      break;
      
      case 6://objeto en el centro
        Motors.Speeds(255,255);//Ataca Frente
      break;
      
      case 8://objeto a la izquierda
        Motors.Speeds(255,-0);//Giro Izquierda
        mem=1;//recuerda que vio el robot a la izquierda
      break;
     
      default://TODAS LAS CONDICIONES QUE NO SE TUVIERON EN CUENTA
        if(mem==0)//recuerda que vio el objeto a la dercha
        Motors.Speeds(-255,255); // Giro en el eje Derecha Memoria
        if(mem==1)//recuerda que vio el objeto a la izquierda
        Motors.Speeds(255,-255); // Giro en el eje Izquierda Memoria
        if(mem==2)//recuerda que vio el doyo
        Motors.Speeds(0,0); // apagar el robot porque vio el borde del doyo
      break;
    }
  }
  //en esta condicion va hacia atras
  if(digitalRead(16)==1 && digitalRead(7)==0){
    Motors.Speeds(-100,-180); // GUri Izquierda Memoria 
    delay(300); //va hacia atras y espera medio segundo
    mem=2;//memoria que salio del doyo
  }
  //en esta condicion va hacia atras
  if(digitalRead(16)==0 && digitalRead(7)==1){
    Motors.Speeds(-180,-100); // GUri Izquierda Memoria
    delay(300);//va hacia atras y espera medio segundo
    mem=2;//memoria que salio del doyo
  }
}
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



