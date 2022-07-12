
#include <TimerOne.h>
 #include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int IN1 = 3; 
LiquidCrystal_I2C lcd(0x27, 16, 2);

 float SetP=37.7;

// Variable para enviar salida al PWM (Salida de control)
int pwmval;




unsigned long counter;

float x=0.14;
double temp;


/*****************
 Parámetros controlador digital (RST cib R=T)
 */
 
 //double a0=1069.8;//255
   //double n4=4931.9;//255
  //double a0=818.2;//195
   //double n4=3771.8;//195

double a0=537.1;//128
double n4=2476;//128

//double a0=125.8440;//3
//double n4=580.1416;//3
//double a0=70.7481;//x
//double n4=349.061;//x
// Estados sin desplazar y desplazados (Bloque de control de lazo de realimentación)
double x1=0;
double x1s=0;

// Salida de controlador uk, entrada de controlador ek (Bloque de control de lazo de realimentación)
double uk=0;
double ek=0;

// Estados sin desplazar y desplazados (Bloque de control de SetPoint)

double x1t,x1st;

// Salida de controlador uk, entrada de controlador ek (Bloque de control de SetPoint)
double ukt;
double ekt;


int incomingByte = 0;   // for incoming serial data


void setup()
{
  Serial.begin(9600);       
  lcd.init();
  lcd.backlight();
  Serial.println("Adafruit MLX90614 test"); 
  mlx.begin(); 
  analogWrite(IN1,0);
   

    

  // Configuración de la interrupción de timer a 30ms tiempo de muestreo
   //Timer1.initialize(500000);  
  // Timer1.attachInterrupt(ISR_RT); 

  
   SetP=SetP+x;
   pwmval=SetP;
   lcd.setCursor(10,0);
   lcd.print (SetP);
   temp=0;
   x1=0;
   x1t=0;
   


}

void loop()
{
 ISR_RT()    ;
 delay(500);
}



// Interrupción de timer 
 void ISR_RT()
   {  

temp=mlx.readAmbientTempC();
    
//Serial.print(temp);

    
  

    /*********************************************************/
    /*****Bloque de control del lazo de realimentación (R/S)***/
    
    // Entrada al bloque de control = señal medida
    ek=temp;

    // Ecuaciones de estado bloque de lazo de realimentación
  

x1s=x1+ek;

uk=n4*ek+a0*x1;

x1=x1s;

    /*********************************************************/
    /*****Bloque de control de setPoint (T/S=R/S)***/

    // Entrada al bloque de control = setPoint
    ekt=SetP;

   // Ecuaciones de estado bloque de control de setPoint
  x1st=x1t+ek;

    // Salida de control del bloque de setPoint
    ukt=n4*ekt+a0*x1t;
   // Actualización de estados
    x1t=x1st;

    // La señal de control que va a la planta es la resta entre 
    // la señal de control de setPoint y la señal de control 
    // del lazo de realimentación


    // Lazo cerrado
   
    pwmval=(int)(ukt-uk);

//     Función de saturación
     if(pwmval<0)
     pwmval=0;
     if(pwmval>255)
     pwmval=255;

     pwmval=255-pwmval;

    // Lazo cerrado
     analogWrite(IN1,pwmval);
     Serial.print(temp);
     Serial.print("--------");
     Serial.println(pwmval);
 lcd.setCursor(0,0);
 lcd.print(temp);
  lcd.setCursor(0,1);    
   lcd.print(pwmval); 
        lcd.setCursor(0,5); 
        
     
 
   

 }
