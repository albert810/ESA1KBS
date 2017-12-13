#include "LevelMenu.h"

void LevelMenu::button1(MI0283QT9 lcd)
{
	//tekent level 1 button
	lcd.fillRect(60, 105, 200, 25, RGB(178, 34, 34));
	lcd.drawRect(60, 105, 200, 25, RGB(0, 0, 0));
	lcd.drawText(105, 111, "Level 1", RGB(0, 0, 0), RGB(178, 34, 34), 2);
	lcd.drawRect(58, 103, 204, 29, RGB(0, 0, 0));//Selecteert eerste button
}

void LevelMenu::button2(MI0283QT9 lcd)
{
	//tekent level 2 button
	lcd.fillRect(60, 135, 200, 25, RGB(178, 34, 34));
	lcd.drawRect(60, 135, 200, 25, RGB(0, 0, 0));
	lcd.drawText(105, 141, "Level 2", RGB(0, 0, 0), RGB(178, 34, 34), 2);
}

void LevelMenu::button3(MI0283QT9 lcd)
{
	//tekent level 3 button
	lcd.fillRect(60, 165, 200, 25, RGB(178, 34, 34));
	lcd.drawRect(60, 165, 200, 25, RGB(0, 0, 0));
	lcd.drawText(105, 171, "Level 3", RGB(0, 0, 0), RGB(178, 34, 34), 2);
}

void LevelMenu::button4(MI0283QT9 lcd)
{
	//tekent random level button
	lcd.fillRect(60, 195, 200, 25, RGB(178, 34, 34));
	lcd.drawRect(60, 195, 200, 25, RGB(0, 0, 0));
	lcd.drawText(85, 201, "Random Map", RGB(0, 0, 0), RGB(178, 34, 34), 2);
}

void LevelMenu::levelsetup(MI0283QT9 lcd, ArduinoNunchuk nunchuk)
{	
	this->pageState.levelmenu = true;
	//maak een grijze achtergrond
	lcd.fillScreen(RGB(120, 120, 120));
	//tekent de bombermannaam
	lcd.drawText(65, 40, "Levels", RGB(0, 0, 0), RGB(120, 120, 120), 4);
	//print de buttons
	this->button1(lcd);
	this->button2(lcd);
	this->button3(lcd);
	this->button4(lcd);
}

void LevelMenu::levelloop(MI0283QT9 lcd, ArduinoNunchuk nunchuk)
{
	nunchuk.update();
	//als de nunchuck stick op en neer word gedaan word gekeken welke kant die op gaat
	while (nunchuk.analogY < 125 || nunchuk.analogY > 137) {
		if (nunchuk.analogY < 125)
		{
			//levelcount houd bij op welke button de nunchuck geselecteerd staat
			//levelcount gaat omhoog, dus word de volgende button geselecteerd
			this->levelcount++;
			_delay_ms(200);
		}
		else if (nunchuk.analogY > 137)
		{
			//levelcount gaat omlaag, dus word de vorige button geselecteerd
			this->levelcount--;
			_delay_ms(200);
		}
		nunchuk.update();
		//als levelcount hoger word dan 4 word de levelcount weer op 4 gezet omdat er maar vier buttons zijn
		nunchuk.update();
		if (this->levelcount>4)
		{
			this->levelcount = 4;
		}
		//als levelcount lager word dan 1 word de levelcount weer op 1 gezet omdat de levelcount lager dan 1 niet kan met de button, 1 is de laagste
		if (this->levelcount<1)
		{
			this->levelcount = 1;
		}
		Serial.println(this->levelcount);
		nunchuk.update();
		//als op een button geklikt word de juiste level opgehaald
		switch (levelcount)
		{
		case level1:  lcd.drawRect(58, 103, 204, 29, RGB(0, 0, 0));//SELECTEER DE EERSTE BUTTON
		//de andere buttons deselecteren
			lcd.drawRect(58, 193, 204, 29, RGB(120, 120, 120));
			lcd.drawRect(58, 163, 204, 29, RGB(120, 120, 120));
			lcd.drawRect(58, 133, 204, 29, RGB(120, 120, 120));
			break;
		case level2: lcd.drawRect(58, 133, 204, 29, RGB(0, 0, 0));// SELECTEER DE TWEEDE BUTTON
		//de andere buttons deselecteren
			lcd.drawRect(58, 103, 204, 29, RGB(120, 120, 120));
			lcd.drawRect(58, 163, 204, 29, RGB(120, 120, 120));
			lcd.drawRect(58, 193, 204, 29, RGB(120, 120, 120));
			break;
		case level3: lcd.drawRect(58, 163, 204, 29, RGB(0, 0, 0));//SELECTEER DE DERDE BUTTON
		 //de andere buttons deselecteren
			lcd.drawRect(58, 103, 204, 29, RGB(120, 120, 120));
			lcd.drawRect(58, 133, 204, 29, RGB(120, 120, 120));
			lcd.drawRect(58, 193, 204, 29, RGB(120, 120, 120));
			break;
		case randomMap:lcd.drawRect(58, 193, 204, 29, RGB(0, 0, 0));//SELECTEER DE VIERDE BUTTON
		//de andere buttons deselecteren
			lcd.drawRect(58, 163, 204, 29, RGB(120, 120, 120));
			lcd.drawRect(58, 133, 204, 29, RGB(120, 120, 120));
			lcd.drawRect(58, 103, 204, 29, RGB(120, 120, 120));
			break;
		default:
			break;
		}
	}
	
//controlleer of er iets is ingedrukt	
	if (nunchuk.zButton)
	{
		switch (levelcount)
		{
		case level1:
			//start level 1
			this->pageState.setLevelmenu(false);
			this->speelveld.constructorAlternatief(2, 2, 15, 15);
			this->speelveld.SetupSpeelveld(lcd, nunchuk, level1);
			break;
		case level2:
			//start level 2
			this->pageState.setLevelmenu(false);
			this->speelveld.constructorAlternatief(2, 2, 15, 15);
			this->speelveld.SetupSpeelveld(lcd, nunchuk, level2);
			break;
		case level3:
			//start level 3
			this->pageState.setLevelmenu(false);
			this->speelveld.constructorAlternatief(2, 2, 15, 15);
			this->speelveld.SetupSpeelveld(lcd, nunchuk, level3);
			break;
		case randomMap:
			//start random map
		default:
			break;
		}
	}

}


void LevelMenu::welkelevel(MI0283QT9 lcd, ArduinoNunchuk nunchuk)
{
	
}

