/*El siguiente código permite obtener la lectura del sensor MLX90614 cada un 1 segundo en el 
monitor serie de Arduino*/ 
/****************************************
*Definir librerías, instancias y constantes
*del sensor MLX90614
****************************************/
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); //Se declara una variable u objeto para el sensor  
void setup()
{
Serial.begin(115200); //Se inicia el monitor serie a 115200 baudios
Serial.println("Iniciando test del MLX90614");  
mlx.begin(); //Se inicia el sensor
}
void loop()
{
//Se imprimen los datos de sensor
  Serial.print("Temperatura Ambiente= "); 
Serial.print(mlx.readAmbientTempC()); Serial.println(" °C");
Serial.print("Temperatura del Objeto= "); 
Serial.print(mlx.readObjectTempC()); Serial.println(" °C"); 
  //Serial.print("Temperatura Ambiente = "); 
  //Serial.print(mlx.readAmbientTempF()); Serial.println(" °F"); 
  //Serial.print("Temperatura del Objeto = ");  
  //Serial.print(mlx.readObjectTempF()); Serial.println(" °F"); 
Serial.println();
  delay(1000);
}
