#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int periodo = 200;
unsigned long TiempoAhora = 0;
LiquidCrystal_I2C lcd(0x3f, 16, 2);
  float dif;

int pinLM35 = A0; // Variable del pin de entrada del sensor (A0)
//I/O
int IN1 = 11;//PINOUT CONTROL HOTER

double a0 =0.0946 ; //128
double n4 =  0.2391 ; //128
double x1 = 0; //estados
double x1s = 0; //estados


// Variable para enviar salida al PWM (Salida de control)
int pwmval; float x = 0; float temp;  // Variable para almacenar el valor obtenido del sensor (0 a 1023)
// Salida de controlador uk, entrada de controlador ek (Bloque de control de lazo de realimentación)
double uk = 0;
double ek = 0;

// Estados sin desplazar y desplazados (Bloque de control de SetPoint)

double x1t, x1st;
double x1t1, x1st1;
// Salida de controlador uk, entrada de controlador ek (Bloque de control de SetPoint)
double ukt=0;
double ekt=0;




//Variables
float set_temperature=25;



float elapsedTime, Time, timePrev;

//Vraiables for rotary encoder state detection



void setup() {


  Serial.begin(9600);
    
  set_temperature = set_temperature + x;
  pwmval = set_temperature;
  temp = 0;
  x1 = 0;
  x1t = 0;

  Wire.begin();

  pinMode(IN1, OUTPUT);
// TCCR2A =   B00000011;  // Fast PWM MODE - OCA DISCONETED
  
  TCCR2B |=B00000001;//NO PRESCALING
//TCCR2B |=B00000010;//clkI/O/8
//TCCR2B |=B00000011;//clkI/O/32
//TCCR2B |=B00000100;//clkI/O/64
//TCCR2B |=B00000101;//clkI/O/128
//TCCR2B |=B00000110;//clkI/O/256
//TCCR2B |=B00000111;//clkI/O/1024
  //TIMSK2 = (TIMSK2 & B11111000) | 0x07;
  
 // TCCR2B = TCCR2B & B11111000 | 0x03;  // pin 3 and 11 PWM frequency of 928.5 Hz
  Time = millis();
  pinMode(11, OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {

  int ADC_SHARP=ADC0_promedio(5);// hacer una adecuacion d la señal

  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  temp = ADC_SHARP; 
   
  // Calculamos la temperatura con la fórmula

  temp=(4.7 * temp * 100.0)/1024.0; //
  Serial.println(temp);
  temp=temp;
   

if(millis() > TiempoAhora + periodo){
   ISR_RT();
  
        TiempoAhora = millis();
       
    }
  
    lcd.setCursor(0, 0);
    lcd.print("RAPPI SERVICE");//MENSAJE
    lcd.setCursor(0, 1);
    lcd.print("Sp:");
    lcd.setCursor(3, 1);
    lcd.print(set_temperature , 1);
    lcd.setCursor(8, 1);
    lcd.print("TMP:");
    lcd.setCursor(12, 1);
    lcd.print(temp, 1);


  }





void ISR_RT()
{
  /*********************************************************/
  /*****Bloque de control del lazo de realimentación (R/S)***/
 
  // Entrada al bloque de control = señal medida
  ek = temp;

  // Ecuaciones de estado bloque de lazo de realimentación



  x1s = x1 + ek;  //     x[Kh+h]=e[kh]+x1;

  uk = n4 * ek + a0 * x1; //μ[Kh] =2.2611 *ek+0.0040*x1;

  x1 = x1s;

  /*********************************************************/
  /*****Bloque de control de setPoint (T/S=R/S)***/

  // Entrada al bloque de control = setPoint
  ekt = set_temperature;

  // Ecuaciones de estado bloque de control de setPoint
  x1st = x1t + ek;//      x[Kh+h]=e[kh]+x1;

  // Salida de control del bloque de setPoint
  ukt = n4 * ekt + a0 * x1t;//μ[Kh] =2.2611 *ek+0.0040*x1;
  // Actualización de estados
  x1t = x1st;

  // La señal de control que va a la planta es la resta entre
  // la señal de control de setPoint y la señal de control
  // del lazo de realimentación


  // Lazo cerrado

  pwmval = (int)(ukt - uk);

  //     Función de saturación
  if (pwmval < 0)
    pwmval = 0;
  if (pwmval > 255)
    pwmval = 255;


  pwmval = 250-pwmval;
    sum();
  analogWrite(IN1, pwmval);
  // Lazo cerrado


//refrigeracion para sobreimpulso


}





int ADC0_promedio(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  return(suma/n);
}


void sum(){

 dif=ekt-ek;
if (dif<0){
  
   pwmval=255;
   
  }

  
  /*
if(dif>0.5)
{
   pwmval=ekt-ek;
}*/
}
 
