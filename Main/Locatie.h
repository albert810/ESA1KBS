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
	void setLocationX(uint8_t x);
	void setLocationY(uint8_t y);
	boolean nietBegaanBareLocatie;
	boolean onverwoestbareLocatie;

	
private:
	

protected:


};

#endif

