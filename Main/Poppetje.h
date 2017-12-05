// Poppetje.h

#ifndef _POPPETJE_h
#define _POPPETJE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <MI0283QT9.h>
#include "Locatie.h"
#include "Bom.h"
class Poppetje {
	
public:
	Poppetje();
	//void setLCD(MI0283QT9 lcd );
	Location currentlocatie;
	void drawPoppetje(int locationX, int locationY);
	MI0283QT9 lcd;
	Bom bom[2];


private:
protected:



};

#endif

