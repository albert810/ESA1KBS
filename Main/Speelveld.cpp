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

void Speelveld::backToMainMenoLoop()
{
	this->nunchuk.update();
//status naar het terug gaan naar het spel
	if (nunchuk.cButton) {
		this->backToMainMenu = 0;
		free(locationsOfMap);//resetten van de locaties
		this->enableMainMenu = 1;//ga terug naar de main menu
	}
}

void Speelveld::resetValuesOfTheGame()
{
	//wanneer het spel opnieuw moet beginnen worden de levens reset en krijgt de standaard waarde.
	this->speler1.levens = 3;
	this->speler2.levens = 3;
	this->vorigelocatieSpeler1 = 0;
	this->vorigelocatieSpeler2 = 5;

	//het resetten van de onbegaanbare locaties van de levels
	switch (this->level)
	{
	case level1:
		//alle locatie vernietigen die aangemaakt zijn van de y as 
		for (size_t i = 0; i < 9; i++)
		{
			vernietigLocatie(4, 2 + i);
			vernietigLocatie(6, 2 + i);
			vernietigLocatie(8, 2 + i);
			vernietigLocatie(10, 2 + i);
			vernietigLocatie(12, 2 + i);

		}

		//alle locaties vernietigen die aangemaakt zijn van de x as
		for (size_t i = 0; i < 13; i++)
		{
			vernietigLocatie(2 + i, 4);
			vernietigLocatie(2 + i, 6);
			vernietigLocatie(2 + i, 8);
		}
		break;
	case level2:
		vernietigLocatie(8, 6);
		//binnenkant
		for (uint8_t i = 0; i < 9; i++)
		{
			vernietigLocatie(4 + i, 4);
			vernietigLocatie(4 + i, 8);

		}
		for (uint8_t i = 0; i < 3; i++)
		{
			vernietigLocatie(4, 5 + i);
			vernietigLocatie(12, 5 + i);

		}
		//buitenkant 
		//horizontaal
		for (uint8_t i = 0; i < 13; i++)
		{
			vernietigLocatie(2 + i, 2);
			vernietigLocatie(2 + i, 10);
		}

		//verticaal
		for (uint8_t i = 0; i < 8; i++)
		{
			vernietigLocatie(2, 3 + i);
			vernietigLocatie(14, 2 + i);

		}
		break;
	default:
		break;
	}
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
	//je Z button was nog ingedrukt van de hoofdmenu en de nunchuck moet even weer stabiel worden vandaar wordt
	//de nunchuck een aantal keer geupdate, dit moet anders komt er een bug.
	for (size_t i = 0; i < 10; i++)
	{
		this->nunchuk.update();
	}
	//instellen van alles
	this->level = level;
	this->setLCD(lcd);
	this->setNunchuck(nunchuck);
	drawBegin(level,  locatienummer);
	
	this->levensTekenen(1);//speler1
	this->levensTekenen(2);//speler2

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
		//teken randen y
		this->lcdGame.fillRect((2 * 20) - 20, (11 * 20) - 20, 260, 20, RGB(50, 50, 50));
		this->lcdGame.drawRect((2 * 20) - 20, (11 * 20) - 20, 260, 20, RGB(50, 50, 50));
		this->lcdGame.fillRect((1 * 20) - 20, (12 * 20) - 20, 320, 20, 0);
		this->lcdGame.drawRect((1 * 20) - 20, (12 * 20) - 20, 320, 20, 0);

		this->lcdGame.fillRect((16 * 20) - 20, (1 * 20) - 20, 20, 260, 0);
		this->lcdGame.drawRect((16 * 20) - 20, (1 * 20) - 20, 20, 260, 0);

		//beginselen voor het spel instellen
		this->locatieNummer = locatieNummer;
		this->bomID = 0;
		this->maakOnbegaanbareMuren();
		this->spelersZijnIngesteld = 1;
		maakLevel(level);
}

