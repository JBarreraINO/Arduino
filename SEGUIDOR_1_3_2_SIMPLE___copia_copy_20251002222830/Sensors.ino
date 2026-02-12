

//  sensors private constants
#define MUX_SWITCH_MASK 0xF
#define ADC_ADMUX_CONFIG_MASK 0xE0
#define ADC_CHANNEL_MASK 0xF
#define ADC_PRESCALER_ADPS_MASK 0x7
#define MAX_ADC_VALUE 255

//  calibration parameters
#define CALIBRATION_NOISE_DIVISOR 8
#define CALIBRATION_AVG_SAMPLES 8
#define CALIBRATION_COLLECTOR_SAMPLES 10

#define s0      A0
#define s1      A1
#define s2      A2
#define OM      A3

void sensorsInit() {

}

void readRawSensors() {
  //  sensor reading loop
 for (int i = 0; i < 8; i++) {
    digitalWrite(s0, i & 0x01);
    digitalWrite(s1, i & 0x02);
    digitalWrite(s2, i & 0x04);

    sensorValues[i] = analogRead(OM);  // almacenar valor en el arreglo

 }
  //  sensor values invert method
  if (INVERT_SENSOR_READS) {
    for (byte i = 0; i < TOTAL_SENSORS; i++) {
      sensorValues[i] = MAX_ADC_VALUE - sensorValues[i];
    }
  }
}

void readSampledSensors() {
  int sumSensorValues[TOTAL_SENSORS];  //  temporal sum of each sensor samples

  //  set sum values to zero
  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    sumSensorValues[i] = 0;
  }

  for (byte j = 0; j < CALIBRATION_AVG_SAMPLES; j++) {
    //  update raw sensor values
    readRawSensors();

    //  adds readings to sum of each sensor
    for (byte i = 0; i < TOTAL_SENSORS; i++) {
      sumSensorValues[i] += sensorValues[i];
    }
  }

  //  update sensor values with sum average
  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    sensorValues[i] = (sumSensorValues[i] + (CALIBRATION_AVG_SAMPLES >> 1)) / CALIBRATION_AVG_SAMPLES;
  }
}

void updateMaxMinSensorValues() {
  int highestSample[TOTAL_SENSORS];  //  temporal highest collector sample for each sensor
  int lowestSample[TOTAL_SENSORS];   //  temporal lowest collector sample for each sensor

  //  samples recollector
  for (byte j = 0; j < CALIBRATION_COLLECTOR_SAMPLES; j++) {
    readSampledSensors();

    for (byte i = 0; i < TOTAL_SENSORS; i++) {
      //  update maximum value collected
      if ((j == 0) || (sensorValues[i] > highestSample[i])) {
        highestSample[i] = sensorValues[i];
      }

      //  update minimum value collected
      if ((j == 0) || (sensorValues[i] < lowestSample[i])) {
        lowestSample[i] = sensorValues[i];
      }
    }
  }

  //  update the min and max values
  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    // update maximum only if the min of all collected readings was still higher than it
    // (we got all collected readings in a row higher than the existing maximum)
    if (lowestSample[i] > maxSensorValues[i]) {
      maxSensorValues[i] = lowestSample[i];
    }

    // update minimum only if the max of all collected readings was still lower than it
    // (we got all collected readings in a row lower than the existing minimum)
    if (highestSample[i] < minSensorValues[i]) {
      minSensorValues[i] = highestSample[i];
    }
  }
}

void resetCalibrationValues() {
  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    maxSensorValues[i] = 0;
    minSensorValues[i] = MAX_ADC_VALUE;
  }
}

void calibrateSensors() {
  setLED_2(1);
  delay(250);
  setLED_2(0);
  delay(250);

  resetCalibrationValues();

  //  end calibration trigger
  while (!readButton_2()) {
    toggleLED_2();
    updateMaxMinSensorValues();
  }
  getSensorThreshold();
  setLED_2(0);
  delay(250);

  if (isConsoleMode) {
    printCalibrationValues();
  }

  confirmAnimation(250, 2);
}

void getSensorThreshold() {
  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    sensorThreshold[i] = (maxSensorValues[i] - minSensorValues[i]) * ((float)(SENSOR_THRESHOLD_PERCENT) / 100) + minSensorValues[i];
  }
}

void readCalibratedSensors() {
  //  get actual raw sensor readings
  readRawSensors();

  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    unsigned int range = maxSensorValues[i] - sensorThreshold[i];

    if (sensorValues[i] > sensorThreshold[i]) {
      if (sensorValues[i] < maxSensorValues[i]) {
        //  scale value to fixed range if raw sensor value is higher than threshold and lower than maximum
        sensorValues[i] = ((sensorValues[i] - sensorThreshold[i]) * 255) / range;
      } else {
        sensorValues[i] = 255;  //  set to 255 if raw sensor value is higher than maximum calibrated value
      }
    } else {
      sensorValues[i] = 0;  //  set to zero if raw sensor value is lower than threshold
    }
  }
}

unsigned int getLinePosition() {
  uint32_t wtd = 0;  //  temporal sum of weighted sensor values
  uint32_t sum = 0;  //  temporal sum of sensor values
  isOnLine = false;  //  set line is not on sensors range at the start of line position calculation

  //  get calibrated sensor read values
  readCalibratedSensors();

  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    //  add to sum if actual sensor value is higher to zero
    if (sensorValues[i]) {
      isOnLine = true;  // updates to true if at least one sensor detects the line
      wtd += (uint32_t)sensorValues[i] * i * 1000;
      sum += sensorValues[i];
    }
  }

  //  if weighted sum is higher to zero return weighted average
  return wtd ? wtd / sum : 0;
}

void printCalibrationValues() {
  Serial.print("MAX:\t");
  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    Serial.print(maxSensorValues[i]);
    Serial.print("\t");
  }
  Serial.println();
  Serial.print("MIN:\t");
  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    Serial.print(minSensorValues[i]);
    Serial.print("\t");
  }
  Serial.println();
  Serial.print("TH:\t");
  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    Serial.print(sensorThreshold[i]);
    Serial.print("\t");
  }
  Serial.println();
}

//  ======================
//  D E B U G   T O O L S
//  ======================

void printSensorValues() {
  for (byte i = 0; i < TOTAL_SENSORS; i++) {
    Serial.print(sensorValues[i]);
    Serial.print("\t");
  }
  Serial.println();
}