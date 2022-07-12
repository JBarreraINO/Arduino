#include <stdio.h>
#include <string.h>
#include <Servo.h>

//--------------------------------------------------------------------------------------//
// LISTADO DE PINES Y CONECCIONES
#define LED1    13
#define LED2     4
#define SW1     12
#define SW2      2
#define ON_RF   17
#define OFF_RF  16
#define TURBINA  3

#define MOTORD_AIN1  11   
#define MOTORD_AIN2  10  
#define MOTORD_PWM   5

#define MOTORI_AIN1    7
#define MOTORI_AIN2    8
#define MOTORI_PWM     6

//------------------------------------------------------------------------------------//
//Sensores de Linea PD

#define NUM_SENSORS             8  // Numero de sensores que usa
#define MAX_CONTADOR            300  

#define COLOR_LINE true  //true linea blanca
//#define COLOR_LINE false  //false linea negra

unsigned char pins[NUM_SENSORS] = {A7,A6,A5,A4,A3,A2,A1,A0}; // SENSORES DEL 0 AL 8 QTR8
unsigned int sensorValues[NUM_SENSORS];
unsigned int sensorValues_max[NUM_SENSORS];
unsigned int sensorValues_min[NUM_SENSORS];
unsigned int position_line;
int error[10];

//------------------------------------------------------------------------------------//
//TURBINA -- ESC FUNCIONA COMO SERVO
Servo myservo; 


//--------------------------------------------------------------------------------------//
//PARAMETROS del Control del Velocista
//AQUI SE MODIFICAN LOS PARAMETROS DE COMPETENCIA
const int VELCIDAD_MAXIMA =   250;    //Velocidad Maxima (entre 0 y 255)
float CTE_PROPORCIONAL = 6;      //Constante de Control Proporcional (ente 1 y 20)
float CTE_DERIVATIVA =   10;     //Constante de Control Diferencia (ente 1 y 20)                                                                                                                                                                                                                                         
int V_TURBINA = 100;             //Velocidad Turbina en Competencia (entre 90 y 150)

 


//Variables para el de control
int maximun_tolerance;
float derivative;
float power_difference_fl;
int power_difference;
long integral;

void setup()
{

  int val;
  
  //INICIO DE PUERTO DE ESC
  myservo.attach(TURBINA);
  
  

  
  
  // Motores detenidos
  SetSpeeds(0,0);    
    
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(SW1,INPUT);
  pinMode(SW2,INPUT);
  pinMode(ON_RF,INPUT);
  pinMode(OFF_RF,INPUT);
  
  //ENCENDER LOS LEDS
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, HIGH);
  
  // ESPERA QUE SE OPRIMA EL SW1 
  do{
   val = digitalRead(SW1);
  }while (val == HIGH);
  
  //APAGAR LOS LEDS
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);  
  

