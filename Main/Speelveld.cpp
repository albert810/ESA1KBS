#include "Speelveld.h"
// 
// 
// 


Speelveld::Speelveld(int startPositionForPlayer1X, int startPositionForPlayer1Y, int startPositionForPlayer2X, int startPositionForPlayer2Y)
{
	//achtergrond groen maken
	lcdGame.fillScreen(RGB(0, 53, 0));

	//instellen startlocatie speler 1

	this->speler1.xLocatie = startPositionForPlayer1X;
	this->speler1.yLocatie = startPositionForPlayer1Y;

	//instellen startlocatie speler 2

	this->speler2.xLocatie = startPositionForPlayer2X;
	this->speler2.yLocatie = startPositionForPlayer2Y;


}

Speelveld::Speelveld()
{
}

void Speelveld::constructorAlternatief(int startPositionForPlayer1X, int startPositionForPlayer1Y, int startPositionForPlayer2X, int startPositionForPlayer2Y)
{
	//achtergrond groen maken
	lcdGame.fillScreen(RGB(0, 53, 0));
	//instellen startlocatie speler 1
	

	this->speler1.xLocatie = startPositionForPlayer1X;
	this->speler1.yLocatie = startPositionForPlayer1Y;

	//instellen startlocatie speler 2


	this->speler2.xLocatie = startPositionForPlayer2X;
	this->speler2.yLocatie = startPositionForPlayer2Y;


}

void Speelveld::setLCD(MI0283QT9 lcd)
{
	this->lcdGame = lcd;
}

void Speelveld::setNunchuck(ArduinoNunchuk nunchuk)
{
	this->nunchuk = nunchuk;
}

void Speelveld::SetupSpeelveld(MI0283QT9 lcd, ArduinoNunchuk nunchuck, uint8_t level, int locatienummer)
{
	this->setLCD(lcd);
	this->setNunchuck(nunchuck);
	drawBegin(level, locatienummer);
	this->levensTekenen(1);
	this->levensTekenen(2);

}


//het instellen van de game
void Speelveld::drawBegin(uint8_t level, int locatieNummer)
{



// hier worden (16*12) 192 objecten aangemaakt en opgeslagen in een array, deze objecten zijn locaties
	
		
		for (size_t i = 1; i < 175; i++)
		{
			//tijdelijke variabele die de locatie opslaat
			
				int x = (this->locationsOfMap[i].vanLocationNummerNaarX(i) * 20) - 20;
				int y = (this->locationsOfMap[i].vanLocationNummerNaarY(i) * 20) - 20;

		
			//de randen voor de game worden hier getekent.
			this->lcdGame.fillRect(x, (1 * 20) - 20, 20, 20, RGB(50, 50, 50));
			this->lcdGame.drawRect(x, (1 * 20) - 20, 20, 20, 0);
			this->lcdGame.fillRect(x, (12 * 20) - 20, 20, 20, RGB(50, 50, 50));
			this->lcdGame.drawRect(x, (12 * 20) - 20, 20, 20, 0);


			
			//instellen dat je niet door de randen kunt voor de Y
			if (this->locationsOfMap[i].vanLocationNummerNaarY(i) == 1 || this->locationsOfMap[i].vanLocationNummerNaarY(i) == 12 || this->locationsOfMap[i].vanLocationNummerNaarY(i) == 11) {
			this->locationsOfMap[i].nietBegaanBareLocatie = 1;
			this->locationsOfMap[i].onverwoestbareLocatie = 1;
			this->lcdGame.fillRect(x, y, 20, 20, RGB(50, 50, 50));
			this->lcdGame.drawRect(x, y, 20, 20, 0);
			}


			//teken randen voor de X
			
			if (this->locationsOfMap[i].vanLocationNummerNaarX(i) ==1 ){
				this->lcdGame.fillRect(x, y, 20, 20, RGB(50, 50, 50));
				this->lcdGame.drawRect(x, y, 20, 20, 0);
				this->locationsOfMap[i].nietBegaanBareLocatie = 1;
				this->locationsOfMap[i].onverwoestbareLocatie = 1;


			}
			if (this->locationsOfMap[i].vanLocationNummerNaarX(i) == 15) {
				this->lcdGame.fillRect(x, y, 20, 20, RGB(50, 50, 50));
				this->lcdGame.drawRect(x, y, 20, 20, 0);
				this->locationsOfMap[i].nietBegaanBareLocatie = 1;
				this->locationsOfMap[i].onverwoestbareLocatie = 1;


			}
			
		}
		
		this->lcdGame.fillRect((2 * 20) - 20, (11 * 20) - 20, 260, 20, RGB(50, 50, 50));
		this->lcdGame.drawRect((2 * 20) - 20, (11 * 20) - 20, 260, 20, RGB(50, 50, 50));
		this->lcdGame.fillRect((1 * 20) - 20, (12 * 20) - 20, 320, 20, 0);
		this->lcdGame.drawRect((1 * 20) - 20, (12 * 20) - 20, 320, 20, 0);

		this->lcdGame.fillRect((16 * 20) - 20, (1 * 20) - 20, 20, 260, 0);
		this->lcdGame.drawRect((16 * 20) - 20, (1 * 20) - 20, 20, 260, 0);

		this->locatieNummer = locatieNummer;
		this->bomID = 0;
		this->maakOnbegaanbareMuren();
		this->spelersZijnIngesteld = 1;
		maakLevel(level);
}

