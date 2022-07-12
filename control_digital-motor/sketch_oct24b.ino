#include <TimerOne.h>
 #include <Wire.h>
 #include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int IN1 = 3; 
LiquidCrystal_I2C lcd(0x27, 16, 2);
int SetP;

// Variable para enviar salida al PWM (Salida de control)
int pwmval;double temp;


/*****************
 Parámetros controlador digital (RST cib R=T)
 */

double a0=3.6231;
double n4=16.7075;

// Estados sin desplazar y desplazados (Bloque de control de lazo de realimentación)
double x1,x1s;

// Salida de controlador uk, entrada de controlador ek (Bloque de control de lazo de realimentación)
double uk;
double ek;

// Estados sin desplazar y desplazados (Bloque de control de SetPoint)

double x1t,x1st;

// Salida de controlador uk, entrada de controlador ek (Bloque de control de SetPoint)
double ukt;
double ekt;

void setup() {
  // put your setup code here, to run once:
lcd.init();
  lcd.backlight();
 mlx.begin();  
  pinMode(3, OUTPUT);
  SetP=35;
  pwmval=SetP;
   
  
  // Condiciones iniciales de los estados iguales a cero

   x1=0;
 

   x1t=0;
   Serial.begin(9600);      
}

void loop() {
  //     // Medida de la variable controlada (velocidad)
    temp=mlx.readAmbientTempC();
    

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
    uk=n4*ek+a0*x1t;
   // Actualización de estados
    x1t=x1st;

    // La señal de control que va a la planta es la resta entre 
    // la señal de control de setPoint y la señal de control 
    // del lazo de realimentación


    // Lazo cerrado
   
    pwmval=(ukt-uk);

    // Función de saturación
     if(pwmval<0)
     pwmval=0;
     if(pwmval>255)
     pwmval=255;

    // Lazo cerrado
     analogWrite(IN1,pwmval);
     Serial.print(pwmval);
     Serial.println(temp);
delay(500);

}
