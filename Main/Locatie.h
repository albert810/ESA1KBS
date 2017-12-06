// Locatie.h

#ifndef _LOCATIE_h
#define _LOCATIE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
class Location {
public:

	uint8_t XLocation;
	uint8_t YLocation;
	Location();
	void setLocationX(int x);
	void setLocationY(int y);
	boolean nietBegaanBareLocatie;

	
private:
	

protected:


};

#endif