void Speelveld::verplaatsPoppetje()
{
	nunchuk.update();
	//omhoog
	//wanneer men naar de ongewenste locatie wil wordt hij tegengehouden, door 1 plaats naar voren te kijken en te zien of daar 
	//de boolean staat van of je er wel of niet doorheenmag.
	if (nunchuk.analogY > grensNaarBovenNunchuck) {
		if (this->locationsOfMap[locatieNummer -16].nietBegaanBareLocatie ) {
		}
		else{
			this->locatieNummer = locatieNummer - 16;
			this->speler1.yLocatie--;
			this->vorigelocatieSpeler1 = omhoog;
		}
	}
	//omlaag
	//wanneer men naar de ongewenste locatie wil wordt hij tegengehouden, door 1 plaats naar voren te kijken en te zien of daar 
	//de boolean staat van of je er wel of niet doorheenmag.
	else if (nunchuk.analogY < grensNaarOnderNunchuck) {
		if (this->locationsOfMap[locatieNummer + 16].nietBegaanBareLocatie) {
		}
		else{
		this->locatieNummer = locatieNummer + 16;

		this->speler1.yLocatie++;
		this->vorigelocatieSpeler1 = omlaag;
		}
	}
	//rechts
	//wanneer men naar de ongewenste locatie wil wordt hij tegengehouden, door 1 plaats naar voren te kijken en te zien of daar 
	//de boolean staat van of je er wel of niet doorheenmag.
	else if (nunchuk.analogX > grensNaarRechtsNunchuck) {
		if(this->locationsOfMap[locatieNummer + 1].nietBegaanBareLocatie){
		}
		else {
			this->speler1.xLocatie++;
			this->vorigelocatieSpeler1 = rechts;
			this->locatieNummer = locatieNummer + 1;
		}
	}
	//links
	//wanneer men naar de ongewenste locatie wil wordt hij tegengehouden, door 1 plaats naar voren te kijken en te zien of daar 
	//de boolean staat van of je er wel of niet doorheenmag.
	else if (nunchuk.analogX < grensNaarLinksNunchuck) {
		if (this->locationsOfMap[locatieNummer - 1].nietBegaanBareLocatie) {
		}
		else{
		this->speler1.xLocatie--;
		this->vorigelocatieSpeler1 = links;
		this->locatieNummer = locatieNummer - 1;
		}

	}

	nunchuk.update();
}

void Speelveld::tekenVerplaatsingPoppetje()
{
	
	int x = (this->speler1.xLocatie * 20) - 20;
	int y= (this->speler1.yLocatie * 20) - 20;

	switch (this->vorigelocatieSpeler1) {

	case omhoog: y = ((this->speler1.yLocatie + 1) * 20) - 20;
		break;
	case omlaag: y = ((this->speler1.yLocatie - 1) * 20) - 20;
		break;
	case links: x = ((this->speler1.xLocatie + 1) * 20) - 20;
		break;
	case rechts: x = ((this->speler1.xLocatie - 1) * 20) - 20;
		break;
	}

	int x2 = (this->speler2.xLocatie * 20) - 20;
	int y2 = (this->speler2.yLocatie * 20) - 20;

	switch (this->vorigelocatieSpeler2) {

	case omhoog: y2 = ((this->speler2.yLocatie + 1) * 20) - 20;
		break;
	case omlaag: y2 = ((this->speler2.yLocatie - 1) * 20) - 20;
		break;
	case links: x2 = ((this->speler2.xLocatie + 1) * 20) - 20;
		break;
	case rechts: x2 = ((this->speler2.xLocatie - 1) * 20) - 20;
		break;
	}
		this->lcdGame.fillRect(x, y, 20, 20, RGB(0, 53, 0));//vorige locatie wegtekenen
		this->lcdGame.fillRect(x2, y2, 20, 20, RGB(0, 53, 0));//vorige locatie wegtekenen

	speler1.drawPoppetje(speler1.xLocatie, speler1.yLocatie);
	speler2.drawPoppetje(speler2.xLocatie, speler2.yLocatie);
}

