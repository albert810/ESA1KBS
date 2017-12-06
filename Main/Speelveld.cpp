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

void Speelveld::SetupSpeelveld(MI0283QT9 lcd, ArduinoNunchuk nunchuck)
{
	this->setLCD(lcd);
	this->setNunchuck(nunchuck);
	drawBegin();


}


//het instellen van de game
void Speelveld::drawBegin()
{
//Een mask voor het tijdelijk opslaan van de x locatie en de y locatie 
		int Xmask = 1;
		int Ymask = 1;


// hier worden (16*12) 192 objecten aangemaakt en opgeslagen in een array, deze objecten zijn locaties
		for (size_t i = 1; i < 193; i++)
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
		
		for (size_t i = 1; i < 193; i++)
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
		this->locatieNummer = 18;
		this->bomID = 0;
		this->maakOnbegaanbareMuren();

		this->spelersZijnIngesteld = 1;

}

void Speelveld::verplaatsPoppetje()
{
	nunchuk.update();
	//omhoog
	//wanneer men naar de ongewenste locatie wil wordt hij tegengehouden, door 1 plaats naar voren te kijken en te zien of daar 
	//de boolean staat van of je er wel of niet doorheenmag.
	if (nunchuk.analogY > 155) {
		if (this->locationsOfMap[locatieNummer -16].nietBegaanBareLocatie ) {
		}
		else{
			this->locatieNummer = locatieNummer - 16;
			this->speler1.currentlocatie.YLocation--;
		this->vorigeLocatie = omhoog;
		}
	}
	//omlaag
	//wanneer men naar de ongewenste locatie wil wordt hij tegengehouden, door 1 plaats naar voren te kijken en te zien of daar 
	//de boolean staat van of je er wel of niet doorheenmag.
	else if (nunchuk.analogY < 100) {
		if (this->locationsOfMap[locatieNummer + 16].nietBegaanBareLocatie) {
		}
		else{
		this->locatieNummer = locatieNummer + 16;

		this->speler1.currentlocatie.YLocation++;
		this->vorigeLocatie = omlaag;
		}

	//	this->locatieNummer = locatieNummer + 16;

	}
	//rechts
	//wanneer men naar de ongewenste locatie wil wordt hij tegengehouden, door 1 plaats naar voren te kijken en te zien of daar 
	//de boolean staat van of je er wel of niet doorheenmag.
	else if (nunchuk.analogX > 155) {
		if(this->locationsOfMap[locatieNummer + 1].nietBegaanBareLocatie){
		}
		else {
			this->speler1.currentlocatie.XLocation++;
			this->vorigeLocatie = rechts;
			this->locatieNummer = locatieNummer + 1;
		}
	}
	//links
	//wanneer men naar de ongewenste locatie wil wordt hij tegengehouden, door 1 plaats naar voren te kijken en te zien of daar 
	//de boolean staat van of je er wel of niet doorheenmag.
	else if (nunchuk.analogX < 100) {
		if (this->locationsOfMap[locatieNummer - 1].nietBegaanBareLocatie) {
		}
		else{
		this->speler1.currentlocatie.XLocation--;
		this->vorigeLocatie = links;
		this->locatieNummer = locatieNummer - 1;
		}

	}

	nunchuk.update();
}

void Speelveld::tekenVerplaatsingPoppetje()
{
	int x = (this->speler1.currentlocatie.XLocation * 20) - 20;
	int y= (this->speler1.currentlocatie.YLocation * 20) - 20;

	switch (this->vorigeLocatie) {

	case omhoog: y = ((this->speler1.currentlocatie.YLocation + 1) * 20) - 20;
		break;
	case omlaag: y = ((this->speler1.currentlocatie.YLocation - 1) * 20) - 20;
		break;
	case links: x = ((this->speler1.currentlocatie.XLocation + 1) * 20) - 20;
		break;
	case rechts: x = ((this->speler1.currentlocatie.XLocation- 1) * 20) - 20;
		break;
	}

	this->lcdGame.fillRect(x, y, 20, 20, RGB(0, 53, 0));

	speler1.drawPoppetje(speler1.currentlocatie.XLocation, speler1.currentlocatie.YLocation);//huidige poppetje tekenen
		
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
	//in de argument this->speler1.bom.cooldownBom>

	if (speler = 1) {

		this->speler1.bom[1].cooldownBom++;

		if (this->nunchuk.zButton && this->speler1.bom[1].cooldownBom > 50) {
			this->speler1.bom[1].cooldownBom = 0;
			if (bomID >= 2) { return; }//je kunt niet meer dan 2 bommen droppen
			this->speler1.bom[1].tekenBom();
			this->bomID++;//1
			this->speler1.bom[bomID].bomStatus = 1;
			Serial.println(bomID);

		}
		if (this->speler1.bom[bomID].bomStatus) {
			this->speler1.bom[bomID].aftellenTotExplosieBom++;
		}
		if (this->speler1.bom[bomID].aftellenTotExplosieBom > 180) {
			this->speler1.bom[bomID].aftellenTotExplosieBom = 0;
			this->speler1.bom[bomID].bomStatus = 0;
			this->speler1.bom[bomID].ontploffing();
			this->bomID--;

		}




		//to do voor speler 2
		else
		{
			//this->speler2.bom.tekenBom();
			//this->speler2.bom.cooldownBom = 0;
			//this->speler2.bom.bomStatus = 1;
		}

	}
}
