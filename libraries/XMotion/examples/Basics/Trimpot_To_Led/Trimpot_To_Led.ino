#include <xmotion.h>

void setup() {

}

void loop() {
  xmotion.ToggleLeds(xmotion.Trimpot()); //Blink delay in trimpot analog reading value between 0 - 1023 milliseconds.
}