void Speelveld::levensTekenen(uint8_t speler)
{
	int x = 230;
	int x1 = 250;
	int x2 = 270;

	int xcircle = (15 * 20) - 32;
	int ycircle = (12* 20) - 12;

	switch (speler)
	{
	case 1:
		
		this->lcdGame.fillTriangle(x + 30-160, x, x + 40-160, x, x + 35-160, x + 10, RGB(255, 3, 3));
		this->lcdGame.fillTriangle(x1 + 30-160, x, x1 + 40-160, x, x1 + 35-160, x + 10, RGB(255, 3, 3));
		this->lcdGame.fillTriangle(x2 + 30-160, x, x2 + 40-160, x, x2 + 35-160, x + 10, RGB(255, 3, 3));
		
		for (size_t i = 0; i < 3; i++)
		{
			this->lcdGame.fillCircle(xcircle + (20 * i)-160, ycircle, 3, RGB(255, 3, 3));
			this->lcdGame.fillCircle(xcircle + (20 * i) - 160 - 6, ycircle, 3, RGB(255, 3, 3));
		}

		break;
	case 2:
		this->lcdGame.fillTriangle(x + 30, x, x + 40, x, x + 35, x + 10, RGB(255, 3, 3));
		this->lcdGame.fillTriangle(x1 + 30, x, x1 + 40, x, x1 + 35, x + 10, RGB(255, 3, 3));
		this->lcdGame.fillTriangle(x2 + 30, x, x2 + 40, x, x2 + 35, x + 10, RGB(255, 3, 3));

		for (size_t i = 0; i < 3; i++)
		{
			this->lcdGame.fillCircle(xcircle + (20 * i), ycircle, 3, RGB(255, 3, 3));
			this->lcdGame.fillCircle(xcircle + (20 * i) - 6, ycircle, 3, RGB(255, 3, 3));

		}
		break;
	default:
		break;
	}
	uint8_t beschadegingSpeler1= 3 - this->speler1.levens;
	uint8_t beschadegingSpeler2 = 3 - this->speler2.levens;
	
	for (size_t i = 0; i < beschadegingSpeler1; i++)
	{
		this->lcdGame.fillRect((6 * 20) - 22 +(i*20), (12 * 20) - 20, 18, 23, 1);

	}
	for (size_t i = 0; i < beschadegingSpeler2; i++)
	{
		this->lcdGame.fillRect((6 * 20) - 22 + (i * 20)+160, (12 * 20) - 20, 18, 23, 1);
	}


}

void Speelveld::maakOnbegaanbareMuren()
{
	//Het maken van de map waarbij 

	//voor elke Y waarde wordt het aanmaken van een rij blokken waar je niet doorheenkunt aangemaakt
	for (size_t y = 0; y < 12; y++)
	{
	
	for (size_t i = 0; i < 15; i++)		// een rij blokken waar je niet doorheenkunt wordt aangemaakt
	{
		i++;
		this->locationsOfMap[(i+(16*y))].nietBegaanBareLocatie = 1;
		this->locationsOfMap[(i+(16*y))].onverwoestbareLocatie = 1;

		this->lcdGame.fillRect((i * 20) - 20, ((y+1) * 20) - 20, 20, 20, RGB(50, 50, 50));
		this->lcdGame.drawRect((i * 20) - 20, ((y+1) * 20) - 20, 20, 20, 0);

	}
	y++;
	}	
}