//-------------Instrucciones para Empezar a hacer la Calibracion de Sensores--------------------------------------//
  
  //ESPERA QUE SE RETIRE EL DEDO DEL SW1
  delay(1000); 
  
  // Enciende el leds para indicar que se esta calibrando.
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, HIGH);
  
  
  Reset_Calibracion();
  int tiempo_cal = 250;
  
  //GIRA MIENTRA CALIBRA
  SetSpeeds(-100, 100);
  
  while(tiempo_cal--)
  {
      Calibrar_Sensores(pins);
      delay(10);
  }
 
  // Apaga el led para indicar que se termino la calibracion.
  digitalWrite(LED2, LOW);     
  digitalWrite(LED1, LOW); 
 
 //stop Motors
  SetSpeeds(0,0);
    
  delay(200);
  digitalWrite(LED2, HIGH);     
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED2, LOW);     // Parpadeo para indicar que el robot esta listo.
  digitalWrite(LED1, LOW);
  delay(200);                  // Parpadeo para indicar que el robot esta listo.
  digitalWrite(LED2, HIGH);     
  digitalWrite(LED1, HIGH);    // Parpadeo para indicar que el robot esta listo.
  delay(200);
  digitalWrite(LED2, LOW);     // Parpadeo para indicar que el robot esta listo.
  digitalWrite(LED1, LOW);
  delay(200);
  //---------------------------Fin Calibracion de Sensores----------------------------------------------------//
  
  // SECUENCIA PARA VERIFICAR SI LA CALIBRACION ESTA BIEN
  // TERMINA CUANDO SE OPRIME SW1
  
  val = digitalRead(SW1);  
  while (val == HIGH )
  {    
   
   position_line = Leer_linea(pins,position_line ); // leemos posicion de la linea en la variable position
   int proportional = (int)position_line - 3500;
   
   Serial.println(proportional);
   
   proportional = proportional/35;//variaa entre 100 y -100
   
   
 if (proportional < -20)
 {
     digitalWrite(LED2, HIGH);
     digitalWrite(LED1, LOW); 
  }
  else  if (proportional > 20 )
  {
     digitalWrite(LED2, LOW);
     digitalWrite(LED1, HIGH);    
  }
  else  
  {
   digitalWrite(LED2, HIGH);
   digitalWrite(LED1, HIGH);    
  }
  
  power_difference_fl = (proportional * CTE_PROPORCIONAL);
  power_difference = (int) power_difference_fl;
  
  maximun_tolerance = (VELCIDAD_MAXIMA*2);
  
  if (power_difference > maximun_tolerance)
    power_difference = maximun_tolerance;
    
  if (power_difference < -(maximun_tolerance))
    power_difference = -(maximun_tolerance);
  
   SetSpeeds(-power_difference,  power_difference);
   
   val = digitalRead(SW1);
  }
  
   //---------------------------FIN DE PRUEBA DE CALIBRACION----------------------------------------------------//

  
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);
   delay(200);
  digitalWrite(LED2, HIGH);     
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED2, LOW);     
  digitalWrite(LED1, LOW);
  delay(200);                  
  digitalWrite(LED2, HIGH);     
  digitalWrite(LED1, HIGH);   
 
 //---------------------------CONTROL DE INICIO DE TURBINA Y TEST (OPCIONAL) ----------------------------------------------------// 
  myservo.write(80); 
  delay(2000);
  myservo.write(30); 
  delay(500);
  
  for (int i = 90; i <= 110; i++)
  {
    myservo.write(i);
    delay(100);
  }
  delay(2000);
  myservo.write(40);
 
  
  //---------------------------LISTO PARA COMPETIR----------------------------------------------------// 
  //---------------------------SELECIONAR METODO DE INICO----------------------------------------------------//
  
// ESPERA QUE SE OPRIMA EL SW2

 digitalWrite(LED2, HIGH);
 digitalWrite(LED1, HIGH);
 
do{
 val = digitalRead(SW1);
}while (val == HIGH);

 

// INICIO CON MODULO REMOTO

//   int rf_control = digitalRead(ON_RF);
//   while(rf_control == LOW)
//   {
//      rf_control = digitalRead(ON_RF);
//   }


// Si se necesitan 5 Segundos
//delay(5000); 

//INICIO DE TURBINA
   myservo.write(V_TURBINA);
   integral = 0;
  
}

 

 

void loop()
{
 
//APAGADO POR MODULO REMOTO
//   int rf_control = digitalRead(OFF_RF);
//   if (rf_control == LOW)
//   {
//       myservo.write(40); 
//       SetSpeeds(0, 0);
//       while(1)
//       {;}
//   } // STOP ROBOT

// leemos posicion de la linea en la variable position_line
position_line = Leer_linea(pins,position_line ); 

// Referencia donde seguira la linea, mitad sensores.
int proportional = (int)position_line - 3500;

//varia entre 100 y -100
proportional= proportional/35;
   
  error[9]=error[8];
  error[8]=error[7];
  error[7]=error[6];
  error[6]=error[5];
  error[5]=error[4];
  error[4]=error[3];
  error[3]=error[2];
  error[2]=error[1];
  error[1]=error[0];
  error[0]=proportional;
  

 if (error[0] < -20)
 {
     digitalWrite(LED2, HIGH);
     digitalWrite(LED1, LOW); 
  }
  else  if (error[0] > 20 )
  {
     digitalWrite(LED2, LOW);
     digitalWrite(LED1, HIGH);    
  }
  else  
  {
   digitalWrite(LED2, HIGH);
   digitalWrite(LED1, HIGH);    
  }
 

    // Calculos PD
  derivative = (error[0] - error[5]) * CTE_DERIVATIVA;
  integral += error[0];

  power_difference_fl = (error[0]*CTE_PROPORCIONAL) + (derivative);//+(integral/10000);
  power_difference = (int) power_difference_fl;
  
  maximun_tolerance = (VELCIDAD_MAXIMA*2);
  if (power_difference > maximun_tolerance)
    power_difference = maximun_tolerance;
    
  if (power_difference < -(maximun_tolerance))
    power_difference = -(maximun_tolerance);
    
    
  //Control de motores
  if (power_difference < 0)
    SetSpeeds(VELCIDAD_MAXIMA, VELCIDAD_MAXIMA  + power_difference);
  else
    SetSpeeds(VELCIDAD_MAXIMA- power_difference , VELCIDAD_MAXIMA );
 
   delay(1);
}

