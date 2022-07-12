#include <Servo.h>   
       


Servo ESC1;

int pos = 0; //Sets position variable

void arm(){

setSpeed(0); //Sets speed variable delay(1000);

}

void setSpeed(int speed){

int angle = map(speed, 0, 100, 0, 180); //Sets servo positions to different speeds ESC1.write(angle);

}

void setup() {

ESC1.attach(10); //Adds ESC to certain pin. arm();

}

void loop() {

int speed; //Implements speed variable

for(speed = 0; speed <= 70; speed += 5) { //Cycles speed up to 70% power for 1 second

setSpeed(speed); //Creates variable for speed to be used in in for loop

delay(1000);

}

delay(4000); //Stays on for 4 seconds

for(speed = 70; speed > 0; speed -= 5) { // Cycles speed down to 0% power for 1 second

setSpeed(speed); delay(1000);

}

setSpeed(0); //Sets speed variable to zero no matter what

delay(1000); //Turns off for 1 second

}