void Speelveld::DropBomb(int speler)
{
	if (speler == 1) {

		this->speler1.bom.cooldownBom++;

		if ((this->nunchuk.zButton && this->speler1.bom.cooldownBom > 10)) {
			this->speler1.bom.cooldownBom = 0;
			this->bomID++;//1+


			this->speler1.bom.xLocatie = this->speler1.xLocatie;
			this->speler1.bom.yLocatie = this->speler1.yLocatie;
			this->speler1.bom.bomStatus = 1;

			

			this->locationsOfMap[this->vanXenYNaarLocatieNummer(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie)].nietBegaanBareLocatie = 1;

	
			this->tekenBom(this->speler1.xLocatie, this->speler1.yLocatie);

		}

		if (this->speler1.bom.bomStatus == 1 )
		{
			
			this->tekenBom(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie);
		}

		for (size_t i = 0; i < 3; i++)
		{
			if (this->speler1.bom.bomStatus) {
				this->speler1.bom.aftellenTotExplosieBom++;
			}
		}
		
			if (this->speler1.bom.aftellenTotExplosieBom > 70) {
				this->locationsOfMap[this->vanXenYNaarLocatieNummer(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie)].nietBegaanBareLocatie = 0;
				this->speler1.bom.aftellenTotExplosieBom = 0;
				this->speler1.bom.bomStatus = 0;
				this->speler1.bom.schadeOpruimen = 1;
			
				//explodeer op de plek waar de bom gestaan heeft
				this->speler1.tekenOntploffing(speler1.bom.xLocatie, speler1.bom.yLocatie);

		 //zorgt voor ondergrondse ontploffing dat alle spelstukken veranderen en tekent ook alle kanten om zich heen, behalve waar de bom zat zelf maar dat gebeurt hierboven
				this->ontploffingBom(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie);
			}
			if (this->speler1.bom.schadeOpruimen) {
				this->speler1.bom.opruimenBomTijd++;
			}

			if (this->speler1.bom.opruimenBomTijd>30) {


				this->bomOpruimen(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie);
				this->speler1.bom.schadeOpruimen = 0;
				this->speler1.bom.opruimenBomTijd = 0;
				this->bomID--;


			}


	}

	//to do voor speler 2

}

void Speelveld::maakRandomMapEenMap()
{
}

void Speelveld::maakVerwoestbareMuur(int xLocatie, int yLocatie)
{//tekenen op de map
	int x = (xLocatie * 20) - 20;
	int y = (yLocatie * 20) - 20;
	
	
	this->lcdGame.fillRect(x, y, 20, 20, RGB(125, 98, 44));
	this->lcdGame.fillRect(x + 5, y, 2, 20, RGB(152, 119, 54));
	this->lcdGame.fillRect(x + 14, y, 2, 20, RGB(152, 119, 54));
	this->lcdGame.drawRect(x, y, 20, 20, RGB(1, 1, 1));
	int locatieMap = ((yLocatie - 1) * 16) + xLocatie;

	//instellen in map dat er een muur is
	this->locationsOfMap[locatieMap].nietBegaanBareLocatie = 1;


}

void Speelveld::maakLevel(uint8_t level)
{
	switch (level)
	{
	case 1: 
		for (size_t i = 0; i < 9; i++)
		{
			maakVerwoestbareMuur(4, 2 + i);
			maakVerwoestbareMuur(6, 2 + i);
			maakVerwoestbareMuur(8, 2 + i);
			maakVerwoestbareMuur(10, 2 + i);
			maakVerwoestbareMuur(12, 2 + i);

		}
	
		for (size_t i = 0; i < 13; i++) 
		{
			maakVerwoestbareMuur(2 + i, 4);
			maakVerwoestbareMuur(2 + i, 6);
			maakVerwoestbareMuur(2 + i, 8);
		}

	

		break;
	case 2: 
		maakVerwoestbareMuur(8,6);
		//binnenkant
		for (uint8_t i = 0; i < 9; i++)
		{
			maakVerwoestbareMuur(4 + i, 4);
			maakVerwoestbareMuur(4 + i, 8);

		}
		for (uint8_t i = 0; i < 3; i++)
		{
			maakVerwoestbareMuur(4 , 5+i);
			maakVerwoestbareMuur(12, 5+i);

		}
		//buitenkant 
		//horizontaal
		for (uint8_t i = 0; i < 13; i++)
		{
			maakVerwoestbareMuur(2 + i, 2);
			maakVerwoestbareMuur(2 + i, 10);
		}

		//verticaal
		for (uint8_t i = 0; i < 8; i++)
		{
			maakVerwoestbareMuur(2, 3 + i);
			maakVerwoestbareMuur(14, 2 + i);

		}

		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}


}

