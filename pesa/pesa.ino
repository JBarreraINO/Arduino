#include "HX711.h"

#define DOUT  A1
#define CLK  A0
int motor;
HX711 balanza(DOUT, CLK);

void setup() {
Serial.begin(9600);
pinMode(motor,OUTPUT);
 
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(1075.27777778); // Establecemos la escala
  balanza.tare(4);  //El peso actual es considerado Tara.
  
  Serial.println("Listo para pesar");  
}

void loop() {
  int peso=balanza.get_units(20);
  if(peso<0){peso=0;}
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");




  if (Serial.available())                                    // reconhece letra para ajuste do fator de calibração
  {
    
   char temp = Serial.read();

  
   switch (temp){

case 'a' :
while(peso<50){
  
digitalWrite(3,HIGH);
delay(1000);
 Serial.print(peso);
 peso=balanza.get_units(20);
  if(peso<0){peso=0;}
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");
 
}
digitalWrite(3,LOW);
delay(1000);
 break;

  


   
      
 case 's' :
while(peso<100){
  
digitalWrite(3,HIGH);
delay(1000);
 Serial.print(peso);
 peso=balanza.get_units(20);
  if(peso<0){peso=0;}
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");
 
}
digitalWrite(3,LOW);
delay(1000);

  break;
  case 'd' :
   while(peso<200){
  
digitalWrite(3,HIGH);
delay(1000);
 Serial.print(peso);
 peso=balanza.get_units(20);
  if(peso<0){peso=0;}
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");
 
}
digitalWrite(3,LOW);
delay(1000);
  break;
  case 'f' :
while(peso<300){
  
digitalWrite(3,HIGH);
delay(1000);
 Serial.print(peso);
 peso=balanza.get_units(20);
  if(peso<0){peso=0;}
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");
 
}
digitalWrite(3,LOW);
delay(1000);
   break;


case 'z':
    while(peso<400){
  
digitalWrite(3,HIGH);
delay(1000);
 Serial.print(peso);
 peso=balanza.get_units(20);
  if(peso<0){peso=0;}
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");
 
}
digitalWrite(3,LOW);
delay(1000);
  break;
 case 'x':
while(peso<500){
  
digitalWrite(3,HIGH);
delay(1000);
 Serial.print(peso);
 peso=balanza.get_units(20);
  if(peso<0){peso=0;}
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");
 
}
digitalWrite(3,LOW);
delay(1000);
  
  break;
  case 'c':
    
       while(peso<600){
  
digitalWrite(3,HIGH);
delay(1000);
 Serial.print(peso);
 peso=balanza.get_units(20);
  if(peso<0){peso=0;}
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");
 
}
digitalWrite(3,LOW);
delay(1000);         
break;

case 'v':
     
      while(peso<700){
  
digitalWrite(3,HIGH);
delay(1000);
 Serial.print(peso);
 peso=balanza.get_units(20);
  if(peso<0){peso=0;}
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");
 
}
digitalWrite(3,LOW);
delay(1000);        
  break;

case 't':
  
digitalWrite(3,HIGH);
delay(1000);
digitalWrite(3,LOW);
delay(10);
 


               
           
  break;



    
}
}




































  
}
