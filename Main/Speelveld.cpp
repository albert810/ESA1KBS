#include "Speelveld.h"
// 
// 
// 

 
#include "Speelveld.h"
#include "Locatie.h"

Speelveld::Speelveld(int startPositionForPlayer1X, int startPositionForPlayer1Y, int startPositionForPlayer2X, int startPositionForPlayer2Y)
{
	//achtergrond groen maken
	lcdGame.fillScreen(RGB(0, 53, 0));

	//instellen startlocatie speler 1
	this->speler1.currentlocatie.setLocationX(startPositionForPlayer1X);
	this->speler1.currentlocatie.setLocationY(startPositionForPlayer1Y);
	//instellen startlocatie speler 2
	this->speler2.currentlocatie.setLocationX(startPositionForPlayer2X);
	this->speler2.currentlocatie.setLocationY(startPositionForPlayer2Y);


}

Speelveld::Speelveld()
{
}

void Speelveld::constructorAlternatief(int startPositionForPlayer1X, int startPositionForPlayer1Y, int startPositionForPlayer2X, int startPositionForPlayer2Y)
{
	//achtergrond groen maken
	lcdGame.fillScreen(RGB(0, 53, 0));
	//instellen startlocatie speler 1
	this->speler1.currentlocatie.setLocationX(startPositionForPlayer1X);
	this->speler1.currentlocatie.setLocationY(startPositionForPlayer1Y);
	//instellen startlocatie speler 2
	this->speler2.currentlocatie.setLocationX(startPositionForPlayer2X);
	this->speler2.currentlocatie.setLocationY(startPositionForPlayer2Y);


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
	//if(this->spelersZijnIngesteld)



}


//het instellen van de game
void Speelveld::drawBegin(uint8_t level, int locatieNummer)
{
//Een mask voor het tijdelijk opslaan van de x locatie en de y locatie 
		uint8_t Xmask = 1;
		uint8_t Ymask = 1;


// hier worden (16*12) 192 objecten aangemaakt en opgeslagen in een array, deze objecten zijn locaties
		for (size_t i = 1; i < 175; i++)
		{
				
			Location l;//aanmaken tijdelijke locatie
			l.setLocationX(Xmask);//instellen x coördienaat
			l.setLocationY(Ymask);//instellen y coördienaat
			this->locationsOfMap[i] = l; // opslaan in de array
			//wanneer de rij horizon voltooid is (dus x is 16) dan begint het tellen weer opnieuw, en de verticale lijn gaat omhoog daarom gaat de Y++
			if (Xmask==16)
			{
				Xmask = 0;//reset de x weer op 0
				Ymask++;// de y gaat 1 omhoog
			}
			Xmask++;//de 
		}
		//masks weer instellen als 1
		Ymask = 1;
		Xmask = 1;
		
		for (size_t i = 1; i < 175; i++)
		{
			//tijdelijke variabele die de locatie opslaat
			int x = (this->locationsOfMap[i].XLocation * 20) - 20;
			int y = (this->locationsOfMap[i].YLocation * 20) - 20;
		
			//de randen voor de game worden hier getekent.
			this->lcdGame.fillRect(x, (1 * 20) - 20, 20, 20, RGB(50, 50, 50));
			this->lcdGame.drawRect(x, (1 * 20) - 20, 20, 20, 0);
			this->lcdGame.fillRect(x, (12 * 20) - 20, 20, 20, RGB(50, 50, 50));
			this->lcdGame.drawRect(x, (12 * 20) - 20, 20, 20, 0);


			//instellen dat je niet door de randen kunt voor de Y
			if (this->locationsOfMap[i].YLocation == 1 || this->locationsOfMap[i].YLocation == 12 || this->locationsOfMap[i].YLocation == 11) {
			this->locationsOfMap[i].nietBegaanBareLocatie = 1;
			this->locationsOfMap[i].onverwoestbareLocatie = 1;
			this->lcdGame.fillRect(x, y, 20, 20, RGB(50, 50, 50));
			this->lcdGame.drawRect(x, y, 20, 20, 0);
			}




			//teken randen voor de X

			if (this->locationsOfMap[i].XLocation==1 ){
				this->lcdGame.fillRect(x, y, 20, 20, RGB(50, 50, 50));
				this->lcdGame.drawRect(x, y, 20, 20, 0);
				this->locationsOfMap[i].nietBegaanBareLocatie = 1;
				this->locationsOfMap[i].onverwoestbareLocatie = 1;


			}
			if (this->locationsOfMap[i].XLocation == 15) {
				this->lcdGame.fillRect(x, y, 20, 20, RGB(50, 50, 50));
				this->lcdGame.drawRect(x, y, 20, 20, 0);
				this->locationsOfMap[i].nietBegaanBareLocatie = 1;
				this->locationsOfMap[i].onverwoestbareLocatie = 1;


			}
			
			this->speler1.drawPoppetje(speler1.currentlocatie.XLocation, this->speler1.currentlocatie.YLocation);
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
			this->speler1.currentlocatie.YLocation--;
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

		this->speler1.currentlocatie.YLocation++;
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
			this->speler1.currentlocatie.XLocation++;
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
		this->speler1.currentlocatie.XLocation--;
		this->vorigelocatieSpeler1 = links;
		this->locatieNummer = locatieNummer - 1;
		}

	}

	nunchuk.update();
}

