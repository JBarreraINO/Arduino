#include <QTRSensors.h>

int linea=0;                //  0 para lineas negra, 1 para lineas blancas
int flanco_color = 0;      // aumenta o disminuye el valor del sensado
int en_linea = 500;         //valor al que considerara si el sensor esta en linea o no
int ruido =  500;          //valor al cual el valor del sensor es considerado como ruido

#define NUM_SENSORS             16  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  3  // average 4 analog samples per sensor reading



#define IN_PIN             A4  // pin analógico


//QTRSensorsMux qtra((unsigned char[]) pins, numSensors, numSamplesPerSensor, inPin, (unsigned char[]) muxPins);
/*
        pins = pines de entrada (ORDEN EN EL CUAL ESTARÁN ORGANIZADOS LOS SENSORES)
        numSensors = numero de sensores
        numSamplesPerSensor = numero de muestras por sensor
        inPin = Pin de entrada analogica de multiplexor
        muxPins = Pines de eleccion de canal multiplexor
*/

//{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
//{0,8,1,9,2,10,3,11,4,12,5,13,6,14,7,15} {7,6,5,4}
// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsMux qtra((unsigned char[]) {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, (unsigned char) IN_PIN, (unsigned char[]){A0, A1, A2, A3});
unsigned int sensorValues[NUM_SENSORS];


void setup()
{
  delay(500);


  for (int i = 0; i < 100; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(10);
}


void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, linea,flanco_color, en_linea, ruido );

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  Serial.print(" ");
  
  Serial.print("Posición ");
  Serial.print(position); // comment this line out if you are using raw values
  
 Serial.println(" ");
  
}
