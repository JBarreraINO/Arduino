
#include <TimerOne.h>
 #include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int IN1 = 3; 
int IN2 = 5; 
const byte A=3;

// Definición de set point (debe estar en las mismas unidades de la variable controlada)
int SetP;

// Variable para enviar salida al PWM (Salida de control)
int pwmval;

byte buf[2]={0,0};


unsigned long counter;
double velocidad;


/*****************
 Parámetros controlador digital (RST cib R=T)
 */
double b1=-0.7283;
double b2=-0.2717;

double c2=2.3672;
double c1=-1.8222;
double a0=3.7582;

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


int incomingByte = 0;   // for incoming serial data


void setup()
{


   
   analogWrite(IN1,pwmval);
   analogWrite(IN2,0); 

   Serial.begin(230400);        

  pinMode(A, INPUT);
  // Interrupción de timer 
  attachInterrupt(digitalPinToInterrupt(A), ISR_RA, RISING);

  // Configuración de la interrupción de timer a 30ms tiempo de muestreo
   Timer1.initialize(30000);  
   Timer1.attachInterrupt(ISR_RT); 

   SetP=255;
   pwmval=SetP;
   
   velocidad=0;
   counter=0;

  // Condiciones iniciales de los estados iguales a cero

   x1=0;
   x2=0;

   x1t=0;
   x2t=0;


}

void loop()
{

        
}

void serialEvent( ) {
  
  if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
                
                //if(incomingByte>=0)
                SetP=incomingByte;
                pwmval=SetP;
                analogWrite(IN1,pwmval);

                x1=0;
                x2=0;
                x1t=0;
                x2t=0;
        }
}

// Interrupción de timer 
 void ISR_RT()
   {  

    // Medida de la variable controlada (velocidad)
    velocidad=mlx.readAmbientTempC();
    counter=0;

    /*********************************************************/
    /*****Bloque de control del lazo de realimentación (R/S)***/
    
    // Entrada al bloque de control = señal medida
    ek=velocidad;

    // Ecuaciones de estado bloque de lazo de realimentación
    x1s=x2;
    x2s=-b2*x1-b1*x2+ek;
    // Salida de control de lazo de realimentación
    uk=a0*ek+c1*x2+c2*x1;
    // Actualización de estados
    x2=x2s;
    x1=x1s;

    /*********************************************************/
    /*****Bloque de control de setPoint (T/S=R/S)***/

    // Entrada al bloque de control = setPoint
    ekt=SetP;

   // Ecuaciones de estado bloque de control de setPoint
    x1st=x2t;
    x2st=-b2*x1t-b1*x2t+ekt;

    // Salida de control del bloque de setPoint
    ukt=a0*ekt+c1*x2t+c2*x1t;
    
   // Actualización de estados
    x2t=x2st;
    x1t=x1st;

    // La señal de control que va a la planta es la resta entre 
    // la señal de control de setPoint y la señal de control 
    // del lazo de realimentación


    // Lazo cerrado
   
    pwmval=ukt-uk;

    // Función de saturación
     if(pwmval<10)
     pwmval=10;
     if(pwmval>255)
     pwmval=255;

    // Lazo cerrado
     analogWrite(IN1,pwmval);

 
           
     buf[0]=velocidad;
     buf[1]=velocidad;

         
     Serial.write(buf, 2);
  

 }

// Interrupción de timer
 void ISR_RA()
   {  
    counter++;
  }
