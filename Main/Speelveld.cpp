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
			l.setLocationX(Xmask);//instellen x co�rdienaat
			l.setLocationY(Ymask);//instellen y co�rdienaat
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
		
			//de randen voor de game worden hier aangemaakt.
			this->lcdGame.fillRect(x, (1 * 20) - 20, 20, 20, RGB(50, 50, 50));
			this->lcdGame.drawRect(x, (1 * 20) - 20, 20, 20, 0);
			this->lcdGame.fillRect(x, (12 * 20) - 20, 20, 20, RGB(50, 50, 50));
			this->lcdGame.drawRect(x, (12 * 20) - 20, 20, 20, 0);
			this->locationsOfMap[i].onbreekbareMuur = 1;

			if (this->locationsOfMap[i].XLocation==1){
				this->lcdGame.fillRect(x, y, 20, 20, RGB(50, 50, 50));
				this->lcdGame.drawRect(x, y, 20, 20, 0);
				this->locationsOfMap[i].onbreekbareMuur = 1;
			}
			if (this->locationsOfMap[i].XLocation == 16) {
				this->lcdGame.fillRect(x, y, 20, 20, RGB(50, 50, 50));
				this->lcdGame.drawRect(x, y, 20, 20, 0);
				this->locationsOfMap[i].onbreekbareMuur = 1;

			}
			
			this->speler1.drawPoppetje(speler1.currentlocatie.XLocation, this->speler1.currentlocatie.YLocation);
		}
		
		this->spelersZijnIngesteld = 1;
		


}

void Speelveld::verplaatsPoppetje()
{
	nunchuk.update();
	//omhoog
	if (nunchuk.analogY > 155) {
		if(!this->locationsOfMap[speler1.currentlocatie.YLocation].onbreekbareMuur){
		this->speler1.currentlocatie.YLocation--;
		this->vorigeLocatie = omhoog;
		Serial.println("omhoog");
		Serial.println(this->speler1.currentlocatie.YLocation);
		}
	}
	//omlaag
	else if (nunchuk.analogY < 100) {
		this->speler1.currentlocatie.YLocation++;
		this->vorigeLocatie = omlaag;
		Serial.println("omlaag");
		Serial.println(this->speler1.currentlocatie.YLocation);


	}
	//rechts
	else if (nunchuk.analogX > 155) {
		this->speler1.currentlocatie.XLocation++;
		this->vorigeLocatie = rechts;
		Serial.println("rechts");
		Serial.println(this->speler1.currentlocatie.XLocation);

	}
	//links
	else if (nunchuk.analogX < 100) {
		this->speler1.currentlocatie.XLocation--;
		this->vorigeLocatie = links;
		Serial.println("links");
		Serial.println(this->speler1.currentlocatie.XLocation);


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
	
	//this->lcdGame.drawRect()
	
}
