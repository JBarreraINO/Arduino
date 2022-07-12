
#include "RTClib.h"
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <SHT21.h>  // include SHT21 library
int periodo = 500;
unsigned long TiempoAhora = 0;
SHT21 sht;
LiquidCrystal_I2C lcd(0x27, 16, 2);
float humidity;
RTC_DS1307 RTC;

//I/O
int IN1 = 3;//PINOUT CONTROL HOTER
int PWM_pin = 5;  //Pin for PWM signal to the MOSFET driver (the BJT npn with pullup)
int clk = 8;      //Pin 1 from rotary encoder
int data = 9;     //Pin 2 from rotary encoder
double a0 = 537.1; //128
double n4 = 2476; //128

double a01 = 292; //resistencia nueva
double n41 = 1601.3; //resistencia nueva

double x1 = 0; //estados
double x1s = 0; //estados
double x11 = 0; //estados
double x1s1 = 0; //estados


// Variable para enviar salida al PWM (Salida de control)
int pwmval;int pwmval1; float x = 0.05; double temp;double humedad;
// Salida de controlador uk, entrada de controlador ek (Bloque de control de lazo de realimentación)
double uk = 0;
double ek = 0;
double uk1 = 0;
double ek1 = 0;
// Estados sin desplazar y desplazados (Bloque de control de SetPoint)

double x1t, x1st;
double x1t1, x1st1;
// Salida de controlador uk, entrada de controlador ek (Bloque de control de SetPoint)
double ukt;
double ekt;

double ukt1;
double ekt1;




//Variables
float set_temperature = 37.7;
float set_humedad = 60;        //Default temperature setpoint. Leave it 0 and control it with rotary encoder

float humedad_read = 0.0;
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
float PID_value = 0;
int button_pressed = 0;
int menu_activated = 0;
float last_set_temperature = 0;
float last_set_humedad = 0;
//Vraiables for rotary encoder state detection
int clk_State;
int Last_State;
bool dt_State;

//PID constants
//////////////////////////////////////////////////////////
//int kp = 1000;   int ki = 1000.0;   int kd = 1000;
int kp = 80;   int ki = 78.8;   int kd = 95;
//////////////////////////////////////////////////////////

int PID_p = 0;    int PID_i = 0;    int PID_d = 0;
float last_kp = 0;
float last_ki = 0;
float last_kd = 0;
int PID_values_fixed = 0;
//////////////////////////////
//////////////////////////////// volteo de huevos/////////////////////////
//   h1=Hora, m1=Minutos, s1=Segundos
// Cuando no se programa ninguna hora se debe dejar escrito el numero 99
// se pueden programar 16 volteos por cada horario,indica que es el horario 1
int segundo;
int minuto;
int hora;

int h1_c1 = 8;   int m1_c1 = 11;   int s1_c1 = 0;
int h2_c1 = 12;   int m2_c1 = 0;  int s2_c1 = 0;
int h3_c1 = 16;   int m3_c1 = 37;  int s3_c1 = 20;
int h4_c1 = 20;   int m4_c1 = 0;  int s4_c1 = 0;
int h5_c1 = 1;   int m5_c1 = 0;  int s5_c1 = 0;
int h6_c1 = 4 ;  int m6_c1 = 35;  int s6_c1 = 0;
int h7_c1 = 99;  int m7_c1 = 0;  int s7_c1 = 0;
int h8_c1 = 99;  int m8_c1 = 0;  int s8_c1 = 0;
int h9_c1 = 99;  int m9_c1 = 0;  int s9_c1 = 0;
int h10_c1 = 99; int m10_c1 = 0;  int s10_c1 = 0;
int h11_c1 = 99; int m11_c1 = 0;  int s11_c1 = 0;
int h12_c1 = 99; int m12_c1 = 0;  int s12_c1 = 0;
int h13_c1 = 99; int m13_c1 = 0;  int s13_c1 = 0;
int h14_c1 = 99; int m14_c1 = 0;  int s14_c1 = 0;
int h15_c1 = 99; int m15_c1 = 0;  int s15_c1 = 0;
int h16_c1 = 99; int m16_c1 = 0;  int s16_c1 = 0;

