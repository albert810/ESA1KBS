// Bom.h

#ifndef _BOM_h
#define _BOM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Locatie.h"

class Bom {

public:
	Bom();
	Location locatieBom;
	void setLocatieBom(Location locatie);
	void bomProces();
	void ontploffing();
	void tekenBom();
	boolean bomStatus;
	int aftellenTotExplosieBom;
	int cooldownBom;
	int bomID=0;







};

#endif

