

#include <avr/io.h>
#include <avr/interrupt.h>	// Encabezado para trabajar con las interrupciones
#include <util/delay.h>		// Funciones de tiempo (delay_ms) (delay_us)

	
//	Primeramente delcarar los pines de entrada y de salida
//	Crear macros para indicarle varias instrucciones al microcontrolador
//	Configurar Interrupciones externas (PIN CHANGE) 
//	Medir los tiempos en alto y/o bajo de la señal entregada por el sensor. (EN IMAGENES)
//	Colocar un prescalador de 64 en el timer para poder contabilizar los (400uS = 0.4ms) con 50 escalones cada escalon fue de 8uS.
//	Categorizamos cad auno de los comandos o señales que nos llegan de parte del sensor
//	Cuantificar las señales recibidas.
//	Si cuantificamos un valor de 11, estamos rebibiendo la trama de RESET	
//	Si cuantificamos un valor de 15, estamos recibiendo la trama de READY (RDY)
//	Si cuantificamos un valor de 13. estamos recibiendo la trama de GO 

int valor = 0;
int dato = 0;
int comando=0;
int desborde=0;

#define RESET_	PORTB |= (1<<4);	PORTB &= ~(1<<3);	PORTB &= ~(1<<1);	PORTB &= ~(1<<0);
#define READY_	PORTB |= (1<<4);	PORTB |= (1<<3);	PORTB &= ~(1<<1);	PORTB |= (1<<0);
#define GO_		PORTB &= ~(1<<4);	PORTB |= (1<<3);	PORTB |= (1<<1);	PORTB &= ~(1<<0);


void external_int(void)
{
	GIMSK |= (1<<5);	// Habilitamos las interrupciones Pinchange
	PCMSK |= (1<<2);	// Habilitamos la interrupción PCINT2
}


void conf_timer0_des(void)
{
	TCNT0 =0;
	TIMSK |= (1<<1);	// Habilitamos la interrupcion de desbordamiento
	TIFR |= (1<<1);		// Limpiamos la bandera de desbordamiento
}


ISR(TIMER0_OVF_vect, ISR_NAKED)
{
	TCNT0 = 0;				//	Reiniciamos el conteo.
	TCCR0B &= ~(1<<1);		//	Detener el timer0
	TCCR0B &= ~(1<<0);
	
	switch(comando)
	{
		case 11: RESET_ break;
		case 15: READY_ break;
		case 13: GO_ break;
		default: break;
	}
	
	comando=0;
	desborde=1;		// Bandera que nos indica que existió un desbordamiento
	
	reti();
}


ISR(PCINT0_vect, ISR_NAKED)
{
	if((PINB & (1<<2))==0)		//Flanco de bajada
	{
		if (desborde==0)
		{
				TCNT0=0;				//Registro de nuestro contador va desde 0-255
				TCCR0B |= (1<<1);		//Encendemos el timer0 con un prescalador de 64 (cada escalon sería de 8uS)
				TCCR0B |= (1<<0);
		}
		else 
		{
			desborde=0;	
		}
	}
	
	else						// Flanco de Subida
	{
		valor = TCNT0;			// contabilizar el tiempo
		TCCR0B &= ~(1<<1);		// Detener el timer0
		TCCR0B &= ~(1<<0);
		dato=1;
	}
	
	reti();	//Regreso de la interrupcion y limpia las banderas
}


int main(void)
{
	
	DDRB |= (1<<0);	//PB0	Pin de RDY del arrancador
	DDRB |= (1<<1);	//PB1	Pin de GO del arrancador
	DDRB &= ~(1<<2);//PB2	PIN DE ENTRADA DE LA SEÑAL DEL SENSOR INFRARROJO
	DDRB |= (1<<3);	//PB3	LED de GO
	DDRB |= (1<<4);	//PB4	LED de RESET	
	
	external_int();		//Llamado de las funciones
	conf_timer0_des();
	RESET_
	
	sei();		// Habilitamos de manera global las interrupciones
	
	
    /* Replace with your application code */
    while (1) 
    {
		
		if (dato==1)
		{
			dato=0;
			// Cada escalor de valor vale 8uS
			if (valor <= 55 && valor > 0){ comando+=1; _delay_us(1); }			// 400uS
			if (valor <= 110 && valor > 55){ comando+=4; _delay_us(1); }		// 800uS
			if (valor <= 165 && valor > 110){ comando+=6; _delay_us(1); }		// 1200uS
		}
		
    }
}


