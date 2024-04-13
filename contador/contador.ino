
// no cambiar las el const int
const int  pulsador_asc = 7;    // pin 2 como entrada para el contador de pulsos 
                                // ascendentes
const int  pulsador_des = 4;    // pin 3 como entrada para el contador de pulsos
                                // descendentes
                                
const int led_rojo = 9;          // Pin 13  como salida 
const int led_verde = 13;          // Pin 13  como salida 
  
  
//VARIABLES PARA EL CONTADOR ASCENDIENTE
// estas variables si puede ser cambiado
int contador            = 0;   // contador para el numero de veces presinados
int estado_pulsador_asc = 0;         // estado actual del pulsador
int lastButtonState_asc = 1;     // estado anterior del pulsador

//VARIABLES PARA EL CONTADOR DESCENDIENTE
// estas variables si puede ser cambiado

int estado_pulsador_des = 0;         // estado actual del pulsador
int lastButtonState_des = 1;     // estado anterior del pulsador

void setup() {
  Serial.begin(9600);
 
  pinMode(pulsador_asc, INPUT_PULLUP); //Resistencia de pullup interna
  pinMode(pulsador_des, INPUT_PULLUP); //Resistencia de pullup interna
  pinMode(led_rojo, OUTPUT);
  pinMode (led_verde,OUTPUT);
}  


void loop() {
//  almacenamos la lectura de la entrada de pin 2
  estado_pulsador_asc = digitalRead(pulsador_asc);
  estado_pulsador_des = digitalRead(pulsador_des);

  // comparar el estado del botón a su estado anterior
  if (estado_pulsador_asc != lastButtonState_asc) {
    // si el estado fue cambiado, incremente el conteo
    if (estado_pulsador_asc == HIGH) {
      // si el estado actual es alto, entonces 
      // que pase de off a on:
      contador++;
      Serial.println("+");
      Serial.print("numero de veces presionado");
      Serial.println(contador);
      delay(100);
    } 
  }
 lastButtonState_asc  = estado_pulsador_asc;
   // comparar el estado del botón a su estado anterior
  if (estado_pulsador_des != lastButtonState_des ) {
    // si el estado fue cambiado, decrementa el conteo
    if (estado_pulsador_des == HIGH) {
      // si el estado actual es alto, entonces 
      // que pase de off a on:
      contador--;
      Serial.println("-");
      Serial.print("numero de veces presionado");
      Serial.println(contador);
      delay(100);
    } 
  }
  //guarda el último estado actual como el ultimo estado
  //para el proximo bucle
  lastButtonState_des  = estado_pulsador_des;

  
  if (contador ==2) {
    digitalWrite(led_rojo, HIGH);
    digitalWrite(led_verde,false);   
  } else 
  if (contador >2)
  {contador ==0;
   digitalWrite(led_rojo, LOW);
   digitalWrite(led_verde,true);
  }
  
}
