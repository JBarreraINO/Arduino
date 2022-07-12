#include <QTRSensors.h>

#include <math.h>
#define s1 A3  
#define s2 A4
#define s3 A2
#define pwmA 5
#define AIN1 6
#define AIN2 7
#define pwmB 3
#define BIN1 4
#define BIN2 2


float sensor_izquierdo=0; 
float sensor_centro=0;
float sensor_derecho=0;
int sl1, sl2=0;
QTRSensors qtr;

const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];



void setup() {
Serial.begin(9600);
pinMode(s1,INPUT); 
pinMode(s2,INPUT);
pinMode(s3,INPUT);

pinMode(pwmA,OUTPUT);
pinMode(AIN1,OUTPUT);
pinMode(AIN2,OUTPUT);
pinMode(pwmB,OUTPUT);
pinMode(BIN1,OUTPUT);
pinMode(BIN2,OUTPUT);


////////////////////////////////////
// configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1}, SensorCount);
 

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); 
  Serial.begin(9600);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();


  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(500);

////////////////////////////////////

}


void loop() {
 
sensor_izquierdo=distancia(1,100);
sensor_centro=distancia(2,100);
sensor_derecho=distancia(3,100);
uint16_t position = qtr.readLineBlack(sensorValues);

if(sensorValues[0]<360)
 sl1=0;
else
sl1=1; 
if(sensorValues[1]<360)
sl2=0;
else
sl2=1; 

/////////////////////////////////////////////

////////////////////////////////////////////



/*
Serial.print("Sensor 1: "); 
Serial.print(sensor_izquierdo);

Serial.print(" Sensor 2: "); 
Serial.print(sensor_centro);

Serial.print(" Sensor 3: "); 
Serial.print(sensor_derecho);

Serial.print(" sensor linea: ");
Serial.print(sl1);
Serial.print(" sensor linea: ");
Serial.println(sl2);
*/
//delay(200);
 
if(sl2==0 && sl1==1)
{retroceder();
 Serial.println(" retroceder ");

 delay(300);
 //detener();
  }
else 
 {if(sl1==0 && sl2==1 )
   {avanzar();
    Serial.println(" avanzar ");

    delay(300);
    //detener();
     }
  else 
    {if (sensor_centro<15)
       {avanzar();
          Serial.println(" atacar ");
           }
    else
       {if(sensor_izquierdo<15)
         {izquierda();
          Serial.println(" izquierda ");
         }         
        if(sensor_derecho<15)
         {derecha();
          Serial.println(" derecha ");
         }
        if(sensor_derecho>21 && sensor_centro>21 && sensor_izquierdo>21 )
        { buscar();
         Serial.println(" buscar ");
        }
        }  
       
     }  
  }

}
/////FUNCIONES /////////////////
float distancia(int sen,int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    if(sen==1)
    suma=suma+analogRead(A3);
    if(sen==2)
    suma=suma+analogRead(A4);
    if(sen==3)
    suma=suma+analogRead(A2);
  }  
  float adc=suma/n;
  float distancia_cm = 17569.7 * pow(adc, -1.2062);
  return(distancia_cm);
  
  } 

////////AVANZAR//////////////////
void avanzar(void) 
{analogWrite(pwmB,255);
digitalWrite(BIN1,0); 
digitalWrite(BIN2,1);
analogWrite(pwmA,255);
digitalWrite(AIN1,0); 
digitalWrite(AIN2,1);
} 
////////RETROCEDER//////////////////
void retroceder(void) 
{analogWrite(pwmB,255);
digitalWrite(BIN1,1); 
digitalWrite(BIN2,0);
analogWrite(pwmA,255);
digitalWrite(AIN1,1); 
digitalWrite(AIN2,0);
} 

////////IZQUIERDA//////////////////
void izquierda(void) 
{analogWrite(pwmB,255);
digitalWrite(BIN1,0); 
digitalWrite(BIN2,1);
analogWrite(pwmA,255);
digitalWrite(AIN1,1); 
digitalWrite(AIN2,0);
} 

////////DERECHA//////////////////
void derecha(void) 
{analogWrite(pwmB,255);
digitalWrite(BIN1,1); 
digitalWrite(BIN2,0);
analogWrite(pwmA,255);
digitalWrite(AIN1,0); 
digitalWrite(AIN2,1);
} 
////////DETENER//////////////////
void detener(void) 
{analogWrite(pwmB,0);
analogWrite(pwmA,0);
} 
////////BUSCAR//////////////////
void buscar(void) 
{analogWrite(pwmB,100);
digitalWrite(BIN1,1); 
digitalWrite(BIN2,0);
analogWrite(pwmA,100);
digitalWrite(AIN1,0); 
digitalWrite(AIN2,1);
} 
