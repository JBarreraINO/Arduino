 //*********PARAMTROS A CALIBRAR *************************************************************************************************
#include<Servo.h>

Servo fan;
int velocidad =250; // Velocidad crucero de robot max 255

float Kp = 0.15; // calibracion proporciona 0.7; 2; 1.1
float Kd = 3.05;  //  calibracion derivativo 9.65
float Ki=0.003;
int sensibilidad = 300;
int frente = 190;   // Velocidad a la que ira el motor hacia adelante cuando pierda la linea max 255  198 para sensores cortos
int reversa = 190;  // Velocidad a la que ira el motor hacia atras cuando pierda la linea    max 255  198 para sensores cortos

int color = 1;      // 1 linea negra 2 linea blanca
//********CONEXION DE PUERTOS****************************************************************************************************
int OP = A4;   // A0 conectdado a OP    SALIDA DEL MULTIPLEXOR

int led = 13;  // Led default de Arduino

int pini = 9;
int pwmi = 5;
int pind = 6;
int pwmd = 3;

//int go = 8;   // Puerto donde se conecta el arrancador ( si el modulo no esta conectado, debe ponerse una resistencia pull-down)
//int rdy = 12;
//int boton_izq = 4; // boton izquierdo
//int boton_der = 7; // boton derecho
//int lon = 11;
//*******VARIABLES A UTILIZAR****************************************************************************************************



int mins1 = 255, mins2 = 255, mins3 = 255, mins4 = 255, mins5 = 255, mins6 = 255, mins7 = 255, mins8 = 255, mins9 = 255, mins10 = 255, mins11 = 255, mins12 = 255, mins13 = 255, mins14 = 255, mins15 = 255, mins16 = 255;

int maxs1 = 0, maxs2 = 0, maxs3 = 0, maxs4 = 0, maxs5 = 0, maxs6 = 0, maxs7 = 0, maxs8 = 0, maxs9 = 0, maxs10 = 0, maxs11 = 0, maxs12 = 0, maxs13 = 0, maxs14 = 0, maxs15 = 0, maxs16 = 0;

int maxs[16];
int mins[16];
int valor_sensor[16];

int valor_bd = 0, state_go = 0, state_rdy = 0, allow_off = 0, valor_bi = 0, memory_deg = 0, posicion = 0, MUESTREO = 1, c = 0, espera = 0, modo = LOW, value_x = 0;
int vel = 0;
unsigned long presente = 0;
long antes = 0;
long pausa = 70;
unsigned long pasado = 0;
unsigned long ahora;
double ERROR_POSICION = 0;
double ERROR_ULTIMO = 0;
double ERROR_I=0;
double CX = 0;
double error1=0;
double error2=0;
double error3=0;
double error4=0;
double error5=0;
double error6=0;

