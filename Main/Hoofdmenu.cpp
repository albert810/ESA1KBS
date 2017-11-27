/*
Name:		hoofdmenu.ccp
Created:	11/16/2017 1:22:40 PM
Author:	Henry
*/
#include "Hoofdmenu.h"


hoofdmenuu::hoofdmenuu()
{
	
}

void hoofdmenuu::buttonstart(int ingedrukt)
{
	//draw the start button	
		lcd.drawRect(57, 102, 206, 56, RGB(120, 120, 120));
		lcd.fillRect(60, 105, 200, 50, RGB(178, 34, 34));
		lcd.drawRect(60, 105, 200, 50, RGB(0, 0, 0));
		lcd.drawText(83, 115, "Start", RGB(0, 0, 0), RGB(178, 34, 34), 4.5);	
	if (ingedrukt == 1) {
		lcd.drawRect(57, 102, 206, 56, RGB(0, 0, 0));
	}
	nunchuk.update();
}

void hoofdmenuu::buttonscores(int ingedrukt2)
{
		//draw the highscores button
		lcd.drawRect(57, 162, 206, 56, RGB(120, 120, 120));
		lcd.fillRect(60, 165, 200, 50, RGB(178, 34, 34));
		lcd.drawRect(60, 165, 200, 50, RGB(0, 0, 0));
		lcd.drawText(81, 183, "Highscores", RGB(0, 0, 0), RGB(178, 34, 34), 2);
	
	if (ingedrukt2 == 1) {
		lcd.drawRect(57, 162, 206, 56, RGB(0, 0, 0));
	}
	nunchuk.update();
}

void hoofdmenuu::welkebutton()
{	
	if (buttoncount == 1) {
		buttonstart(1);
		buttonscores(0);
		}else {
		buttonstart(0);
		buttonscores(1);
	}
	if (nunchuk.analogY > 155) {
		buttoncount--;
	}
	else if (nunchuk.analogY < 100) {
		buttoncount++;
	}
	if (buttoncount > 2) {
		buttoncount = 2;
	}
	if (buttoncount < 1) {
		buttoncount = 1;
	}	
}

void hoofdmenuu::hoofdmenuloop()
{
	nunchuk.update();
	while (nunchuk.analogY < 125 || nunchuk.analogY > 137) {
		welkebutton();
	}
	if (nunchuk.cButton) {
		_delay_ms(10);
		if (buttoncount == 1) {
			//verwijst door als button 1 met button c ingedrukt word naar de game
			Speelveld speelveld(2,2,15,15);
			speelveld.SetupSpeelveld(lcd, nunchuk);
			return;
		}
		else if (buttoncount == 2) {
			//verwijst door als button 2 met button c ingedrukt word
			lcd.fillScreen(RGB(200, 200, 200));
		}
		if (nunchuk.zButton) {
			hoofdmenusetup();
		}
	}
}

void hoofdmenuu::hoofdmenusetup()
{
	nunchuk.init();
	//init display
	lcd.begin();
	//make the screen grey
	lcd.fillScreen(RGB(120, 120, 120));
	//draw the bombermanname
	lcd.drawText(20, 40, "Bomberman", RGB(0, 0, 0), RGB(120, 120, 120), 4);
	nunchuk.init();
	welkebutton();
}
