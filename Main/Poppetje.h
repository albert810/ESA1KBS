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
	void tekenOntploffing(int xLocatie, int yLocatie);//teken de ontploffing op de plaats waar de poppetje zelf staat
	void drawPoppetje(int locationX, int locationY);//het poppetje tekenen om de speelveld
	uint8_t	xLocatie;
	uint8_t yLocatie;
	Bom bom;
	uint8_t levens = 3;
	uint8_t	snelheidsGrens; //wordt telkens verhoogt in de main loop, wanneer hij een bepaalde waarde heeft mag de poppetje bewegen
	MI0283QT9 lcd;
private:
protected:



};

#endif

