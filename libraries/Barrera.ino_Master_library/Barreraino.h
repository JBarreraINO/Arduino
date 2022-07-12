#ifndef Barreraino
#define Barreraino
#include <Arduino.h>
/*
	LIBRERIA Barrera.ino V0.1
	Desarrollado por Juan carlos Barrera para controlar la placa UnoBarrera.ino  de forma simple
	y didactica, contiene una serie de funciones que facilitan el funcionamiento de los circuitos
	la librería va conbinada con los ejemplos de Arduino.
	FUNCIONES
	#############
		* Control del Dirver de Motores.
		* Lectura del botón.
		
	#############

*/
class barrera{
	public: int activar=0;
	//
	
	barrera();
	    void unoBarrera();
		short activarele();
		short desactivarele();
	//Permite concer el estado de las variables mas importantes linea, bateria etc...
	short Boton1();
	short Boton2();

	
	
	private:
};
#endif