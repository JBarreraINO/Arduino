#include <xmotion.h>

void setup() {
xmotion.ToggleLeds(100); //Make blink Both Leds 100 millisecs
}

void loop() {  
  xmotion.Forward(100,100); // %100 Speed, both motor forward 100mS.
  xmotion.StopMotors(100);  // 100ms Stop Both Motors
  xmotion.Backward(70,250); // %70 Speed, both motor backward 250mS.
  xmotion.Right0(51,1000);  // %51 Speed, 1 second Right 0 Turn. (Left Motor Forward, Right Backward)
  xmotion.Left0(20,3500);   // %20 Speed, 3.5 second Left 0 Turn. (Right Motor Forward, Left Backward)
  xmotion.ArcTurn(20,60,250); // 250 millisecond %20 Speed Left, %60Speed Right Motor
  xmotion.MotorControl(-150,190); //Timeless -150/255 Left Motor Backward Speed, 190/255 Right Motor Speed
  delay(100); // 100ms Delay
}
