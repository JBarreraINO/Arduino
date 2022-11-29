/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1747 3V version
  ----> https://www.adafruit.com/products/1748 5V version

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  
  Wire.begin();
  mlx.begin();  
    lcd.init();
  lcd.backlight();
}

void loop() {
  

      lcd.setCursor(0, 0);
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  lcd.print("t_objeto=") ;
  lcd.setCursor(10, 0);
  lcd.print(mlx.readObjectTempC());
   lcd.setCursor(15, 0);
     lcd.print("C") ;

       lcd.setCursor(0, 2);
  lcd.print("ambiente=") ;
  lcd.setCursor(10, 2);
  lcd.print(mlx.readAmbientTempF());
   lcd.setCursor(15, 2);
     lcd.print("F") ;






  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  delay(500);
}
