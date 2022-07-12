#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"
 
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
 
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
 
void setup() 
{
 
Serial.begin(9600);
 
if (! rtc.begin()) {
Serial.println("Couldn't find RTC");
while (1);
}
 
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
{ 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
}
 
rtc.adjust(DateTime(__DATE__, __TIME__));
 
 display.display();
 delay(2);
 display.clearDisplay();
 
 
display.clearDisplay();
display.setTextColor(BLUE);
//display.startscrollright(0x00, 0x0F);
display.setTextSize(2);
display.setCursor(0,5);
display.print("  Clock ");
display.display();
delay(3000);
}
 
void loop()
{
DateTime now = rtc.now();
 
display.clearDisplay();
display.setTextSize(2);
display.setCursor(75,0);
display.println(now.second(), DEC);
 
display.setTextSize(2);
display.setCursor(25,0);
display.println(":");
 
display.setTextSize(2);
display.setCursor(65,0);
display.println(":");
 
display.setTextSize(2);
display.setCursor(40,0);
display.println(now.minute(), DEC);
 
display.setTextSize(2);
display.setCursor(0,0);
display.println(now.hour(), DEC);
 
display.setTextSize(2);
display.setCursor(0,20);
display.println(now.day(), DEC);
 
display.setTextSize(2);
display.setCursor(25,20);
display.println("-");
 
display.setTextSize(2);
display.setCursor(40,20);
display.println(now.month(), DEC);
 
display.setTextSize(2);
display.setCursor(55,20);
display.println("-");
 
display.setTextSize(2);
display.setCursor(70,20);
display.println(now.year(), DEC);
 
display.setTextSize(2);
display.setCursor(0,40);
display.print(daysOfTheWeek[now.dayOfTheWeek()]);
 
display.display(); 
}
