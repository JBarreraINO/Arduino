/* Programa para Calibração do HX711
  Blog Eletrogate - http://blog.eletrogate.com/balanca-digital-com-arduino-aprenda-a-usar-a-celula-de-carga
  Arduino UNO - IDE 1.8.5 - Modulo HX711 - celulas de Carga 50 Kg
  Gustavo Murta   31/maio/2018
  Biblioteca https://github.com/bogde/HX711
  Baseado em https://www.hackster.io/MOHAN_CHANDALURU/hx711-load-cell-amplifier-interface-with-arduino-fa47f3
*/
 
#include "HX711.h"                    // Biblioteca HX711 
 int incomingByte = 0;
#define DOUT  A0                      // HX711 DATA OUT = pino A0 do Arduino 
#define CLK  A1                       // HX711 SCK IN = pino A1 do Arduino 
 
HX711 balanca(DOUT, CLK);             // instancia Balança HX711
 
float calibration_factor = 4213;

;     // fator de calibração para teste inicial
 
void setup()
{
  Serial.begin(9600);                                              // monitor serial 9600 Bps
  
  balanca.set_scale();                                             // configura a escala da Balança
  zeraBalanca ();                                                  // zera a Balança
}
 
void zeraBalanca ()
{
  Serial.println();                                               // salta uma linha
  balanca.tare();                                                 // zera a Balança
  Serial.println("Balanza ajustada ");
}
 
void loop()
{
  balanca.set_scale(calibration_factor);    
 int peso=balanca.get_units();
  //Serial.print("Peso: ");                                    // imprime no monitor serial
  Serial.print(balanca.get_units(), 3);                      // imprime peso da balança com 3 casas decimais
  Serial.print(" kg");
  Serial.print("      Fator de Calibracion: ");               // imprime no monitor serial
  Serial.println(calibration_factor);                        // imprime fator de calibração
  delay(500) ;                                               // atraso de 0,5 segundo
 
  if (Serial.available())                                    // reconhece letra para ajuste do fator de calibração
  {
    
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')                // a = aumenta 10
      calibration_factor += 10;
    else if (temp == '-' || temp == 'z')           // z = diminui 10
      calibration_factor -= 10;
    else if (temp == 's')                          // s = aumenta 100
      calibration_factor += 100;
    else if (temp == 'x')                          // x = diminui 100
      calibration_factor -= 100;
    else if (temp == 'd')                          // d = aumenta 1000
      calibration_factor += 1000;
    else if (temp == 'c')                          // c = diminui 1000
      calibration_factor -= 1000;
    else if (temp == 'f')                          // f = aumenta 10000
      calibration_factor += 10000;
    else if (temp == 'v')                          // v = dimuni 10000
      calibration_factor -= 10000;
    else if (temp == 't') zeraBalanca ();          // t = zera a Balança
   String mensaje = "";
  
   switch (temp){

case 'o' :
  if(peso>=25 && peso<=27){                    
                mensaje =  " Su perro esta saludable";                
           Serial.print(mensaje);
             delay(3000);
            }
                if(peso<25){                    
                
                   mensaje = " Su perro esta bajo de peso ";                    
                  Serial.print(mensaje);
                  delay(5000);
                }                
                if(peso>35){                    
                   
                    mensaje = " Su perro esta en sobrepeso ";                    
                 Serial.print(mensaje);
                   delay(3000);
                }     



    break;
      
 case 'p' :
if(peso>=25 && peso<=34){                    
                    mensaje = " Felicitaciones usted tiene un perro sanludable ";                    
                      Serial.print(mensaje);
             delay(3000);
                }                
                if(peso<25){                    
                    mensaje = " Atención su perro esta bajo de peso ";                    
                 Serial.print(mensaje);
             delay(3000);
                }                
                if(peso>34){                    
                    mensaje = " Alerta su perro tiene sobrepeso";                    
                Serial.print(mensaje);
             delay(3000);
                }    

  break;
  case 'q' :
     if(peso>=26&& peso<=36){                    
                    mensaje = " Su perro esta saludable  ";                }                
                 Serial.print(mensaje);
             delay(3000);
                if(peso<26){                    
                    mensaje = " Su perro esta bajo de peso ";                    
                 Serial.print(mensaje);
             delay(3000);
                }                
                if(peso>36){                    
                
                    mensaje = " Alerta \n El perro esta con sobre peso  ";                    
                 Serial.print(mensaje);
             delay(3000);
                }    


  break;
  case 'l' :
   if(peso>=24 && peso<=28){                    
                    mensaje = " Su perro esta muy bien de peso ";
                Serial.print(mensaje);
             delay(3000);
                }               
                if(peso<24){                    
                    mensaje = " Su perro esta bajo de peso  ";                    
                Serial.print(mensaje);
             delay(3000);
                }                
                if(peso>28){                    
                    mensaje = " Alerta\n El perro esta con sobre peso  ";                   
               Serial.print(mensaje);
             delay(3000);
                }    
                break;


case 'm':
     if(peso>=24&&peso<=28){                    
                    mensaje = " Su perro esta muy bien de peso  ";
                 Serial.print(mensaje);
             delay(3000);
                }               
                if(peso<24){                    
                    mensaje = " Su perro esta bajo de peso ";                    
                Serial.print(mensaje);
             delay(3000);
                }                
                if(peso>28){                    
                    mensaje = " Alerta\n El perro esta con sobre peso  ";                   
                Serial.print(mensaje);
             delay(3000);
                }   
  break;
 case 'n':

  if(peso>=3.75 && peso<=4.5){                
                mensaje = " Su perro esta muy bien de peso  ";                    
                Serial.print(mensaje);
             delay(3000);
            }                
                if(peso<3.75){                    
                     mensaje = " Su perro esta bajo de peso  ";                    
                   Serial.print(mensaje);
             delay(3000);
                }                
                if(peso>4.5){                    
                    mensaje = " Alerta\n El perro esta con sobre peso  ";                    
                  Serial.print(mensaje);
             delay(3000);
                }  
  
  break;
  case 'j':
    if(peso>=5&&peso<=13){                    
                   mensaje = " Su perro esta muy bien de peso  ";
                 Serial.print(mensaje);
             delay(3000);
                }                
                if(peso<5){                    
                    mensaje = " Su perro esta bajo de peso  ";                    
                 Serial.print(mensaje);
             delay(3000);
                }
                
                if(peso>13){
                    
                  mensaje = " Alerta\n El perro esta con sobre peso  ";  
                  Serial.print(mensaje);
             delay(3000);  
                }
                
break;

case 'k':
     if(peso>=5&&peso<=13){                    
                   mensaje = " Su perro esta muy bien de peso ";
                 Serial.print(mensaje);
             delay(3000);
                }                
                if(peso<5){                    
                    mensaje = " Su perro esta bajo de peso  ";                    
                 Serial.print(mensaje);
             delay(3000);
                }
                
                if(peso>13){
                    
                  mensaje = " Alerta \n El perro esta con sobre peso ";  
                  Serial.print(mensaje);
             delay(3000);  
                }
              
  break;

case 'h':
    if(peso>=27.5 && peso<=34){                    
                   mensaje = " Su perro esta muy bien de peso  ";
                       Serial.print(mensaje);
             delay(3000);                 }                
                if(peso<27.5){                    
                    mensaje = " Su perro esta bajo de peso  ";
                      Serial.print(mensaje);
             delay(3000);                 }                
                if(peso>34){                    
                    mensaje = " Alerta \n El perro esta con sobre peso  ";                      
                Serial.print(mensaje);
             delay(3000); 
                }                     
               
           
  break;



    
}
}
}