int Speelveld::vanXenYNaarLocatieNummer(int x, int y)
{
	int locatieIndex = ((y - 1) * 16) + x;
	return locatieIndex;
}

void Speelveld::ontploffingBom(uint8_t xLocatie, uint8_t yLocatie)
{	
	ontploffingBomVanLijn(xAsLinks, xLocatie, yLocatie);
	ontploffingBomVanLijn(xAsRechts, xLocatie, yLocatie);
	ontploffingBomVanLijn(yAsBoven, xLocatie, yLocatie);
	ontploffingBomVanLijn(yAsOnder, xLocatie, yLocatie);
	
}

void Speelveld::ontploffingBomVanLijn(char as, uint8_t xLocatie, uint8_t yLocatie)
{
	int locatieIndex = ((yLocatie - 1) * 16) + xLocatie;//de index die aangeeft welke locatie het is van de x en y waarde
	int locatieCounter;	//om aan te geven welke kant de locatie op gaat
	int yAsMin=-1;		//oor de y as wanneer
/*	*Wanneer  een locatie naar rechts gaat dan gaat de waarde +1 dus gewoon 1
	*Wanneer  een locatie naar rechts gaat dan gaat de waarde -1 dus gewoon -1
	*Wanneer  een locatie naar boven gaat dan gaat de waarde +16 dus gewoon 16
	*Wanneer  een locatie naar rechts gaat dan gaat de waarde -16 dus gewoon 16

*/	

	switch (as)
	{
	case xAsRechts:
		locatieCounter = 1;
		
		break;
	case xAsLinks:
		locatieCounter = -1;
			break;
	case yAsBoven:
		locatieCounter = -16;
		yAsMin = 1;
				break;
	case yAsOnder:
		locatieCounter = 16;

	default:
		break;
	}

	
	for (size_t i = 1; i < this->rangeBomb; i++)
	{
		
		
		if (speler1.xLocatie == this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarX(locatieIndex + locatieCounter * i) && speler1.yLocatie == this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarY(locatieIndex + locatieCounter * i))
		{
			this->speler1.levens--;
			this->levensTekenen(1);
		
		}
		
		if (speler2.xLocatie == this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarX(locatieIndex + locatieCounter * i) && speler2.yLocatie == this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarY(locatieIndex + locatieCounter * i)) {
			this->speler2.levens--;
			this->levensTekenen(2);
		

		}

		if (as ==xAsLinks || as == xAsRechts)
		{

			tekenOntploffing(this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarX(locatieIndex + locatieCounter * i) - locatieCounter, this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarY(locatieIndex + locatieCounter * i));//teken de ontploffing
		
		}
		else
		{
			
			tekenOntploffing(this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarX(locatieIndex + locatieCounter * i), this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarY(locatieIndex + locatieCounter * i) + yAsMin);//teken de ontploffing

		}
																																		 //wanneer de rechter locatie een nietkapotbare te maken locatie is dan stopt de ontploffing
		if (this->locationsOfMap[locatieIndex + locatieCounter * i].onverwoestbareLocatie) {
			i = rangeBomb + 1;//stop de explosie
		}

		else
		{
			//wanneer de rechter locatie kapot kan, dan gaat hij kapot en stopt de explosie
			if (this->locationsOfMap[locatieIndex + locatieCounter * i].nietBegaanBareLocatie) {
				this->locationsOfMap[locatieIndex + locatieCounter * i].nietBegaanBareLocatie = 0;
				i = rangeBomb + 1;//de explosie stopt

			}
		}
	}
}

void Speelveld::tekenBom(uint8_t xLocatie, uint8_t yLocatie)
{
	int x;
	int y;
	
		x = (xLocatie * 20) - 10;
		y = (yLocatie * 20) - 10;

		this->lcdGame.drawCircle(x, y, 5, 0);
		this->lcdGame.fillCircle(x, y, 5, 0);
		this->lcdGame.fillRect(x + 4, y - 5, 3, 3, 0);
		this->lcdGame.fillRect(x + 5, y - 7, 3, 3, RGB(229, 12, 13));
}

void Speelveld::tekenOntploffing(uint8_t xLocatie, uint8_t yLocatie)
{
	int x;
	int y;

	x = (xLocatie * 20) - 20;
	y = (yLocatie * 20) - 20;

	this->lcdGame.drawRect(x, y, 20, 20, RGB(255, 10, 10));
	this->lcdGame.fillRect(x, y, 20, 20, RGB(255, 10, 10));

}

