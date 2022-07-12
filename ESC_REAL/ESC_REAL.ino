#include<Servo.h>

Servo ESC;
int vel = 0;
void setup() {
  // put your setup code here, to run once:
  ESC.attach(10);
  ESC.writeMicroseconds(0);
  delay(2000);
  ESC.writeMicroseconds(2000);
  delay(2000);
  ESC.writeMicroseconds(0);
  delay(2000);
}

void loop() {
turbina(1200);
delay(2000);
}

void turbina(int vel)
{
  if (vel != 0)
  {
    ESC.writeMicroseconds(vel); //Generar un pulso con el numero recibido
  }

}
