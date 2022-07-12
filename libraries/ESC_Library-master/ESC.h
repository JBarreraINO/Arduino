/* 
* ESC.h
*
* Created: 6/01/2017 10:17:29 p. m.
* Author: Michael Vargas
*/


#ifndef __ESC_H__
#define __ESC_H__

class ESC
{
//functions
public:
	ESC(char pin); //Constructor
	void init(void);
	static inline void handle_interrupt() __attribute__((__always_inline__));
	void setSpeed(unsigned int highTimeMicroseconds);
	~ESC();
private:
	//Creación de variables estaticas
	static volatile unsigned int ESCTime; 
	static volatile bool ESCHigh;
	static volatile unsigned int ESC_HighTime;
	static unsigned char bitMask;
	static volatile unsigned char *pin_register;
	ESC( const ESC &c );
	ESC& operator=( const ESC &c );

}; //ESC

#endif //__ESC_H__