void Speelveld::verplaatsPoppetje()
{
	
	
	nunchuk.update();
	this->speler1.snelheidsGrens++;
	if(this->speler1.snelheidsGrens>cooldownBewegenSpeler){
	//omhoog
	//wanneer men naar de ongewenste locatie wil wordt hij tegengehouden, door 1 plaats naar voren te kijken en te zien of daar 
	//de boolean staat van of je er wel of niet doorheenmag.
	if (nunchuk.analogY > grensNaarBovenNunchuck) {
		if (this->locationsOfMap[locatieNummer -16].nietBegaanBareLocatie ) {
		}
		else{
			c.sendSingleData(verzendSpelerOmhoog);
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
			c.sendSingleData(verzendSpelerOmlaag);
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
			c.sendSingleData(verzendSpelerNaarRechts);
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
			c.sendSingleData(verzendSpelerNaarLinks);
		this->speler1.xLocatie--;
		this->vorigelocatieSpeler1 = links;
		this->locatieNummer = locatieNummer - 1;
		}

	}
	this->speler1.snelheidsGrens = 0;
	}
	nunchuk.update();
	
}

void Speelveld::tekenVerplaatsingPoppetje()
{
	
	int x = (this->speler1.xLocatie * 20) - 20;//formule voor een vierkant van de locatie x speler 1
	int y= (this->speler1.yLocatie * 20) - 20;//formule voor een vierkant van de locatie y speler 1
	//kijken wat de vorige locatie was
	switch (this->vorigelocatieSpeler1){

	case omhoog: y = ((this->speler1.yLocatie + 1) * 20) - 20;
		break;
	case omlaag: y = ((this->speler1.yLocatie - 1) * 20) - 20;
		break;
	case links: x = ((this->speler1.xLocatie + 1) * 20) - 20;
		break;
	case rechts: x = ((this->speler1.xLocatie - 1) * 20) - 20;
		break;
	}
	
	int x2 = (this->speler2.xLocatie * 20) - 20;//formule voor een vierkant van de locatie x speler 2
	int y2 = (this->speler2.yLocatie * 20) - 20;//formule voor een vierkant van de locatie x speler 2

	//kijken voor speler 2 wat de vorige locatie was
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
	//de vorige locatie van speler 1 en speler 2(daarvan de x en y locaties) weggummen, zodat niet 2 keer een poppetje getekent word voor 1 speler.
		this->lcdGame.fillRect(x, y, 20, 20, RGB(0, 53, 0));//vorige locatie wegtekenen
		this->lcdGame.fillRect(x2, y2, 20, 20, RGB(0, 53, 0));//vorige locatie wegtekenen

		//de spelers zelf tekenen
	speler1.drawPoppetje(speler1.xLocatie, speler1.yLocatie);
	speler2.drawPoppetje(speler2.xLocatie, speler2.yLocatie);

}

