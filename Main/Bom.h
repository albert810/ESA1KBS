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
	uint8_t xLocatie;
	uint8_t yLocatie;
	//bepaalde statussen van de bom
	boolean schadeOpruimen;;//wanneer de bom opgeruimd moet worden word deze true
	boolean bomStatus;//wanneer de bom af is gegaan wordt deze true
	
	//Het id van de bom,  voor het bijhouden van welke bom er ook af moet gaan
	int bomID=0;
	
	//timers voor de bom
	int cooldownBom;
	int aftellenTotExplosieBom;
	int	opruimenBomTijd;




};

#endif