/////////////////////////////////////////////////////////////////
///FUNCIONES LOCALES
/////////////////////////////////////////////////////////////////


void SetSpeeds(int motor_izquierdo,int motor_derecho)
{

  if(motor_derecho==0)
  {
     digitalWrite(MOTORD_AIN1, HIGH);
     digitalWrite(MOTORD_AIN2, HIGH);
     analogWrite(MOTORI_PWM, motor_derecho);
  }
  else if(motor_derecho>0)
  {
    
     if(motor_derecho>255)
         {
            motor_derecho = 255;
         }
     digitalWrite(MOTORD_AIN1, LOW);
     digitalWrite(MOTORD_AIN2, HIGH);
      analogWrite(MOTORD_PWM, motor_derecho);
  }
  else
    {
      
      if(motor_derecho<-255)
         {
            motor_derecho = -255;
         }
     digitalWrite(MOTORD_AIN1, HIGH);
     digitalWrite(MOTORD_AIN2, LOW);
     analogWrite(MOTORD_PWM, -motor_derecho);
  }
 
 
 
   if(motor_izquierdo==0)
  {
     digitalWrite(MOTORI_AIN1, HIGH);
     digitalWrite(MOTORI_AIN2, HIGH);
     analogWrite(MOTORI_PWM, motor_izquierdo);
  }
  else if(motor_izquierdo>0)
  { 
    if(motor_izquierdo>255)
    {
      motor_izquierdo = 255;
    }
    
     digitalWrite(MOTORI_AIN1, LOW);
     digitalWrite(MOTORI_AIN2, HIGH);
     analogWrite(MOTORI_PWM, motor_izquierdo);
  }
  else
    {
       if(motor_izquierdo<-255)
         {
            motor_izquierdo = -255;
         }
         
     digitalWrite(MOTORI_AIN1, HIGH);
     digitalWrite(MOTORI_AIN2, LOW);
     analogWrite(MOTORI_PWM, -motor_izquierdo);
  }
  
}

 

void Reset_Calibracion(void)
{
   for(int x=0; x<NUM_SENSORS; x++)
   {
     sensorValues_max[x] = 0; 
     sensorValues_min[x] = MAX_CONTADOR;
   }
}

 

void Calibrar_Sensores(unsigned char* pins)
{   
    Leer_sensores (pins);
    
    for(int x=0; x<NUM_SENSORS; x++)
     {
       if(sensorValues[x] > sensorValues_max[x])
       {
          sensorValues_max[x] = sensorValues[x];
       }
       
       if(sensorValues[x] < sensorValues_min[x])
       {
          sensorValues_min[x] = sensorValues[x];
       }
     }
}

 

int Leer_linea(unsigned char* pins, int linea_anterior)
{   
   int linea, suma, activos;
   
    Leer_sensores (pins);
    
    suma = 0;
    linea = 0;
    activos = 0;
    
    for(int x=0; x<NUM_SENSORS; x++)
     {
       int rango_comparacion = (sensorValues_max[x] - sensorValues_min[x])/2;
       
       if(COLOR_LINE)
       {
             if(sensorValues[x] > rango_comparacion) // ES MAYOR ES POR QUE ES NEGRA LINEA - FONDO BLANCO
             {
                suma += x*1000;
                activos ++;
             }
       }
       else
       {
             if(sensorValues[x] < rango_comparacion) // ES MENOR ES POR QUE ES BLANCO LINEA-- FONDO NEGRO
             {
                suma += x*1000;
                activos ++;
             }       
       }
     }
     
     if(activos > 0)
     {
       linea = suma/activos;
     }
     else
     {
       linea = linea_anterior;
     
     }
     
     return linea;
     
}


void Leer_sensores (unsigned char* pins)
{
  
     for(int x=0; x<NUM_SENSORS; x++)
     {
       digitalWrite(pins[x], HIGH);
     }
    
for(int x=0; x<NUM_SENSORS; x++)
       {
              sensorValues[x]=analogRead(pins[x]);
       }
}
