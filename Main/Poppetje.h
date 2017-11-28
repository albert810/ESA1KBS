// Poppetje.h

#ifndef _POPPETJE_h
#define _POPPETJE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <MI0283QT9.h>

class Poppetje {

public:
	Poppetje();
	void setCurrentXLocation(int x);
	void setCurrentYLocation(int y);
	//void setLCD(MI0283QT9 lcd );
	int currentXLocation;
	int currentYlocation;
	void drawPoppetje(int locationX, int locationY);
	void dropBomb();
	void removeBomb();
	MI0283QT9 lcd;
private:
protected:



};

#endif

