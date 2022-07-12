// Opponent Sensors give 0 when see the obstacle.
#include <xmotion.h> 
void setup() {
//  Serial.begin(9600);
}

void loop() {

     Serial.println(xmotion.VoltageIn()); 
     xmotion.LipoCutOff(2);
     delay(300); 
}
