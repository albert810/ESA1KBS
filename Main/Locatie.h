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


	Location();
	int vanLocationNummerNaarX(int locatienummer);
	int vanLocationNummerNaarY(int locatienummer);


	boolean nietBegaanBareLocatie;
	boolean onverwoestbareLocatie;

	
private:
	

protected:


};

#endif