void setup()
{
 //Serial.begin(115200);
/*  TCCR0B_PRESCALER 6 Y 5
CS02 CS01 CS
0 0 0 No clock source (Timer/Counter stopped)
0 0 1 clkI/O/(no prescaling)
0 1 0 clkI/O/8 (from prescaler)
0 1 1 clkI/O/64 (from prescaler)
1 0 0 clkI/O/256 (from prescaler)
1 0 1 clkI/O/1024 (from prescaler)
1 1 0 External clock source on T0 pin. Clock on falling edge.
1 1 1 External clock source on T0 pin. Clock on rising edge.



TCCR2B_PRESCALER 11 Y 3
 CS22 CS21 CS20
0 0 0 No clock source (Timer/Counter stopped).
0 0 1 clkT2S/(no prescaling)
0 1 0 clkT2S/8 (from prescaler)
0 1 1 clkT2S/32 (from prescaler)
1 0 0 clkT2S/64 (from prescaler)
1 0 1 clkT2S/128 (from prescaler)
1 1 0 clkT2S/256 (from prescaler)
1 1 1 clkT2S/1024 (from prescaler)
*/

//TCCR0B |=B00000001;//NO PRESCALING
//TCCR0B |=B00000010;//clkI/O/8
//TCCR0B |=B00000011;//clkI/O/64
//TCCR0B |=B00000110;//clkI/O/256
//TCCR0B |=B00000111;//clkI/O/1024


//TCCR2B |=B00000001;//NO PRESCALING
//TCCR2B |=B00000010;//clkI/O/8
//TCCR2B |=B00000011;//clkI/O/32
//TCCR2B |=B00000100;//clkI/O/64
//TCCR2B |=B00000101;//clkI/O/128
//TCCR2B |=B00000110;//clkI/O/256
//TCCR2B |=B00000111;//clkI/O/1024

  //TCCR2A =   B00000011;  // Fast PWM MODE - OCA DISCONETED
 // TCCR2B =  (TCCR2A & B11110111) ;  
  
 // TIMSK2 = (TIMSK2 & B11111000) | 0x07;

  DDRC=B00001111;//pinmode(s0,s1,s2,s3,output)
  DDRD=B01101000;//pinmode(3,5,6,output) PORTD=B01000000;
  DDRB=B00101010;//pinmode(9,11,13)
   DDRD &=~B10010000;//ENTRADAS 4,7
   DDRC &=~B00010000;//ENTRADAS A4
   DDRB &=~B00010001;//ENTRADAS 8,12
   //PORTB |=B00001000; //11 HIGH
 fan.attach(10);
 fan.writeMicroseconds(1000);
rutina1:
  
  delay(1000);
 
   PORTB |=B00100000; //13 HIGH
rutina2:
  lectura();
  if ( valor_bi == LOW ) {
    value_x = 1;
  }
  if ( valor_bi == HIGH && value_x == 1 ) {
    delay (50);
    goto rutina3;
  }
  goto rutina2;


  //****************************************************************************************************************************************************************************


rutina3:   // Calibracion de sensores

  while ( espera < 4000) {
    lectura();
    if ( valor_bi == LOW ) {
      espera = 5000;
    }
    presente = millis();
    if (presente - antes > pausa) {
      antes = presente;
      if (modo == LOW) {
        modo = HIGH;
      }
      else {
        modo = LOW;
      }
      digitalWrite(led, modo);
    }



    if (valor_sensor[0] <  mins1) {
      mins1 = valor_sensor[0];
    }
    if (valor_sensor[1] <  mins2) {
      mins2 = valor_sensor[1];
    }
    if (valor_sensor[2] <  mins3) {
      mins3 = valor_sensor[2];
    }
    if (valor_sensor[3] <  mins4) {
      mins4 = valor_sensor[3];
    }
    if (valor_sensor[4] <  mins5) {
      mins5 = valor_sensor[4];
    }
    if (valor_sensor[5] <  mins6) {
      mins6 = valor_sensor[5];
    }
    if (valor_sensor[6] <  mins7) {
      mins7 = valor_sensor[6];
    }
    if (valor_sensor[7] <  mins8) {
      mins8 = valor_sensor[7];
    }
    if (valor_sensor[8] <  mins9) {
      mins9 = valor_sensor[8];
    }
    if (valor_sensor[9] <  mins10) {
      mins10 = valor_sensor[9];
    }
    if (valor_sensor[10] <  mins11) {
      mins11 = valor_sensor[10];
    }
    if (valor_sensor[11] <  mins12) {
      mins12 = valor_sensor[11];
    }
    if (valor_sensor[12] <  mins13) {
      mins13 = valor_sensor[12];
    }
    if (valor_sensor[13] <  mins14) {
      mins14 = valor_sensor[13];
    }
    if (valor_sensor[14] <  mins15) {
      mins15 = valor_sensor[14];
    }
    if (valor_sensor[15] <  mins16) {
      mins16 = valor_sensor[15];
    }

    if (valor_sensor[0] >  maxs1) {
      maxs1 = valor_sensor[0];
    }
    if (valor_sensor[1] >  maxs2) {
      maxs2 = valor_sensor[1];
    }
    if (valor_sensor[2] >  maxs3) {
      maxs3 = valor_sensor[2];
    }
    if (valor_sensor[3] >  maxs4) {
      maxs4 = valor_sensor[3];
    }
    if (valor_sensor[4] >  maxs5) {
      maxs5 = valor_sensor[4];
    }
    if (valor_sensor[5] >  maxs6) {
      maxs6 = valor_sensor[5];
    }
    if (valor_sensor[6] >  maxs7) {
      maxs7 = valor_sensor[6];
    }
    if (valor_sensor[7] >  maxs8) {
      maxs8 = valor_sensor[7];
    }
    if (valor_sensor[8] >  maxs9) {
      maxs9 = valor_sensor[8];
    }
    if (valor_sensor[9] >  maxs10) {
      maxs10 = valor_sensor[9];
    }
    if (valor_sensor[10] >  maxs11) {
      maxs11 = valor_sensor[10];
    }
    if (valor_sensor[11] >  maxs12) {
      maxs12 = valor_sensor[11];
    }
    if (valor_sensor[12] >  maxs13) {
      maxs13 = valor_sensor[12];
    }
    if (valor_sensor[13] >  maxs14) {
      maxs14 = valor_sensor[13];
    }
    if (valor_sensor[14] >  maxs15) {
      maxs15 = valor_sensor[14];
    }
    if (valor_sensor[15] >  maxs16) {
      maxs16 = valor_sensor[15];
    }

  }  // Termina calibracion de sensores


  digitalWrite ( led, LOW);
  delay (500);



rutina4:

  digitalWrite ( led, HIGH);
  lectura();
  if ( state_go == HIGH) {
    allow_off = 1;
    goto PD;
  }
  if ( valor_bi == LOW) {
    c = 1;
  }

  if(valor_bd==LOW)
  {
  fan.write(1500);
   delay(150);
  }
  if ( valor_bi == HIGH && c == 1 ) {
    delay ( 50);
    digitalWrite ( led, LOW);
    
    
 
    goto PD;
  }
  goto rutina4;



off:
  lectura();
  if ( state_go == HIGH ) {
    goto PD;
  }
  analogWrite ( pwmi , 0); analogWrite ( pwmd, 0);
  fan.write(1000);
  goto off;





  //*****************************************************************> PROGRAMA PRINCIPAL DE PD <**************************************************************************************

PD:

  if ( state_go == 0 && allow_off == 1 ) {
    goto off;
  }
    //velocidad=map(velocidad,0,255,0,180);
  ahora = millis();
  int ACTUAL = ahora - pasado;
  if (ACTUAL >= MUESTREO)
  {

    lectura();
   
    ERROR_POSICION = valor_sensor[0] * (-1) + valor_sensor[1] * (-1) + valor_sensor[2] * (-1) + valor_sensor[3] * (-.8) + valor_sensor[4] * (-.6) + valor_sensor[5] * (-.4) + valor_sensor[6] * (-.2) + valor_sensor[7] * (-.1) + valor_sensor[8] * (.1) + valor_sensor[9] * (.2) + valor_sensor[10] * (.4) + valor_sensor[11] * (.6) + valor_sensor[12] * (.8) + valor_sensor[13] * (1) + valor_sensor[14] * (1) + valor_sensor[15] * (1);

  
    double ERROR_D = (ERROR_POSICION - ERROR_ULTIMO);
    float P = Kp * ERROR_POSICION;
    float D = Kd * ERROR_D;
    float I = Kp * ERROR_I;

  error6=error5;
  error5=error4;
  error4=error3;
  error3=error2;
  error2=error1;
  error1=ERROR_POSICION;

    CX = P + D + I;

    pasado = ahora;
    ERROR_ULTIMO = ERROR_POSICION;

    if ( CX >=  255 ) {
      CX =  255;
    }
    if ( CX <= -255 ) {
      CX = -255;
    }




    int pwm1 = velocidad + (CX);
    int pwm2 = velocidad - (CX);

    if ( pwm1 >= 255 ) {
      pwm1 = 255;
    }
    if ( pwm2 >= 255 ) {
      pwm2 = 255;
    }


    if ( valor_sensor[2] > sensibilidad | valor_sensor[13] > sensibilidad ) {
      posicion = 0;//en rango
    }
    if ( valor_sensor[1]> sensibilidad && valor_sensor[7] < sensibilidad && valor_sensor[8] < sensibilidad  ) {
      posicion = 1;//sale hacia izquierda
    }

    if ( valor_sensor[14] > sensibilidad  && valor_sensor[7] < sensibilidad && valor_sensor[8] < sensibilidad  ) {
      posicion = 16;//SALE A DERECHA
    }
    

    float r1 = abs(pwm1);
    float r2 = abs (pwm2);

    if ( r1 >= 255 ) {
      r1 = 255;
    }
    if ( r2 >= 255 ) {
      r2 = 255;
    }
//Si te sales
   

    if ( posicion == 16 )
    { analogWrite ( pwmd, reversa); PORTD |=B01000000;//6 HIGH
      analogWrite ( pwmi, frente);  PORTB |=B00000010; //9 HIGH
      
    }

    if ( posicion == 1 )
    { analogWrite ( pwmd, frente);  PORTD &=B10111111;//6 LOW
      analogWrite ( pwmi, reversa);  PORTB &=B11111101; //9 LOW
     
    }
/*
   if (posicion ==1 | posicion==16)
{
  fan.write(1900);
}
*/
//control de motores EN RANGO 
    if ( posicion != 16 && posicion != 1 ) 
    {
       //fan.write(1300);

      if ( pwm1 < 0 ) {
        analogWrite ( pwmd, r1);
        PORTD &=B10111111;// 6 LOW
          digitalWrite ( 13, HIGH);
             
           
      }
      if ( pwm2 < 0 ) {
        analogWrite ( pwmi, r2);
         PORTB |=B00000010;//9 HIGH
       
      }

      if ( pwm1 == 0 ) {
        analogWrite ( pwmd, 0);
       PORTD &=B10111111;//6 LOW
        
      
      }
      if ( pwm2 == 0 ) {
        analogWrite ( pwmi, 0);
        PORTB &=B11111101; //9 LOW 
      
        
      }

      if ( pwm1 > 0 ) {
        analogWrite ( pwmd, pwm1);
        PORTD |=B01000000;//6 HIGH
      
      }
      if ( pwm2 > 0 ) {
        analogWrite ( pwmi, pwm2);
        PORTB &=B11111101; //9 LOW 
       
      }
    }
  }
  goto PD;
}




