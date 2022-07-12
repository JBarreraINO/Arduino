#include <QTRSensors.h>



#define NUM_SENSORS             16  // numero de sensores usados
#define NUM_SAMPLES_PER_SENSOR  3  // numero de muestras
#define IN_PIN             A11  // PIN de entrada del multiplexor


//QTRSensorsMux qtra((unsigned char[]) pins, numSensors, numSamplesPerSensor, inPin, (unsigned char[]) muxPins);
/*
        pins = ORDEN EN EL CUAL ESTARÁN ORGANIZADOS LOS SENSORES EN ENTRADAS DEL MULTIPLEXOR, por lo general : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
        numSensors = numero de sensores
        numSamplesPerSensor = numero de muestras por sensor
        inPin = Pin de entrada analogica de multiplexor
        muxPins = Pines digitales para eleccion de canal multiplexor {S0, S1, S2, S3}
*/

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsMux qtra((unsigned char[]) {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, (unsigned char) IN_PIN, (unsigned char[]){A0, A1, 10,11} );
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
  delay(1000);
}


void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned long tInicial = micros ();
  unsigned int position = qtra.readLine(sensorValues);
  unsigned long tFinal = micros () - tInicial;
  Serial.print ("Tiempo: ");
  Serial.println (tFinal);
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.println("");
  Serial.println("Posición ");
  Serial.println(position); // comment this line out if you are using raw values
}
