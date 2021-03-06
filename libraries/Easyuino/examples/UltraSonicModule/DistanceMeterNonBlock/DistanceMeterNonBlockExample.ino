/*
DistanceMeterNonBlockExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::DistanceMeterNonBlock;  // Necessary in order to use DistanceMeterNonBlock API

int triggerPin = 7;  // Arduino pin that connects to Ultrasonic Module trigger pin
int echoPin = 2;	 // Arduino pin that connects to Ultrasonic Module echo pin			

DistanceMeterNonBlock distanceMeterNB(triggerPin, echoPin);  // Create the DistanceMeterNonBlock API object

void setup() {
  Serial.begin(9600);
  distanceMeterNB.begin();  // Initialize the DistanceMeterNonBlock API
}

/*
- Information: You can do the same calls of the DistanceMeter API
see DistanceMeterExample.ino plus the following one
*/
void loop() {
  /*
  - This call makes the Ultrasonic Module update its distance to the closer object.
  - To get the distance measure you need call getDistanceCentimeters(); or getDistanceInches();
  - The difference to the updateDistance(); method is that the Arduino will NOT WAIT for the Ultrasonic
  module to finish the measurement. So the instructions after this call will execute while the distance is measured.
  - WARNING-1: When using this method the arduino echo pin must support interruptions you can see
  in this link what are pins of your board that support it https://www.arduino.cc/en/Reference/AttachInterrupt
  - WARNING-2: The measurement with this call are more unstable and less accurate due to the mechanism
  used to achieve this non blocking.
  */
  distanceMeterNB.updateDistanceNonBlock();

  /*
  See DistanceMeterExample.ino for the explanation
  */
  float distanceCentimeters = distanceMeterNB.getDistanceCentimeters();
  Serial.println(distanceCentimeters);

  delay(500);
}