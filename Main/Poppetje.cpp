// 
// 
// 

#include "Poppetje.h"

void Poppetje::tekenOntploffing(int xLocatie, int yLocatie)
{

	Serial.println(xLocatie);
	Serial.println(yLocatie);
	int x = (xLocatie * 20) - 20;
	int y = (yLocatie * 20) - 20;
	lcd.fillRect(x, y, 20, 20, RGB(10, 10, 10));
	lcd.drawRect(x, y, 20, 20, 0);



	Serial.println("BOOOOOOEEMMMMM");

}

Poppetje::Poppetje()
{

}







//het afdrukken van de poppetje
void Poppetje::drawPoppetje(int locationX, int locationY)
{
	/*
	this->lcd.fillRect(x, y,20,20,1);
	*/

	int x = (locationX * 20) - 15;
	int y = (locationY * 20) - 12;

	this->lcd.fillRect(x, y, 10, 7, RGB(204, 0, 0));
	this->lcd.drawRect(x, y, 10, 7, 0);
	this->lcd.fillRect(x + 1, y - 6, 8, 1, 0);
	this->lcd.fillRect(x + 3, y - 7, 4, 1, RGB(204, 0, 0));

	this->lcd.fillRect(x - 1, y - 5, 12, 8, RGB(255, 255, 255));
	this->lcd.drawRect(x - 1, y - 5, 12, 8, 0);

	this->lcd.fillRect(x + 1, y - 3, 8, 4, RGB(255, 204, 102));
	this->lcd.fillRect(x + 6, y - 2, 2, 3, 0);
	this->lcd.fillRect(x + 2, y - 2, 2, 3, 0);
	this->lcd.fillRect(x + 3, y + 4, 4, 2, RGB(0, 0, 204));

	this->lcd.fillRect(x, y + 7, 4, 3, RGB(255, 255, 255));
	this->lcd.drawRect(x, y + 7, 4, 3, 0);

	this->lcd.fillRect(x + 6, y + 7, 4, 3, RGB(255, 255, 255));
	this->lcd.drawRect(x + 6, y + 7, 4, 3, 0);

	this->lcd.fillRect(x + 6, y + 10, 6, 2, RGB(204, 0, 0));
	this->lcd.drawRect(x + 6, y + 10, 6, 2, 0);

	this->lcd.fillRect(x - 2, y + 10, 6, 2, RGB(204, 0, 0));
	this->lcd.drawRect(x - 2, y + 10, 6, 2, 0);
	
}

