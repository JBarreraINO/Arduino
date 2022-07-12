//Motors 6V 300 RPM
//LiPo Battery 3S 450 Mah
// Opponent Sensors give 1 When see the opponent.

#include <xmotion.h> //Included XMotion Library
int RightSensor = A5; //Right Opponent Sensor Pin
int RightDiagonalSensor = 4; //Right Diagonal Opppnent Sensor Pin
int MiddleSensor = 2; //Middle Oppoent Sensor Pin
int LeftDiagonalSensor = 1; //Left Diagonal Opponent Sensor Pin
int LeftSensor = 0; //Left Opponent Sensor Pin

int LeftLine = A2; //Left Line Sensor Pin
int RightLine = A4; //Right Line Sensor Pin
int Start = 10; //Start Button Pin

int Led1 = 8;

int LastValue = 0;

void setup() {
  xmotion.StopMotors(100); //Stopping motors, in case of pin open output.
  xmotion.ToggleLeds(100); // Blink Delay Function for blinking 2 User Leds
  pinMode(Led1, OUTPUT);
  pinMode(RightSensor, INPUT); // We declare Digital Inputs and outputs.
  pinMode(RightDiagonalSensor, INPUT);
  pinMode(MiddleSensor, INPUT);
  pinMode(LeftDiagonalSensor, INPUT);
  pinMode(LeftSensor, INPUT);
  pinMode(Start, INPUT);
  Serial.begin(9600);
}

void loop() {
  while (digitalRead(Start) == 0) // Button push is waited. When Button is pushed, it gives 1 value.
  { //This if statement
    if (digitalRead(LeftSensor) == 1 || digitalRead(MiddleSensor) == 1 || digitalRead(RightSensor) == 1 || digitalRead(RightDiagonalSensor) == 1 || digitalRead(LeftDiagonalSensor) == 1)
    {
      digitalWrite(Led1, HIGH);
    } else {
      digitalWrite(Led1, LOW);
    }

    xmotion.UserLed2(100); //Blink User Led 2 100millisecond Intervals.
  }
  xmotion.CounterLeds(1000, 5);
  while (1) {
    if (analogRead(LeftLine) < 300 && analogRead(RightLine) > 300 ) //Left Line Sensor Saw the Line
    {
      xmotion.Backward(100, 100); //Backward %100 speed, 100 ms retreat.
      xmotion.Right0(100, 200); //Right Turning %100 speed, 200ms duration.
    } else if (analogRead(LeftLine) > 300 && analogRead(RightLine) < 300 ) //Right Line Sensor Saw the Line
    {
      xmotion.Backward(100, 100); //Backward %100 speed, 100 ms retreat.
      xmotion.Left0(100, 200); //Left Turning %100 speed, 200ms duration.
    } else if (analogRead(LeftLine) < 300 && analogRead(RightLine) < 300 ) //Both Sensor Saw the Line
    {
      xmotion.Backward(100, 200); //Backward %100 speed, 200 ms retreat.
      xmotion.Right0(100, 300); //Left Turning %100 speed, 200ms duration.
    }

    else if (digitalRead(MiddleSensor) == 1 ) //Middle Sensor see the opponent (0 Not Seen, 1 Seen)
    {
      xmotion.Forward(100, 1); // Both Motors Forward %100 Speed, 1 Milliseconds
      LastValue = 0;
    }
    else if (digitalRead(RightSensor) == 1) //Right Sensor see the opponent
    {
      xmotion.Right0(70, 1); // Right Turn %70 Power 1 Milliseconds
      LastValue = 1;
    }
    else if (digitalRead(LeftSensor) == 1) //Left Sensor see the opponent
    {
      xmotion.Left0(70, 1); // Left Turn %70 Power 1 Milliseconds
      LastValue = 2;
    }
    else if (digitalRead(LeftDiagonalSensor) == 1) //Left Diagonal Sensor see the opponent
    {
      xmotion.ArcTurn(20, 70, 1); // Left Motor %20 Speed, Right %70 Speed 1 ms.
      LastValue = 2;
    }
    else if (digitalRead(RightDiagonalSensor) == 1) //Right Diagonal Sensor see the opponent
    {
      xmotion.ArcTurn(70, 20, 1); // Left Motor %70 Speed, Right %20 Speed 1 ms.
      LastValue = 1;
    } else if (LastValue == 0) { //Middle Sensor Saw the opponent
      xmotion.Forward(20, 1);
    } else if (LastValue == 1) { //Right or Right Diagonal Sensor saw the opponent
      xmotion.Right0(30, 1);
    } else if (LastValue == 2) { //Left or Left Diagonal Sensor saw the opponent.
      xmotion.Left0(30, 1);
    }
  }
}

