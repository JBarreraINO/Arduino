//programa para dispensador de comida para perros
//pensado para programacion orientada a objetos
//para conexion con interfaz java
// 12/9/18.

#include "HX711.h"
int incomingByte = 0;  // para el dato serial de entrada
//galga 1
HX711 scale(2, 3);
HX711 scale2(11, 12);

//varibles motor de compuerta//
int derA = 7; 
int derB = 6; 
int sen=8;
int vel = 155;
int rep=0;// Velocidad de los motor (0-255)

float calibration_factor = 48100; // este factor es de acuerdo a la galga

float calibration_factor2 = 49000; // este factor es de acuerdo a la galga
float units;
float ounces;
//defino una segunda galga 
float units1;
float ounces1;
void setup() {
  
  Serial.begin(9600); // el puerto se tiene que poner  9600 bps igual que java
 pinMode(13,OUTPUT);
  pinMode(8,INPUT);
 scale2.set_scale();
  scale.set_scale();
  scale.tare();  //reinicia a cero
  scale2.tare();
  
  long zero_factor = scale.read_average();
}

void loop() {
int detect = digitalRead(8);
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // lee los datos de entrada
    incomingByte = Serial.read();

    // dice lo que recibe (se puede quitar)
    //Serial.print("I received: ");
   //DD Serial.println(incomingByte, DEC);

 //funcion para calibrar galga con botones 
 char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 20;




//funcion para seleccionar cantidad de comida
    
    switch (incomingByte){

case '1' :
if(detect==LOW){
analogWrite(derB, vel);  // 
delay(2000);
analogWrite(derA, vel);
delay(1000);
analogWrite(derB, rep);  // 
delay(1000);
analogWrite(derA, rep);
delay(1000);
}
Serial.print("caso 1");
    break;
    
 case '2' :

 analogWrite(derB, vel);  // 
delay(3000);
analogWrite(derA, vel);
delay(3000);
analogWrite(derB, rep);  // 
delay(1000);
analogWrite(derA, rep);
delay(1000);
Serial.print("caso 2") ;

  break;

 case '3' :
Serial.print("caso 3") ;
analogWrite(derB, vel);  // 
delay(3000);
analogWrite(derA, vel);
delay(3000);
analogWrite(derB, rep);  // 
delay(1000);
analogWrite(derA, rep);
delay(1000);

  break;
   case '4' :
Serial.print("caso 4 ") ;

analogWrite(derB, vel);  // 
delay(4000);
analogWrite(derA, vel);
delay(4000);
analogWrite(derB, rep);  // 
delay(1000);
analogWrite(derA, rep);
delay(1000);
  break;
   case '5' :

analogWrite(derB, vel);  // 
delay(100);
analogWrite(derA, vel);
delay(100);
analogWrite(derB, rep);  // 
delay(100);
analogWrite(derA, rep);
delay(100);
  break;
   case '6' :

analogWrite(derB, vel);  // 
delay(200);
analogWrite(derA, vel);
delay(200);
analogWrite(derB, rep);  // 
delay(200);
analogWrite(derA, rep);
delay(200);
  break;
   case '7' :


analogWrite(derB, vel);  // 
delay(300);
analogWrite(derA, vel);
delay(300);
analogWrite(derB, rep);  // 
delay(300);
analogWrite(derA, rep);
delay(300);
  break;
   case '8' :

analogWrite(derB, vel);  // 
delay(2300);
analogWrite(derA, vel);
delay(1000);
analogWrite(derB, rep);  // 
delay(1000);
analogWrite(derA, rep);
delay(1000);


  break;

 case '9' :
Serial.print("caso 9") ;
analogWrite(derA, vel);  // 
delay(500);
analogWrite(derB, vel);  //

  break; 
  
  
  }

}
delay(10);
galga();
galga2();
}





  void galga(){
    
   scale.set_scale(calibration_factor); //Adjust to this calibration factor

 // Serial.print("Reading: ");
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print("");
  Serial.print(units);
 Serial.print(" kg");
   Serial.print("");
     Serial.print("-------^^^^^^^-------"); 
 // Serial.print(" calibration_factor: ");
 // Serial.print(calibration_factor);
//  Serial.print();
  delay(100); 
    
    
    
    
    }

void galga2()
{
   scale2.set_scale(calibration_factor2); //Adjust to this calibration factor

 // Serial.print("Reading: ");
  units1 = scale2.get_units(), 10;
  if (units1 < 0)
  {
    units1 = 0.00;
  }
  ounces1 = units1 * 0.035274;
 Serial.print(units1);
 Serial.print(" kg"); 
 // Serial.print(" calibration_factor: ");
 // Serial.print(calibration_factor);
  Serial.println();
  delay(100); 
  
  
  }

    