void Speelveld::levensTekenen(uint8_t speler)
{
	/*een leven bestaat uit hartjes
	De hartjes hebben een driehoen en twee rondjes
	dus:  oo
		  \/
		  maar dan ingekleurd*/
	//indexen voor het tekenen van een hartje voor de driehoek
	int x = 230;
	int x1 = 250;
	int x2 = 270;

	//indexen voor het tekenen van rondjes
	int xcircle = (15 * 20) - 32;
	int ycircle = (12* 20) - 12;

	//als er voor speler X levens getekent moet worden:
	switch (speler)
	{
		//speler1
	case 1:
		//drie driehoeken tekenen
		this->lcdGame.fillTriangle(x + 30-160, x, x + 40-160, x, x + 35-160, x + 10, RGB(255, 3, 3));
		this->lcdGame.fillTriangle(x1 + 30-160, x, x1 + 40-160, x, x1 + 35-160, x + 10, RGB(255, 3, 3));
		this->lcdGame.fillTriangle(x2 + 30-160, x, x2 + 40-160, x, x2 + 35-160, x + 10, RGB(255, 3, 3));
		
		for (size_t i = 0; i < 3; i++)
		{
			//6 rondjes tekenen
			this->lcdGame.fillCircle(xcircle + (20 * i)-160, ycircle, 3, RGB(255, 3, 3));
			this->lcdGame.fillCircle(xcircle + (20 * i) - 160 - 6, ycircle, 3, RGB(255, 3, 3));
		}

		break;
		//speler2
	case 2:
		//3 driehoeken tekenen
		this->lcdGame.fillTriangle(x + 30, x, x + 40, x, x + 35, x + 10, RGB(255, 3, 3));
		this->lcdGame.fillTriangle(x1 + 30, x, x1 + 40, x, x1 + 35, x + 10, RGB(255, 3, 3));
		this->lcdGame.fillTriangle(x2 + 30, x, x2 + 40, x, x2 + 35, x + 10, RGB(255, 3, 3));

		for (size_t i = 0; i < 3; i++)
		{
			//6 rondjes tekenen
			this->lcdGame.fillCircle(xcircle + (20 * i), ycircle, 3, RGB(255, 3, 3));
			this->lcdGame.fillCircle(xcircle + (20 * i) - 6, ycircle, 3, RGB(255, 3, 3));
		}
		break;
	default:
		break;
	}

	//het aantal levens is:
	uint8_t beschadegingSpeler1= 3 - this->speler1.levens;
	uint8_t beschadegingSpeler2 = 3 - this->speler2.levens;
	
	//voor elk leven wat je niet hebt word 1 hartje weggetekent voor speler 1 en 2
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
	//Het maken van de map van vaste locaties die niet kapot kunnen
	//voor elke Y waarde wordt het aanmaken van een rij blokken waar je niet doorheenkunt aangemaakt
	//dit is de standard "skelet" wat je nodig bent voor een lege bomberman map.
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
		//de cooldown van de bom begint steeds
		this->speler1.bom.cooldownBom++;
		//wanneer de cooldown afgelopen is en speler de Z knop is ingedrukt
		if ((this->nunchuk.zButton && this->speler1.bom.cooldownBom > cooldownBomLimiet)) {
			c.sendSingleData(verzendBom);//de IR communicatie, verzend commando 5 wat hetzelfde is als "bom"
			//de cooldown word gereset de bomid gaat omhoog, de locatie van de bom word de huidige speler locatie en de bomstatus word 1, dus de bom is gedropt
			this->speler1.bom.cooldownBom = 0;
			this->bomID++;//1+
			this->speler1.bom.xLocatie = this->speler1.xLocatie;
			this->speler1.bom.yLocatie = this->speler1.yLocatie;
			this->speler1.bom.bomStatus = 1;

			//je mag niet over de bom heen lopen, je kunt er niet langs
			this->locationsOfMap[this->vanXenYNaarLocatieNummer(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie)].nietBegaanBareLocatie = 1;
			//ten slotte de bom nog tekenen
			this->tekenBom(this->speler1.xLocatie, this->speler1.yLocatie);

		}
		//teken de bom constant
		if (this->speler1.bom.bomStatus == 1 )
		{
			
			this->tekenBom(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie);
		}

		//de bom is geactiveerd dus nu aftellen
		for (size_t i = 0; i < 3; i++)
		{
			if (this->speler1.bom.bomStatus) {
				this->speler1.bom.aftellenTotExplosieBom++;
			}
		}
		
		//wanneer de bom af moet gaan (dus de aftelletn tot explosie limiet bereikt is, dan gaat hij af.
			if (this->speler1.bom.aftellenTotExplosieBom > aftellenTotExplosieBomLimiet) {
				this->locationsOfMap[this->vanXenYNaarLocatieNummer(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie)].nietBegaanBareLocatie = 0;//maak de locatie weer begaanbaar op de plek waar de bom was
				this->speler1.bom.aftellenTotExplosieBom = 0;//aftellen hoeft niet meer en word gereset
				this->speler1.bom.bomStatus = 0;//bom is er niet meer want is al geexplodeerd
				this->speler1.bom.schadeOpruimen = 1;// de explosie moet nu opgeruimt worden
			
				//explodeer op de plek waar de bom gestaan heeft
				this->speler1.tekenOntploffing(speler1.bom.xLocatie, speler1.bom.yLocatie);

		 //zorgt voor ondergrondse ontploffing dat alle spelstukken veranderen en tekent ook alle kanten om zich heen, behalve waar de bom zat zelf maar dat gebeurt hierboven
				this->ontploffingBom(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie);
			}

			//wanneer de schade opgeruimt moet worden , gaat de opruimtijd omhoog 
			if (this->speler1.bom.schadeOpruimen) {
				this->speler1.bom.opruimenBomTijd++;
			}

			//waneer we willen opruimen (aftellentotopruiming)  is overschreden, dan ruimen we dom bom op.
			if (this->speler1.bom.opruimenBomTijd>aftellenTotOpruimingBom) {
				this->bomOpruimen(this->speler1.bom.xLocatie, this->speler1.bom.yLocatie);//ruim de bom op
				this->speler1.bom.schadeOpruimen = 0;//we hoeven de schade niet meer op te ruimen dus die word 0
				this->speler1.bom.opruimenBomTijd = 0;//reset de timing
				this->bomID--;
			
				//als de tegenstander al zijn levens kwijt is dan is de game afgelopen en ga je naar de volgende scherm dan win je
				if (this->speler2.levens == 0) {
					this->spelersZijnIngesteld = false;//spel is afgelopen dus de spelers zijn niet meer ingesteld
					this->lcdGame.fillScreen(RGB(255, 255, 255));
					lcdGame.drawText(20, 40, "You Win!", RGB(0, 0, 0), RGB(120, 120, 120), 4);//laat you lose op het beeld zien
					this->backToMainMenu = 1;//nu moeten we terug naar het menu, dus word de instantie geactiveerd die er voor meot zorgen dat we terug naar rhet menu gaan
					free(this->locationsOfMap);//reset waardes map
					this->nunchuk.update();
				}
				//als de jijzelf al zijn levens kwijt is dan is de game afgelopen en ga je naar de volgende scherm dan verlies je
				else if (this->speler1.levens == 0) {
					this->spelersZijnIngesteld = false;//spel is afgelopen dus de spelers zijn niet meer ingesteld
					this->lcdGame.fillScreen(RGB(255, 255, 255));//maak het beeld wit
					lcdGame.drawText(20, 40, "You Lose!", RGB(0, 0, 0), RGB(120, 120, 120), 4);//laat you lose op het beeld zien
					this->backToMainMenu = 1;//nu moeten we terug naar het menu, dus word de instantie geactiveerd die er voor meot zorgen dat we terug naar rhet menu gaan
					free(this->locationsOfMap);//reset de waardes map
					this->nunchuk.update();
				}
			}

			//de cooldown van de bom begint steeds
			this->speler2.bom.cooldownBom++;
			if ((this->bomstatusSpeler2 && this->speler2.bom.cooldownBom > cooldownBomLimiet)) {
				//de cooldown word gereset de bomid gaat omhoog, de locatie van de bom word de huidige speler locatie en de bomstatus word 1, dus de bom is gedropt
				this->bomstatusSpeler2 = 0;
				this->speler2.bom.cooldownBom = 0;
				this->bomID++;//1+
				this->speler2.bom.xLocatie = this->speler2.xLocatie;
				this->speler2.bom.yLocatie = this->speler2.yLocatie;
				this->speler2.bom.bomStatus = 1;



				this->locationsOfMap[this->vanXenYNaarLocatieNummer(this->speler2.bom.xLocatie, this->speler2.bom.yLocatie)].nietBegaanBareLocatie = 1;


				this->tekenBom(this->speler2.xLocatie, this->speler2.yLocatie);

			}

			if (this->speler2.bom.bomStatus == 1)
			{

				this->tekenBom(this->speler2.bom.xLocatie, this->speler2.bom.yLocatie);
			}
			//de bom is geactiveerd dus nu aftellen
			for (size_t i = 0; i < 3; i++)
			{
				if (this->speler2.bom.bomStatus) {
					this->speler2.bom.aftellenTotExplosieBom++;
				}
			}

			if (this->speler2.bom.aftellenTotExplosieBom > aftellenTotExplosieBomLimiet) {
				this->locationsOfMap[this->vanXenYNaarLocatieNummer(this->speler2.bom.xLocatie, this->speler2.bom.yLocatie)].nietBegaanBareLocatie = 0;
				this->speler2.bom.aftellenTotExplosieBom = 0;
				this->speler2.bom.bomStatus = 0;
				this->speler2.bom.schadeOpruimen = 1;

				//explodeer op de plek waar de bom gestaan heeft
				this->speler2.tekenOntploffing(speler2.bom.xLocatie, speler2.bom.yLocatie);

				//zorgt voor ondergrondse ontploffing dat alle spelstukken veranderen en tekent ook alle kanten om zich heen, behalve waar de bom zat zelf maar dat gebeurt hierboven
				this->ontploffingBom(this->speler2.bom.xLocatie, this->speler2.bom.yLocatie);
			}
			if (this->speler2.bom.schadeOpruimen) {
				this->speler2.bom.opruimenBomTijd++;
			}
			//waneer we willen opruimen (aftellentotopruiming)  is overschreden, dan ruimen we dom bom op.
			if (this->speler2.bom.opruimenBomTijd>aftellenTotOpruimingBom) {

				this->bomOpruimen(this->speler2.bom.xLocatie, this->speler2.bom.yLocatie);
				this->speler2.bom.schadeOpruimen = 0;
				this->speler2.bom.opruimenBomTijd = 0;
				this->bomID--;

				//wanneer de levens van speler 2 op zijn dan win je // zie speler 1 voor dezelfde commentaar
				if (this->speler2.levens == 0) {
					this->spelersZijnIngesteld = false;
					this->lcdGame.fillScreen(RGB(255, 255, 255));
					lcdGame.drawText(20, 40, "You Win!", RGB(0, 0, 0), RGB(120, 120, 120), 4);
					this->backToMainMenu = 1;
					free(this->locationsOfMap);
					this->nunchuk.update();
				}
				//wanneer de levens van speler 1 op zijn dan verlies  je  // zie speler 1 voor dezelfde commentaar
				else if (this->speler1.levens == 0) {
					this->spelersZijnIngesteld = false;
					this->lcdGame.fillScreen(RGB(255, 255, 255));
					lcdGame.drawText(20, 40, "You Lose!", RGB(0, 0, 0), RGB(120, 120, 120), 4);
					this->backToMainMenu = 1;
					free(this->locationsOfMap);
					this->nunchuk.update();
				}
			}

	}
}
void Speelveld::maakVerwoestbareMuur(int xLocatie, int yLocatie)
{//tekenen op de map formule
	int x = (xLocatie * 20) - 20;
	int y = (yLocatie * 20) - 20;
	
	//teken de muur en bereken wat de locatie van de map het is
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
	case level1: 
		for (size_t i = 0; i < 9; i++)
		{
			//maak 5 rijen y assen van verwoestbare muren
			maakVerwoestbareMuur(4, 2 + i);
			maakVerwoestbareMuur(6, 2 + i);
			maakVerwoestbareMuur(8, 2 + i);
			maakVerwoestbareMuur(10, 2 + i);
			maakVerwoestbareMuur(12, 2 + i);

		}
	
		for (size_t i = 0; i < 13; i++) 
		{
			//maak 3 rijen op de x as en maak hier verwoestbare muren
			maakVerwoestbareMuur(2 + i, 4);
			maakVerwoestbareMuur(2 + i, 6);
			maakVerwoestbareMuur(2 + i, 8);
		}

	

		break;
	case level2: 
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
	case level3:
		break;
	case 4:
		break;
	default:
		break;
	}


}

