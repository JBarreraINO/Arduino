
// Declaracion de variables globales
float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
int pinLM35 = A0; // Variable del pin de entrada del sensor (A0)
int brightness = 125;    // how bright the LED is
int led = 9;           // the PWM pin the LED is attached to 
 
void setup() {
  // Configuramos el puerto serial a 9600 bps
    Serial.begin(9600);//el baud rate
    pinMode(led, OUTPUT);
 
}
 
void loop() {

  int ADC_SHARP=ADC0_promedio(5);// hacer una adecuacion d la señal
  analogWrite(led, brightness);
  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  tempC = ADC_SHARP; 
   
  // Calculamos la temperatura con la fórmula

  tempC=(4.7 * tempC * 100.0)/1024.0; //
   Serial.println(tempC);
   delay(200);

 
  
 
  // Envia el dato al puerto serial

  // Salto de línea
  
  
  // Esperamos un tiempo para repetir el loop
 
}

int ADC0_promedio(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  return(suma/n);
}