void Speelveld::bomOpruimen(uint8_t xLocatie, uint8_t yLocatie)
{
	int locatieIndex = ((yLocatie - 1) * 16) + xLocatie;
															  
	 //=====TekenOpruimingOmhoog=====
	for (size_t i = 1; i < this->rangeBomb; i++)
	{
		
		tekenOpruiming(this->locationsOfMap[locatieIndex - 16 * i].vanLocationNummerNaarX(locatieIndex - 16 * i), this->locationsOfMap[locatieIndex - 16 * i].vanLocationNummerNaarY(locatieIndex - 16 * i)+1);//teken de opruiming
		if (this->locationsOfMap[locatieIndex - 16 * i].onverwoestbareLocatie) {
			i = rangeBomb + 1;//stop het tekenen
		}
		else
		{
			//wanneer de  locatie omhoog kapot kan, dan gaat hij kapot en stopt het wegtekenen van de locatie
			if (this->locationsOfMap[locatieIndex - 16 * i].nietBegaanBareLocatie) {
				i = rangeBomb + 1;//stop de explosie
			}
		}

	}

	//==========tekenOpruimingOmlaag===========
	for (size_t i = 1; i < this->rangeBomb; i++)
	{

		tekenOpruiming(this->locationsOfMap[locatieIndex + 16 * i].vanLocationNummerNaarX(locatieIndex + 16 * i), this->locationsOfMap[locatieIndex + 16 * i].vanLocationNummerNaarY(locatieIndex + 16 * i) - 1);//teken de opruiming
		if (this->locationsOfMap[locatieIndex + 16 * i].onverwoestbareLocatie) {
			i = rangeBomb + 1;//stop het tekenen
		}
		else
		{
			//wanneer de  locatie omhoog kapot kan, dan gaat hij kapot en stopt het wegtekenen van de locatie
			if (this->locationsOfMap[locatieIndex + 16 * i].nietBegaanBareLocatie) {
				i = rangeBomb + 1;//stop de explosie
			}
		}

	}

	//==============tekenOpruimingRechts-===========
	for (size_t i = 1; i < this->rangeBomb; i++)
	{
		

		tekenOpruiming(this->locationsOfMap[locatieIndex + 1 * i].vanLocationNummerNaarX(locatieIndex + 1 * i) - 1, this->locationsOfMap[locatieIndex +1 * i].vanLocationNummerNaarY(locatieIndex +1 * i));//teken de ontploffing
		if (this->locationsOfMap[locatieIndex + 1 * i].onverwoestbareLocatie) {
			i = rangeBomb + 1;//stop het tekenen
		}
		else
		{
			//wanneer de  locatie omhoog kapot kan, dan gaat hij kapot en stopt het wegtekenen van de locatie
			if (this->locationsOfMap[locatieIndex + 1 * i].nietBegaanBareLocatie) {
				i = rangeBomb + 1;//stop de explosie
			}
		}
	}


	//==============tekenOpruimingLinks-===========
	for (size_t i = 1; i < this->rangeBomb; i++)
	{
		tekenOpruiming(this->locationsOfMap[locatieIndex - 1 * i].vanLocationNummerNaarX(locatieIndex - 1 * i) +1, this->locationsOfMap[locatieIndex - 1 * i].vanLocationNummerNaarY(locatieIndex - 1 * i));//teken de ontploffing
		if (this->locationsOfMap[locatieIndex - 1 * i].onverwoestbareLocatie) {
			i = rangeBomb + 1;//stop het tekenen
		}
		else
		{
			//wanneer de  locatie omhoog kapot kan, dan gaat hij kapot en stopt het wegtekenen van de locatie
			if (this->locationsOfMap[locatieIndex - 1 * i].nietBegaanBareLocatie) {
				i = rangeBomb + 1;//stop de explosie
			}
		}
	}



}

void Speelveld::tekenOpruiming(uint8_t xLocatie, uint8_t yLocatie)
{
	int x;
	int y;

	x = (xLocatie * 20) - 20;
	y = (yLocatie * 20) - 20;

	this->lcdGame.drawRect(x, y, 20, 20, RGB(0, 53, 0));
	this->lcdGame.fillRect(x, y, 20, 20, RGB(0, 53, 0));
}