void setup() {


  Serial.begin(9600);
  set_temperature = set_temperature + x;
  pwmval = set_temperature;
  
  pwmval1 = set_humedad;
  temp = 0;
  humedad=0;
  x1 = 0;
  x1t = 0;
  x11 = 0;
  x1t1 = 0;


  Wire.begin();

  RTC.begin();
  pinMode(IN1, OUTPUT);
  pinMode(PWM_pin, OUTPUT);
  TCCR2B = TCCR2B & B11111000 | 0x03;  // pin 3 and 11 PWM frequency of 928.5 Hz
  Time = millis();
  pinMode(14, OUTPUT);
   pinMode(15, OUTPUT);
    pinMode(16, OUTPUT); pinMode(17, OUTPUT);
  // RTC.adjust(DateTime(__DATE__, __TIME__));
  Last_State = (PINB & B00000001);      //Detect first state of the encoder

  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan
  PCMSK0 |= (1 << PCINT0);  //Set pin D8 trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT1);  //Set pin D9 trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT3);  //Set pin D11 trigger an interrupt on state change.

  pinMode(11, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {



  if (menu_activated == 0)
  {

if(millis() > TiempoAhora + periodo){
   ISR_RT();
   ISR_RT2();

        TiempoAhora = millis();
       
    }
    // se lee la temperatura del sensor
   
    
    humidity = sht.getHumidity();
    humedad_read = humidity;

    delay(1000); // Frecuencia de actualización + retraso de la impresión LCD
    lcd.clear();
    ////////// FUNCION DE REJOJ//////
    DateTime now = RTC.now();
    lcd.setCursor(0, 0);
    lcd.print("H:");
    //   lcd.print(SHT2x.GetHumidity());

    lcd.print(humidity);
    lcd.setCursor(8, 0);lcd.print(now.hour(), DEC);lcd.print(":"); lcd.print(now.minute(), DEC);lcd.print(":"); lcd.print(now.second(), DEC);segundo = now.second();minuto = now.minute();hora = now.hour();horario_1();

    /////////
    lcd.setCursor(0, 1);
    lcd.print("S:");
    lcd.setCursor(2, 1);
    lcd.print(set_temperature - x, 1);
    lcd.setCursor(9, 1);
    lcd.print("R:");
    lcd.setCursor(11, 1);
    lcd.print(mlx.readAmbientTempC(), 1);


  }// Fin del menú 0 (control PID)






  // Primera página del menú (temp setpoint)
  if (menu_activated == 1)
  {

    analogWrite(PWM_pin, 255);
    if (set_temperature != last_set_temperature)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set  temperatura");
      lcd.setCursor(0, 1);
      lcd.print(set_temperature - x);
    }
    last_set_temperature = set_temperature;
  }




  if (menu_activated == 2)
  {
    analogWrite(PWM_pin, 255);
    if (set_humedad != last_set_humedad)
    {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set  humedad");
      lcd.setCursor(0, 1);
      lcd.print(set_humedad);
    }
    last_set_humedad = set_humedad;

  }//fin del menu 1








  //Segundo menu  (P set)
  if (menu_activated == 3)
  {

    if (kp != last_kp)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("valor P    ");
      lcd.setCursor(0, 1);
      lcd.print(kp);
    }
    last_kp = kp;


  }//fin del menu 2




  //terce menu (I set)
  if (menu_activated == 4)
  {

    if (ki != last_ki)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("valor I ");
      lcd.setCursor(0, 1);
      lcd.print(ki);
    }
    last_ki = ki;


  }//fin del menu 3




  //Cuarta página del menú (D set)
  if (menu_activated == 5)
  {

    if (kd != last_kd)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("valor  D    ");
      lcd.setCursor(0, 1);
      lcd.print(kd);
    }
    last_kd = kd;
  }//fin del menu 4






}//fin
// El vector de interrupción para pulsador y codificador rotatorio.





ISR(PCINT0_vect) {

  ////////////////////////////////////
  if (menu_activated == 1)
  {
    clk_State =   (PINB & B00000001); // pin 8 estado? ¿Es alto?
    dt_State  =   (PINB & B00000010);
    if (clk_State != Last_State) {
      // Si el estado de los datos es diferente al estado del reloj, eso significa que el codificador está girando hacia la derecha
      if (dt_State != clk_State) {
        set_temperature = set_temperature + 0.1 ;
      }
      else {
        set_temperature = set_temperature - 0.1;
      }
    }
    Last_State = clk_State; // Actualiza el estado anterior del reloj con el estado actual
  }

  if (menu_activated == 2)
  {
    clk_State =   (PINB & B00000001); // pin 8 estado? ¿Es alto?
    dt_State  =   (PINB & B00000010);
    if (clk_State != Last_State) {
      // Si el estado de los datos es diferente al estado del reloj, eso significa que el codificador está girando hacia la derecha
      if (dt_State != clk_State) {
        set_humedad = set_humedad + 0.5 ;
      }
      else {
        set_humedad = set_humedad - 0.5;
      }
    }
    Last_State = clk_State; // Actualiza el estado anterior del reloj con el estado actual
  }


  ////////////////////////////////////
  if (menu_activated == 3)
  {
    clk_State =   (PINB & B00000001); // pin 8 estado?
    dt_State  =   (PINB & B00000010);
    if (clk_State != Last_State) {
      // Si el estado de los datos es diferente al estado del reloj, eso significa que el codificador está girando hacia la derecha
      if (dt_State != clk_State) {
        kp = kp + 1 ;
      }
      else {
        kp = kp - 1;
      }
    }
    Last_State = clk_State; // Actualiza el estado anterior del reloj con el estado actual
  }


  ////////////////////////////////////


  ////////////////////////////////////

  ////////////////////////////////////


  ////////////////////////////////////////////////
  // ¡Se presionó el botón!
  if (PINB & B00001000) //Pin D11 is HIGH?
  {
    button_pressed = 1;
  }

  
  // Navegamos por los 4 menús con cada botón presionado.
  else if (button_pressed == 1)
  {



    if (menu_activated == 5)
    {
   
    }



    if (menu_activated == 4)
    {
 
    }

    if (menu_activated == 3)
    {

    }

    if (menu_activated == 2)
    {
     menu_activated = 0;
      PID_values_fixed = 1;
      button_pressed = 0;
      delay(500);
    }

    if (menu_activated == 1)
    {
      menu_activated = menu_activated + 1;
      button_pressed = 0;
      set_humedad = set_humedad + 1;
      delay(500);
    }

    if (menu_activated == 0 && PID_values_fixed != 1)
    {
      menu_activated = menu_activated + 1;
      button_pressed = 0;
      set_temperature = set_temperature + 1;
      delay(500);
    }
    PID_values_fixed = 0;

  }
}


