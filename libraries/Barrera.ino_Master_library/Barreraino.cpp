#include "Arduino.h"
#include "Barreraino.h"

barrera::barrera(){

}

//Funciones de configuracion segun la tarjeta
void barrera::unoBarrera(){//Configuracion del unoBarrera
/*
unoBarrera es una  version mejorada del arduino uno 
contiene las siguientes conexiones:
  *Entradas
    -Boton D10
	 -Boton D11
    -Sensor Bateria A11
    - 9 pines digitales (A5,A4,A3,A2,A1,A0,D13,D10,D9), 6 pueden ser Analogos, 3 de PWM
  *Salidas
    -Motor MA(D6-D8)
    -Motor MB(D5-D7)
    -LED D11
  *Comunicacion
    
*/
  //Asignacion de salidas
  //BOTON 2
  pinMode(11,INPUT);
    //BOTON 1
pinMode(10,INPUT);
	//pin relay
//pinMode(2, OUTPUT);
  //Asignacion de pines de salida Motor A
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  //Asignacion de pines de salida Motor B
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

}


short barrera::Boton1(){//Lectura del botón
 
  if(activar==0)
    return !digitalRead(11);
}
short barrera::Boton2(){//Lectura del botón
	
	if(activar==0)
	return !digitalRead(10);
}
/*
short barrera::activarele(){//Lectura del botón
	
	
	digitalWrite(2,LOW);
}

short barrera::desactivarele(){//Lectura del botón
	
	
	digitalWrite(2,HIGH);
}
*/



