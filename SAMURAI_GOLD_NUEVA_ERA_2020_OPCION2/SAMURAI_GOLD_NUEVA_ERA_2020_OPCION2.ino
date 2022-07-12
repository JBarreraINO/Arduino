//*********PARAMTROS A CALIBRAR *************************************************************************************************
#include <Servo.h>
#include <QTRSensors.h>
Servo fan;
int linea = 0;         //  0 para lineas negra, 1 para lineas blancas
int flanco_color = 0;  // aumenta o disminuye el valor del sensado
int en_linea = 200;    //valor al que considerara si el sensor esta en linea o no
int ruido = 50;       //valor al cual el valor del sensor es considerado como ruido

#define NUM_SENSORS 16            // number of sensors used
#define NUM_SAMPLES_PER_SENSOR 2  // average 4 analog samples per sensor reading



#define IN_PIN A4  // pin analógico
QTRSensorsMux qtra((unsigned char[]){
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
                   NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, (unsigned char)IN_PIN, (unsigned char[]){ A0, A1, A2, A3 });
unsigned int sensorValues[NUM_SENSORS];

int velocidad = 90;  // Velocidad crucero de robot max 255
float Kp =2;      // calibracion proporciona 0.7; 2; 1.1
float Kd = 0;        //  calibracion derivativo 9.65
int sensibilidad = 100;
int frente = 158;   // Velocidad a la que ira el motor hacia adelante cuando pierda la linea max 255  198 para sensores cortos
int reversa = 158;  // Velocidad a la que ira el motor hacia atras cuando pierda la linea    max 255  198 para sensores cortos

int led = 13;  // Led default de Arduino

int pini = 9;
int pwmi = 5;
int pind = 6;
int pwmd = 3;

int go = 8;  // Puerto donde se conecta el arrancador ( si el modulo no esta conectado, debe ponerse una resistencia pull-down)
int rdy = 12;
int boton_izq = 4;  // boton izquierdo
//int boton_der = 7; // boton derecho
int lon = 11;
//*******VARIABLES A UTILIZAR****************************************************************************************************


int valor_bd = 0, state_go = 0, state_rdy = 0, allow_off = 0, valor_bi = 0, memory_deg = 0, posicion = 0, MUESTREO = 1, c = 0, espera = 0, modo = LOW, value_x = 0;
int vel = 0;
unsigned long presente = 0;
long antes = 0;
long pausa = 70;
unsigned long pasado = 0;
unsigned long ahora;
float ERROR_POSICION = 0;
float ERROR_ULTIMO=0;
int CX = 0;
int setpoint = 7500;
long int position=0;

void setup() {
  Serial.begin(115200);
  fan.attach(10);
  fan.writeMicroseconds(1000);
  pinMode(led, OUTPUT);
  pinMode(lon, OUTPUT);

  pinMode(go, INPUT);
  pinMode(boton_izq, INPUT);
  //  pinMode ( boton_der, INPUT);
  pinMode(rdy, INPUT);

  //TCCR2B = TCCR2B & B11111000 | B00000001;
  //set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz

  TCCR2B = TCCR2B & B11111000 | B00000010;
  //set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

  //TCCR2B = TCCR2B & B11111000 | B00000011;
  //set timer 2 divisor to    32 for PWM frequency of   980.39 Hz

  //TCCR2B = TCCR2B & B11111000 | B00000100;
  //set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)

  //TCCR2B = TCCR2B & B11111000 | B00000101;
  //set timer 2 divisor to   128 for PWM frequency of   245.10 Hz

  //TCCR2B = TCCR2B & B11111000 | B00000110;
  //set timer 2 divisor to   256 for PWM frequency of   122.55 Hz

  //TCCR2B = TCCR2B & B11111000 | B00000111;
  //set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz
  pinMode(pini, OUTPUT);
  pinMode(pwmi, OUTPUT);
  pinMode(pind, OUTPUT);
  pinMode(pwmd, OUTPUT);
  digitalWrite(lon, HIGH);

rutina1:

  delay(1000);
  digitalWrite(led, HIGH);

rutina2:
  lectura();


  if (valor_bi == LOW) {
    value_x = 1;
  }
  if (valor_bi == HIGH && value_x == 1) {
    delay(50);
    goto rutina3;
  }
  goto rutina2;


  //****************************************************************************************************************************************************************************


rutina3:  // Calibracion de sensores

  while (espera < 4000) {
    lectura();
    if (valor_bi == LOW) {
      espera = 5000;
    }



    for (int i = 0; i < 50; i++)  // make the calibration take about 10 seconds
    {

      qtra.calibrate();
    }

    // print the calibration minimum values measured when emitters were on

    for (int i = 0; i < NUM_SENSORS; i++) {
      Serial.print(qtra.calibratedMinimumOn[i]);
      Serial.print(' ');
    }
    Serial.println();

    // print the calibration maximum values measured when emitters were on
    for (int i = 0; i < NUM_SENSORS; i++) {
      Serial.print(qtra.calibratedMaximumOn[i]);
      Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    
    break;
  }
  // Termina calibracion de sensores

  analogWrite(pwmd, 0);
  analogWrite(pwmi, 0);
  digitalWrite(led, LOW);
  delay(500);



rutina4:

  digitalWrite(led, HIGH);
  lectura();
  if (state_go == HIGH) {
    allow_off = 1;
    goto PD;
  }
  if (valor_bi == LOW) {
    c = 1;
  }
  if (valor_bi == HIGH && c == 1) {
    delay(50);
    digitalWrite(led, LOW);
    //  fan.write(1500);
    // delay(1500);
    goto PD;
  }
  goto rutina4;



off:
  lectura();
  if (state_go == HIGH) {
    goto PD;
  }
  analogWrite(pwmi, 0);
  analogWrite(pwmd, 0);
  fan.write(1000);
  goto off;





  //*****************************************************************> PROGRAMA PRINCIPAL DE PD <**************************************************************************************

PD:

  if (state_go == 0 && allow_off == 1) {
    goto off;
  }

  ahora = millis();
  int ACTUAL = ahora - pasado;
  if (ACTUAL >= MUESTREO) {

    lectura();
      ERROR_POSICION = sensorValues[0] * (-1) + sensorValues[1] * (-1) + sensorValues[2] * (-1) + sensorValues[3] * (-.8) + sensorValues[4] * (-.6) + sensorValues[5] * (-.4) + sensorValues[6] * (-.2) +sensorValues[7] * (-.1) + sensorValues[8] * (.1) + sensorValues[9] * (.2) + sensorValues[10] * (.4) + sensorValues[11] * (.6) + sensorValues[12] * (.8) + sensorValues[13] * (1) + sensorValues[14] * (1) + sensorValues[15] * (1);

    Serial.print("error posicion:");
    Serial.print(ERROR_POSICION);
    Serial.print('\t');
    float ERROR_D = (ERROR_POSICION - ERROR_ULTIMO);
    float P = Kp * ERROR_POSICION;
    float D = Kd * ERROR_D;

    CX = P + D;

    pasado = ahora;

    ERROR_ULTIMO = ERROR_POSICION;

    if (CX >= 255) {
      CX = 255;
    }
    if (CX <= -255) {
      CX = -255;
    }




    int pwm1 = velocidad + (CX);
    int pwm2 = velocidad - (CX);

    if (pwm1 >= 255) {
      pwm1 = 255;
    }
    if (pwm2 >= 255) {
      pwm2 = 255;
    }


    if (sensorValues[2] > sensibilidad) {
      posicion = 0;
    }
    if (sensorValues[0] > sensibilidad && sensorValues[7] < sensibilidad && sensorValues[8] < sensibilidad) {
      posicion = 1;
    }

    if (sensorValues[13] > sensibilidad) {
      posicion = 0;
    }
    if (sensorValues[15] > sensibilidad && sensorValues[7] < sensibilidad && sensorValues[8] < sensibilidad) {

      posicion = 16;
    }
    Serial.print("posicion");
    Serial.print(posicion);
    Serial.print('\t');

    float r1 = abs(pwm1);
    float r2 = abs(pwm2);

    if (r1 >= 255) {
      r1 = 255;
    }
    if (r2 >= 255) {
      r2 = 255;
    }
    //Si te sales
    if (posicion == 16) {
      analogWrite(pwmd, reversa);
      digitalWrite(pind, HIGH);
      analogWrite(pwmi, frente);
      digitalWrite(pini, HIGH);
      fan.write(1900);
    }

    if (posicion == 1) {
      analogWrite(pwmd, frente);
      digitalWrite(pind, LOW);
      analogWrite(pwmi, reversa);
      digitalWrite(pini, LOW);
      fan.write(1900);
    }
    //control de motores
    if (posicion != 16 && posicion != 1) {
      if (pwm1 < 0) {
        analogWrite(pwmd, r1);
        digitalWrite(pind, LOW);  //Derecho atras
        digitalWrite(13, HIGH);
        fan.write(1500);
      }
      if (pwm2 < 0) {
        analogWrite(pwmi, r2);
        digitalWrite(pini, HIGH);
        fan.write(1700);
      }

      if (pwm1 == 0) {
        analogWrite(pwmd, 0);
        digitalWrite(pind, LOW);
        digitalWrite(13, LOW);
        fan.write(1400);
      }
      if (pwm2 == 0) {
        analogWrite(pwmi, 0);
        digitalWrite(pini, LOW);
        digitalWrite(13, LOW);
        fan.write(1400);
      }

      if (pwm1 > 0) {
        analogWrite(pwmd, pwm1);
        digitalWrite(pind, HIGH);
        fan.write(1700);
      }
      if (pwm2 > 0) {
        analogWrite(pwmi, pwm2);
        digitalWrite(pini, LOW);
        fan.write(1700);
      }
    }
  }
  goto PD;
}




void loop() {}

void lectura() {

  valor_bi = digitalRead(boton_izq);
  //valor_bd = digitalRead ( boton_der);
  state_go = digitalRead(go);
  state_rdy = digitalRead(rdy);

  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  //position = qtra.read(sensorValues, QTR_EMITTERS_ON, linea, flanco_color, en_linea, ruido);
 qtra.readCalibrated(sensorValues,QTR_EMITTERS_ON,0);
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }


}