void loop() {}

void lectura() {

  valor_bi =   (PIND >> 4 &  B00010000 >> 4);
  valor_bd =  (PIND >> 7 &   B10000000 >> 7);
  state_go =  (PINB >> 0 &   B00000001 >> 0);
  state_rdy = (PINB >> 4 &   B00010000 >> 4);

//s0
PORTC=B00000000;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[0] =(ADCL | (ADCH << 8))/4;




PORTC=B00000001;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[1] =(ADCL | (ADCH << 8))/4;



PORTC=B00000010;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[2] =(ADCL | (ADCH << 8))/4;

PORTC=B00000011;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[3] =(ADCL | (ADCH << 8))/4;

PORTC=B00000100;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[4] =(ADCL | (ADCH << 8))/4;

PORTC=B00000101;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[5] =(ADCL | (ADCH << 8))/4;

PORTC=B00000110;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[6] =(ADCL | (ADCH << 8))/4;

PORTC=B00000111;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[7] =(ADCL | (ADCH << 8))/4;

PORTC=B00001000;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[8] =(ADCL | (ADCH << 8))/4;

PORTC=B00001001;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[9] =(ADCL | (ADCH << 8))/4;

PORTC=B00001010;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[10] =(ADCL | (ADCH << 8))/4;

PORTC=B00001011;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[11] =(ADCL | (ADCH << 8))/4;

PORTC=B00001100;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[12] =(ADCL | (ADCH << 8))/4;

PORTC=B00001101;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[13] =(ADCL | (ADCH << 8))/4;

PORTC=B00001110;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[14] =(ADCL | (ADCH << 8))/4;

PORTC=B00001111;
ADMUX |= B00000100;
ADMUX |=B11000000;
ADCSRA |= B11000000;
while (bit_is_set(ADCSRA, ADSC));
valor_sensor[15] =(ADCL | (ADCH << 8))/4;










/*
for(int i=0;i<16;i++){
  digitalWrite(S0,i&0x01);
  digitalWrite(S1,i&0x02);
  digitalWrite(S2,i&0x04);
  digitalWrite(S3,i&0x08);
   valor_sensor[i]=analogRead(OP)/4;
}
*/




  if ( color == 2 )
  {
    for(int i=0;i<16;i++){
     valor_sensor[i]= map(valor_sensor[i], 0 , 255 , 255, 0);
    }
  }

   for(int i=0;i<16;i++){
valor_sensor[i]= map(valor_sensor[i], mins1 , maxs1 , 0, 255);}

}
