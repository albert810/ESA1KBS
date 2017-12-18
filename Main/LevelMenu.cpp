// 
// 
// 

#include "LevelMenu.h"

void LevelMenu::button1(MI0283QT9 lcd)
{
	//draw the level1 button	
	lcd.fillRect(60, 105, 200, 25, RGB(178, 34, 34));
	lcd.drawRect(60, 105, 200, 25, RGB(0, 0, 0));
	lcd.drawText(105, 111, "Level 1", RGB(0, 0, 0), RGB(178, 34, 34), 2);
	lcd.drawRect(58, 103, 204, 29, RGB(0, 0, 0));//SELECTEER DE EERSTE BUTTON
}

void LevelMenu::button2(MI0283QT9 lcd)
{
	//draw the level2 button	
	lcd.fillRect(60, 135, 200, 25, RGB(178, 34, 34));
	lcd.drawRect(60, 135, 200, 25, RGB(0, 0, 0));
	lcd.drawText(105, 141, "Level 2", RGB(0, 0, 0), RGB(178, 34, 34), 2);
}

void LevelMenu::button3(MI0283QT9 lcd)
{
	//draw the level3 button	
	lcd.fillRect(60, 165, 200, 25, RGB(178, 34, 34));
	lcd.drawRect(60, 165, 200, 25, RGB(0, 0, 0));
	lcd.drawText(105, 171, "Level 3", RGB(0, 0, 0), RGB(178, 34, 34), 2);
}

void LevelMenu::button4(MI0283QT9 lcd)
{
	//draw the level3 button	
	lcd.fillRect(60, 195, 200, 25, RGB(178, 34, 34));
	lcd.drawRect(60, 195, 200, 25, RGB(0, 0, 0));
	lcd.drawText(85, 201, "Random Map", RGB(0, 0, 0), RGB(178, 34, 34), 2);
}

void LevelMenu::levelsetup(MI0283QT9 lcd, ArduinoNunchuk nunchuk)
{
	
	this->pageState.levelmenu = true;
	//make the screen grey
	lcd.fillScreen(RGB(120, 120, 120));
	//draw the bombermanname
	lcd.drawText(65, 40, "Levels", RGB(0, 0, 0), RGB(120, 120, 120), 4);
	this->button1(lcd);
	this->button2(lcd);
	this->button3(lcd);
	this->button4(lcd);
}

void LevelMenu::levelloop(MI0283QT9 lcd, ArduinoNunchuk nunchuk)
{
	
	nunchuk.update();
	while (nunchuk.analogY < naarOnderGrensNunchuck || nunchuk.analogY > naarBovenGrensNunchuck) {
		//nunchuck naar onder
		if (nunchuk.analogY < naarOnderGrensNunchuck)
		{
			this->levelcount++;
			_delay_ms(200);
		}
		//nunchuck naar boven
		else if (nunchuk.analogY > naarBovenGrensNunchuck)
		{
			this->levelcount--;
			_delay_ms(200);
		}
		nunchuk.update();

		nunchuk.update();
		/*de levelcount mag niet meer zijn dan de mogelijkheiden 
		dus als je nog een keer naar onder doet, blijft hij hetzelfde*/
		if (this->levelcount>randomMap)
		{
			this->levelcount = randomMap;
		}
		
		if (this->levelcount<level1)
		{
			this->levelcount = level1;
		}
		nunchuk.update();

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
			this->speelveld.constructorAlternatief(2, 2, 14, 10);
			this->speelveld.SetupSpeelveld(lcd, nunchuk, level1, 18);
			break;
		case level2:
			//start level 2
			this->pageState.setLevelmenu(false);
			this->speelveld.constructorAlternatief(6, 6, 10, 6);
			this->speelveld.SetupSpeelveld(lcd, nunchuk, level2, 86 );
			break;
		case level3:
			//start level 3
			this->pageState.setLevelmenu(false);
			this->speelveld.constructorAlternatief(2, 2, 14, 10);
			this->speelveld.SetupSpeelveld(lcd, nunchuk, level3,18);
			break;
		case randomMap:
			this->pageState.setLevelmenu(false);
			this->speelveld.constructorAlternatief(2, 2, 14, 10);
			this->speelveld.SetupSpeelveld(lcd, nunchuk, randomMap,18);
			//start random map

		default:
			break;
		}
	}

}


void LevelMenu::welkelevel(MI0283QT9 lcd, ArduinoNunchuk nunchuk)
{
	
}

