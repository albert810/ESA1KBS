// Poppetje.h

#ifndef _POPPETJE_h
#define _POPPETJE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
class Poppetje {

public:
	Poppetje();
	void setCurrentXLocation(int x);
	void setCurrentYLocation(int y);
	int currentXLocation;
	int currentYlocation;
	void drawPoppetje();
private:
protected:



};

#endif

