
#include <TimerOne.h>
int IN1 = 3;

// Estados sin desplazar y desplazados (Bloque de control de lazo de realimentación)
double x1,x2,x1s,x2s;

// Salida de controlador uk, entrada de controlador ek (Bloque de control de lazo de realimentación)
double uk;
double ek;

// Estados sin desplazar y desplazados (Bloque de control de SetPoint)

double x1t,x2t,x1st,x2st;

// Salida de controlador uk, entrada de controlador ek (Bloque de control de SetPoint)
double ukt;
double ekt;
int pwmval=0;


void setup() {
  x1=0;
   x2=0;

   x1t=0;
   x2t=0;
    attachInterrupt(digitalPinToInterrupt(3), RST, RISING);

  // Configuración de la interrupción de timer a 30ms tiempo de muestreo
   Timer1.initialize(30000);  
   Timer1.attachInterrupt(RST); 
  // put your setup code here, to run once:
pinMode(3,OUTPUT);
}

void loop() {
 

}
void RST()
{
  int velocidad;
ek=velocidad;
x1s=x2; 
x2s=0.2801*x1+0.7199*x2+ek;

uk=2.458406752879653e+03*ek-3.1309e+03*x2+3.1309e+03*x1;

x2=x2s;
x1=x1s;



x1st=x2t; 
x2st=0.2801*x1t+0.7199*x2t+ekt;

ukt=2.458406752879653e+03*ekt-3.1309e+03*x2t+3.1309e+03*x1t;

x2t=x2st;
x1t=x1st;


    pwmval=ukt-uk;

    // Función de saturación
     if(pwmval<10)
     pwmval=10;
     if(pwmval>255)
     pwmval=255;

    // Lazo cerrado
     analogWrite(IN1,pwmval);

  
  
  }
