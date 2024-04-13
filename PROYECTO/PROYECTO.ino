/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/
#define SENSOR_PROXIMITY_A_PIN   DDD4 // Sensor de proximidad A
#define SENSOR_PROXIMITY_B_PIN   DDD7 // Sensor de proximidad B
// the setup routine runs once when you press reset:
int proximity_A_count = 0;
int proximity_B_count = 0;
int state_A_count = 0;
int contador            = 0;   // contador para el numero de veces presinados
int estado_pulsador_asc = 0;         // estado actual del pulsador
int lastButtonState_asc = 1;     // estado anterior del pulsador

//VARIABLES PARA EL CONTADOR DESCENDIENTE
// estas variables si puede ser cambiado

int estado_pulsador_des = 0;         // estado actual del pulsador
int lastButtonState_des = 1;     // estado anterior del pulsador
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
      DDRD &= ~(1 << SENSOR_PROXIMITY_A_PIN);
      DDRD &= ~(1 << SENSOR_PROXIMITY_B_PIN);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  /*

             estado_pulsador_asc= (PIND & (1 << SENSOR_PROXIMITY_A_PIN));
              Serial.println(estado_pulsador_asc);
            if (estado_pulsador_asc !=  lastButtonState_asc )
               {
                Serial.println("entre a count");
             if (estado_pulsador_asc == (PIND & (1 << SENSOR_PROXIMITY_A_PIN))) {
                proximity_A_count++;
                
                 Serial.println("+");
                 Serial.print("numero de veces presionado");
                 Serial.println(proximity_A_count);
            }
            }
             lastButtonState_asc  = estado_pulsador_asc;

*/

             
      if ((PIND & (1 << SENSOR_PROXIMITY_A_PIN))) {

       //PORTB |= (1 << LED_PIN); 
       lastButtonState_asc = 1;
       Serial.println("+"); 
    
      }
    
      if (!(PIND & (1 << SENSOR_PROXIMITY_A_PIN)))
      {
        //PORTB &= ~(1<< LED_PIN);
        estado_pulsador_asc = 1; 
      
      }

if(( lastButtonState_asc==1 && estado_pulsador_asc== 1  )) 
    {
         proximity_A_count++;

         lastButtonState_asc = 0; 
         estado_pulsador_asc = 0; 
    }


       
                  Serial.print("ESTADO 1:");
                 Serial.print(estado_pulsador_asc);
                 Serial.print("ESTADO 2:");
                 Serial.print(lastButtonState_asc);
                 Serial.print("numero de veces presionado");
                 Serial.println(proximity_A_count);   
  delay(1);  // delay in between reads for stability
}