void Speelveld::vernietigLocatie(int xLocatie, int yLocatie)
{
	//formule voor de locatie van de map, zodat we waten wat dat is
	int locatieMap = ((yLocatie - 1) * 16) + xLocatie;

	//instellen in map dat er een muur is
	this->locationsOfMap[locatieMap].nietBegaanBareLocatie = 0;
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

	//wanneer de speler in de lijn van de explosie komt zal hij een leven verliezen
	for (size_t i = 1; i < this->rangeBomb; i++)
	{	
		if (speler1.xLocatie == this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarX(locatieIndex + locatieCounter * i) && speler1.yLocatie == this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarY(locatieIndex + locatieCounter * i))
		{
			this->speler1.levens--;
			this->levensTekenen(1);//het tekenen van de levens voor speler 1 , hij heeft nu 1 leven minder dus zal hij 1 minder tekenen
		}
		
		if (speler2.xLocatie == this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarX(locatieIndex + locatieCounter * i) && speler2.yLocatie == this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarY(locatieIndex + locatieCounter * i)) {
			this->speler2.levens--;
			this->levensTekenen(2);//het tekenen van de levens voor speler 2, hij heeft nu 1 leven minder dus zal hij 1 minder tekenen
		

		}

		//wanneer de linkser kant van de x as (dus het westen) of de rechter kant de de x as (dus het oostern) het geval is, dan moeten we voor die as de explosie tekenen
		if (as ==xAsLinks || as == xAsRechts)
		{
			tekenOntploffing(this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarX(locatieIndex + locatieCounter * i) - locatieCounter, this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarY(locatieIndex + locatieCounter * i));//teken de ontploffing
		}
		else
		{
			
			tekenOntploffing(this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarX(locatieIndex + locatieCounter * i), this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarY(locatieIndex + locatieCounter * i) + yAsMin);//teken de ontploffing

		}
 //wanneer de rechter locatie een nietkapotbare te maken locatie is dan stopt de ontploffing dus de muur die niet kapot kan
		if (this->locationsOfMap[locatieIndex + locatieCounter * i].onverwoestbareLocatie) {
			i = rangeBomb + 1;//stop de explosie
		}

		else
		{
			//wanneer de  locatie kapot kan, dan gaat de locaite kapot en stopt de explosie
			if (this->locationsOfMap[locatieIndex + locatieCounter * i].nietBegaanBareLocatie) {
				tekenOntploffing(this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarX(locatieIndex + locatieCounter * i), this->locationsOfMap[locatieIndex + locatieCounter * i].vanLocationNummerNaarY(locatieIndex + locatieCounter * i));
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
	//formule voor de tekengrote
		x = (xLocatie * 20) - 10;
		y = (yLocatie * 20) - 10;
		//teken de bom, het is 1 circel met een rood londe er aan
		this->lcdGame.drawCircle(x, y, 5, 0);
		this->lcdGame.fillCircle(x, y, 5, 0);
		this->lcdGame.fillRect(x + 4, y - 5, 3, 3, 0);//de bom
		this->lcdGame.fillRect(x + 5, y - 7, 3, 3, RGB(229, 12, 13));//de londje (met het kleur rood)
}

void Speelveld::tekenOntploffing(uint8_t xLocatie, uint8_t yLocatie)
{
	int x;
	int y;
	//formule voor de tekengrote
	x = (xLocatie * 20) - 20;
	y = (yLocatie * 20) - 20;

	//teken de de explosie die rood is
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
	//formule voor de tekengrote
	x = (xLocatie * 20) - 20;
	y = (yLocatie * 20) - 20;
	//de maak van de locatie weer de achtergrond kleur
	this->lcdGame.drawRect(x, y, 20, 20, RGB(0, 53, 0));
	this->lcdGame.fillRect(x, y, 20, 20, RGB(0, 53, 0));
}