void Speelveld::tekenVerplaatsingPoppetje()
{
	int x = (this->speler1.currentlocatie.XLocation * 20) - 20;
	int y= (this->speler1.currentlocatie.YLocation * 20) - 20;

	switch (this->vorigelocatieSpeler1) {

	case omhoog: y = ((this->speler1.currentlocatie.YLocation + 1) * 20) - 20;
		break;
	case omlaag: y = ((this->speler1.currentlocatie.YLocation - 1) * 20) - 20;
		break;
	case links: x = ((this->speler1.currentlocatie.XLocation + 1) * 20) - 20;
		break;
	case rechts: x = ((this->speler1.currentlocatie.XLocation- 1) * 20) - 20;
		break;
	}
	int x2 = (this->speler2.currentlocatie.XLocation * 20) - 20;
	int y2 = (this->speler2.currentlocatie.YLocation * 20) - 20;

	switch (this->vorigelocatieSpeler2) {

	case omhoog: y2 = ((this->speler2.currentlocatie.YLocation + 1) * 20) - 20;
		break;
	case omlaag: y2 = ((this->speler2.currentlocatie.YLocation - 1) * 20) - 20;
		break;
	case links: x2 = ((this->speler2.currentlocatie.XLocation + 1) * 20) - 20;
		break;
	case rechts: x2 = ((this->speler2.currentlocatie.XLocation - 1) * 20) - 20;
		break;
	}
		this->lcdGame.fillRect(x, y, 20, 20, RGB(0, 53, 0));//vorige locatie wegtekenen
		this->lcdGame.fillRect(x2, y2, 20, 20, RGB(0, 53, 0));//vorige locatie wegtekenen

	speler1.drawPoppetje(speler1.currentlocatie.XLocation, speler1.currentlocatie.YLocation);//huidige poppetje tekenen
	speler2.drawPoppetje(speler2.currentlocatie.XLocation, speler2.currentlocatie.YLocation);
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

		this->speler1.bom[1].cooldownBom++;

		if ((this->nunchuk.zButton && this->speler1.bom[1].cooldownBom > 10)&& bomID<1) {
			this->speler1.bom[1].cooldownBom = 0;
			this->bomID++;//1+
			this->speler1.bom[bomID].locatieBom = this->speler1.currentlocatie;
			this->speler1.bom[bomID].bomStatus = 1;
			this->locationsOfMap[this->vanXenYNaarLocatieNummer(this->speler1.bom[bomID].locatieBom.XLocation, this->speler1.bom[bomID].locatieBom.YLocation)].nietBegaanBareLocatie=1;
	

			this->tekenBom(this->speler1.currentlocatie.XLocation, this->speler1.currentlocatie.YLocation);

		}

		if (this->speler1.bom[bomID].bomStatus == 1 )
		{
			this->tekenBom(this->speler1.bom[bomID].locatieBom.XLocation, this->speler1.bom[bomID].locatieBom.YLocation);
		}

		for (size_t i = 0; i < 3; i++)
		{
			if (this->speler1.bom[bomID - i].bomStatus) {
				this->speler1.bom[bomID - i].aftellenTotExplosieBom++;
			}
		}
		
			if (this->speler1.bom[bomID].aftellenTotExplosieBom > 70) {
				Serial.print("x=");
				Serial.println(this->speler1.bom[bomID].locatieBom.XLocation);
				Serial.print("y=");
				Serial.println(this->speler1.bom[bomID].locatieBom.YLocation);
				this->locationsOfMap[this->vanXenYNaarLocatieNummer(this->speler1.bom[bomID].locatieBom.XLocation, this->speler1.bom[bomID].locatieBom.YLocation)].nietBegaanBareLocatie = 0;
				this->speler1.bom[bomID].aftellenTotExplosieBom = 0;
				this->speler1.bom[bomID].bomStatus = 0;
				this->speler1.bom[bomID].schadeOpruimen = 1;
			
				//explodeer op de plek waar de bom gestaan heeft
			this->speler1.tekenOntploffing(this->speler1.bom[bomID].locatieBom.XLocation, this->speler1.bom[bomID].locatieBom.YLocation);

		 //zorgt voor ondergrondse ontploffing dat alle spelstukken veranderen en tekent ook alle kanten om zich heen, behalve waar de bom zat zelf maar dat gebeurt hierboven
				this->ontploffingBom(this->speler1.bom[bomID].locatieBom.XLocation, this->speler1.bom[bomID].locatieBom.YLocation);
			}
			if (this->speler1.bom[bomID].schadeOpruimen) {
				this->speler1.bom[bomID].opruimenBomTijd++;
			}

			if (this->speler1.bom[bomID].opruimenBomTijd>30) {

				this->bomOpruimen(this->speler1.bom[bomID].locatieBom.XLocation, this->speler1.bom[bomID].locatieBom.YLocation);
				this->speler1.bom[bomID].schadeOpruimen = 0;
				this->speler1.bom[bomID].opruimenBomTijd = 0;
				
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
	int locatieIndex = ((yLocatie - 1) * 16) + xLocatie;
	//wanneer een bom ontploft gaat hij (met rangebomb) bij langs hoe groot het bereik is, wanneer er iets geraakt heeft, gaat hij uit de for loop zodat niet meerdere muren kapot gaan)
	
	//=====explosieOmhoog=====
	for (size_t i = 1; i < this->rangeBomb; i++)
	{
		tekenOntploffing(this->locationsOfMap[locatieIndex - 16 * i].XLocation, this->locationsOfMap[locatieIndex - 16 * i].YLocation+1);//teken de ontploffing
		//wanneer de  locatie omhoog een nietkapotbare te maken locatie is dan stopt de ontploffing
		if (this->locationsOfMap[locatieIndex - 16 * i].onverwoestbareLocatie) {
			i = rangeBomb + 1;//stop de explosie
		}
		else
		{
			//wanneer de  locatie omhoog kapot kan, dan gaat hij kapot en stopt de explosie
			if (this->locationsOfMap[locatieIndex - 16 * i].nietBegaanBareLocatie) {
				this->locationsOfMap[locatieIndex - 16 * i].nietBegaanBareLocatie = 0;
				tekenOntploffing(this->locationsOfMap[locatieIndex - 16 * i].XLocation, this->locationsOfMap[locatieIndex - 16 * i].YLocation);
				i = rangeBomb + 1;//stop de explosie
			}
		}

	}

	//=====explosieOmlaag======
		for (size_t i = 1; i < this->rangeBomb; i++)
		{
			tekenOntploffing(this->locationsOfMap[locatieIndex + 16 * i].XLocation, this->locationsOfMap[locatieIndex + 16 * i].YLocation - 1);//teken de ontploffing
			//wanneer de  locatie omlaag een nietkapotbare te maken locatie is dan stopt de ontploffing
			if (this->locationsOfMap[locatieIndex + 16 * i].onverwoestbareLocatie) {
				i = rangeBomb + 1;//stop de explosie
			}
			else
			{
				//wanneer de  locatie omlaag kapot kan, dan gaat hij kapot en stopt de explosie
				if (this->locationsOfMap[locatieIndex + 16 * i].nietBegaanBareLocatie) {
					this->locationsOfMap[locatieIndex + 16 * i].nietBegaanBareLocatie = 0;
					tekenOntploffing(this->locationsOfMap[locatieIndex + 16 * i].XLocation, this->locationsOfMap[locatieIndex + 16 * i].YLocation);
					i = rangeBomb + 1;//stop de explosie

				}
			}
		
		}
	
		
		//=======explosieRechts======
		for (size_t i = 1; i < this->rangeBomb; i++)
		{
			tekenOntploffing(this->locationsOfMap[locatieIndex + 1 * i].XLocation-1, this->locationsOfMap[locatieIndex + 1 * i].YLocation);//teken de ontploffing
			//wanneer de rechter locatie een nietkapotbare te maken locatie is dan stopt de ontploffing
			if (this->locationsOfMap[locatieIndex + 1 * i].onverwoestbareLocatie) {
						i = rangeBomb + 1;//stop de explosie
			}

			else
			{
				//wanneer de rechter locatie kapot kan, dan gaat hij kapot en stopt de explosie
				if (this->locationsOfMap[locatieIndex + 1 * i].nietBegaanBareLocatie) {
					this->locationsOfMap[locatieIndex + 1 * i].nietBegaanBareLocatie = 0;
					tekenOntploffing(this->locationsOfMap[locatieIndex + 1 * i].XLocation, this->locationsOfMap[locatieIndex + 1 * i].YLocation);
					i = rangeBomb + 1;//de explosie stopt

				}
			}
		

		}



		//========explosieLinks=======
		for (size_t i = 1; i < this->rangeBomb; i++) {
			
			tekenOntploffing(this->locationsOfMap[locatieIndex - 1 * i].XLocation + 1, this->locationsOfMap[locatieIndex - 1 * i].YLocation);//teken de ontploffing

			//wanneer de linker locatie een nietkapotbare te maken locatie is dan stopt de ontploffing
			if (this->locationsOfMap[locatieIndex - 1 * i].onverwoestbareLocatie) {
				i = rangeBomb + 1;//stop de explosie
			}
			else
			{
			//wanneer de linker locatie kapot kan, dan gaat hij kapot en stopt de explosie
				if (this->locationsOfMap[locatieIndex - 1 * i].nietBegaanBareLocatie) {
					this->locationsOfMap[locatieIndex - 1 * i].nietBegaanBareLocatie = 0;
					tekenOntploffing(this->locationsOfMap[locatieIndex - 1 * i].XLocation, this->locationsOfMap[locatieIndex - 1 * i].YLocation);
					i = rangeBomb + 1;//stop de explosie
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
	
	 

	this->lcdGame.drawCircle(x, y, 5, 20);
	this->lcdGame.fillCircle(x, y, 5, 20);
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
		tekenOpruiming(this->locationsOfMap[locatieIndex - 16 * i].XLocation, this->locationsOfMap[locatieIndex - 16 * i].YLocation+1);//teken de opruiming
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
		tekenOpruiming(this->locationsOfMap[locatieIndex + 16 * i].XLocation, this->locationsOfMap[locatieIndex + 16 * i].YLocation - 1);//teken de opruiming
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
		tekenOpruiming(this->locationsOfMap[locatieIndex + 1 * i].XLocation - 1, this->locationsOfMap[locatieIndex + 1 * i].YLocation);//teken de ontploffing
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
		tekenOpruiming(this->locationsOfMap[locatieIndex - 1 * i].XLocation +1, this->locationsOfMap[locatieIndex - 1 * i].YLocation);//teken de ontploffing
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


