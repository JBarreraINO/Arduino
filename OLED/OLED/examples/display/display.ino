/*  OLED          arduino
     D0-----------10
     D1-----------9
     RST----------13
     DC-----------11
     VCC----------5V
     GND----------GND*/
#include <OLED.h>
OLED OLED;


void setup()
 {
   OLED.LEDPIN_Init(10,9,13,11);
   OLED.LED_Init();
 }
 
 
 void loop()
 {
    OLED.LED_PrintBMP(0,0,128,7,(unsigned char *)logo);
    delay(300);
    OLED.LED_P6x8Str(0,0,"Library has written");
    OLED.LED_P6x8Char(0,2,'u');
    //OLED.LED_P8x16Str(0,5,"u");
    while(1);
 }
