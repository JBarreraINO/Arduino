/* 
* ESC.cpp
*
* Created: 6/01/2017 10:17:28 p. m.
* Author: Michael Vargas
*/


#include "ESC.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <Arduino.h>

#if F_CPU == 20000000
#define MIN_VAL_COPY	2500
#define REFRESH_50HZ	50000
#elif	F_CPU	==	16000000
#define MIN_VAL_COPY	2000
#define REFRESH_50HZ	40000
#elif	F_CPU	==	8000000
#define MIN_VAL_COPY	1000
#define REFRESH_50HZ	20000
#endif
#define MAX_VAL_US	2000
#define MIN_VAL_US	1000

//Inicialización de variables estaticas
unsigned char ESC::bitMask = 0;
volatile unsigned char *ESC::pin_register;
volatile unsigned int ESC::ESC_HighTime = MIN_VAL_COPY;
volatile unsigned int ESC::ESCTime= 0;
volatile bool ESC::ESCHigh =false;

inline void ESC::handle_interrupt()
{

  // The time that passed since the last interrupt is OCR1A + 1
  // because the timer value will equal OCR1A before going to 0.
   ESCTime += OCR1A + 1;

  static uint16_t highTimeCopy = MIN_VAL_COPY;
  static uint8_t interruptCount = 0;

  if (ESCHigh)
  {
    if (++interruptCount == 2)
    {
      OCR1A = 255;
    }

    // The ESC pin is currently high.
    // Check to see if is time for a falling edge.
    // Note: We could == instead of >=.
    if (ESCTime >= highTimeCopy)
    {
      // The pin has been high enough, so do a falling edge.
      //digitalWrite(ESC_PIN, LOW);
	 *pin_register &= ~bitMask;
      ESCHigh = false;
      interruptCount = 0;
    }
  }
  else
  {
    // The ESC pin is currently low.

    if (ESCTime >= REFRESH_50HZ)
    {
      // We've hit the end of the period (20 ms),
      // so do a rising edge.
      highTimeCopy = ESC_HighTime;
     //	 digitalWrite(ESC_PIN, HIGH);
     *pin_register |= bitMask;
	  ESCHigh = true;
      ESCTime = 0;
      interruptCount = 0;
      OCR1A = ((highTimeCopy % 256) + 256) / 2 - 1;
    }
  } 
}
// default constructor
ESC::ESC(char pin)
{
	  digitalWrite(pin, LOW);
	  pinMode(pin, OUTPUT);
	 bitMask = digitalPinToBitMask(pin);
     pin_register = portOutputRegister(digitalPinToPort(pin));
} //ESC

void ESC::init(){

	  cli();
	  TCCR1B = 0;
	  TCCR1A = 0; 
	  // Set a 1:8 prescaler.  This gives us 0.5us resolution.
	  TCCR1B = (1 << CS11) | (1 << WGM12);
	  // Put the timer in a good default state.
	  TCNT1 = 0;
	  OCR1A = 255;
	  TIMSK1 |= (1 << OCIE1A);  // Enable timer compare interrupt.
	  sei();   // Enable interrupts.
}
void ESC::setSpeed(unsigned int highTimeMicroseconds)
{
  TIMSK1 &= ~(1 << OCIE1A); // disable timer compare interrupt
#if F_CPU == 20000000
 ESC_HighTime = (highTimeMicroseconds <= MAX_VAL_US && highTimeMicroseconds >= MIN_VAL_US) ? highTimeMicroseconds * 2.5 : MIN_VAL_COPY;
#elif	F_CPU	==	16000000
 ESC_HighTime = (highTimeMicroseconds <= MAX_VAL_US && highTimeMicroseconds >= MIN_VAL_US) ? highTimeMicroseconds * 2 : MIN_VAL_COPY;
#elif	F_CPU	==	8000000
 ESC_HighTime = (highTimeMicroseconds <= MAX_VAL_US && highTimeMicroseconds >= MIN_VAL_US) ? highTimeMicroseconds : MIN_VAL_COPY;
#endif 
 TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
}


ISR(TIMER1_COMPA_vect)
{
  ESC::handle_interrupt();
}
// default destructor
ESC::~ESC()
{
} //~ESC
