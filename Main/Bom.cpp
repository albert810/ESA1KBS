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

/*void Bom::tekenOntploffing(uint8_t xLocatie, uint8_t yLocatie, uint8_t range, MI0283QT9 lcd)
{

	int x = (xLocatie * 20) - 20;
	int y = (yLocatie * 20) - 20;
	
	
		lcd.fillRect(x, y, 20, 20, RGB(50, 50, 50));
		lcd.drawRect(x, y, 20, 20, 0);
	


	Serial.println("BOOOOOOEEMMMMM");
}*/

void Bom::tekenBom()
{
	Serial.println("bom is gedropt");
}
