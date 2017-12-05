// 
// 
// 

#include "Bom.h"

Bom::Bom()
{
}



void Bom::setLocatieBom(Location locatie)
{
	this->locatieBom = locatie;
}

void Bom::bomProces()
{
	this->tekenBom();
	this->cooldownBom = 0;
	//this->bomStatus = 1;
	
}

void Bom::ontploffing()
{
	Serial.println("BOOOOOOEEMMMMM");
}

void Bom::tekenBom()
{
	Serial.println("bom is gedropt");
}