void horario_1() {

  if ((hora == h1_c1) && (minuto == m1_c1) && (segundo == s1_c1))  activar();
  if ((hora == h2_c1) && (minuto == m2_c1) && (segundo == s2_c1))  activar();
  if ((hora == h3_c1) && (minuto == m3_c1) && (segundo == s3_c1))  activar();
  if ((hora == h4_c1) && (minuto == m4_c1) && (segundo == s4_c1))  activar();
  if ((hora == h5_c1) && (minuto == m5_c1) && (segundo == s5_c1))  activar();
  if ((hora == h6_c1) && (minuto == m6_c1) && (segundo == s6_c1))  activar();
  if ((hora == h7_c1) && (minuto == m7_c1) && (segundo == s7_c1))  activar();
  if ((hora == h8_c1) && (minuto == m8_c1) && (segundo == s8_c1))  activar();
  if ((hora == h9_c1) && (minuto == m9_c1) && (segundo == s9_c1))  activar();
  if ((hora == h10_c1) && (minuto == m10_c1) && (segundo == s10_c1))  activar();
  if ((hora == h11_c1) && (minuto == m11_c1) && (segundo == s11_c1))  activar();
  if ((hora == h12_c1) && (minuto == m12_c1) && (segundo == s12_c1))  activar();
  if ((hora == h13_c1) && (minuto == m13_c1) && (segundo == s13_c1))  activar();
  if ((hora == h14_c1) && (minuto == m14_c1) && (segundo == s14_c1))  activar();
  if ((hora == h15_c1) && (minuto == m15_c1) && (segundo == s15_c1))  activar();
  if ((hora == h16_c1) && (minuto == m16_c1) && (segundo == s16_c1))  activar();
}
void activar() {
  digitalWrite(15, HIGH);
  delay(15000);
  digitalWrite(15, LOW);
  delay(50);
}


void ISR_RT()
{

  temp = mlx.readAmbientTempC();

  //Serial.print(temp);




  /*********************************************************/
  /*****Bloque de control del lazo de realimentación (R/S)***/

  // Entrada al bloque de control = señal medida
  ek = temp;

  // Ecuaciones de estado bloque de lazo de realimentación


  x1s = x1 + ek;

  uk = n4 * ek + a0 * x1;

  x1 = x1s;

  /*********************************************************/
  /*****Bloque de control de setPoint (T/S=R/S)***/

  // Entrada al bloque de control = setPoint
  ekt = set_temperature;

  // Ecuaciones de estado bloque de control de setPoint
  x1st = x1t + ek;

  // Salida de control del bloque de setPoint
  ukt = n4 * ekt + a0 * x1t;
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

  pwmval = 255 - pwmval;

  // Lazo cerrado
  analogWrite(IN1, pwmval);
  if (temp<25){  analogWrite(IN1,0);}




if(temp>ekt)
{
  
 digitalWrite(14,HIGH);
  delay(1);
 }
 else
 { digitalWrite(14,LOW);
 
 delay(1);
 }





  
}













void ISR_RT2()
{

  humedad = sht.getHumidity();

  //Serial.print(temp);




  /*********************************************************/
  /*****Bloque de control del lazo de realimentación (R/S)***/

  // Entrada al bloque de control = señal medida
  ek1 = humedad;

  // Ecuaciones de estado bloque de lazo de realimentación


  x1s1 = x11 + ek1;

  uk1 = n41 * ek1 + a01 * x11;

  x11 = x1s1;

  /*********************************************************/
  /*****Bloque de control de setPoint (T/S=R/S)***/

  // Entrada al bloque de control = setPoint
  ekt1 = set_humedad;

  // Ecuaciones de estado bloque de control de setPoint
  x1st1 = x1t1 + ek1;

  // Salida de control del bloque de setPoint
  ukt1 = n41 * ekt1 + a01 * x1t1;
  // Actualización de estados
  x1t1 = x1st1;

  // La señal de control que va a la planta es la resta entre
  // la señal de control de setPoint y la señal de control
  // del lazo de realimentación


  // Lazo cerrado

  pwmval1 = (int)(ukt1 - uk1);

  //     Función de saturación
  if (pwmval1 < 0)
    pwmval1 = 0;
  if (pwmval1 > 255)
    pwmval1 = 255;

  pwmval1 = 255 - pwmval1;

  // Lazo cerrado
  analogWrite(PWM_pin, pwmval1);
  
}
