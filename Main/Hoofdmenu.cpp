/*
Name:		hoofdmenu.ccp
Created:	11/16/2017 1:22:40 PM
Author:	Henry
*/
#include "Hoofdmenu.h"

void hoofdmenuu::buttonstart(int ingedrukt)
{
	//draw the start button
	if (ingedrukt == 0 || 2) {
		lcd.drawRect(57, 102, 206, 56, RGB(120, 120, 120));
		lcd.fillRect(60, 105, 200, 50, RGB(178, 34, 34));
		lcd.drawRect(60, 105, 200, 50, RGB(0, 0, 0));
		lcd.drawText(83, 115, "Start", RGB(0, 0, 0), RGB(178, 34, 34), 4.5);
	}
	if (ingedrukt == 1) {
		lcd.drawRect(57, 102, 206, 56, RGB(0, 0, 0));
	}
	nunchuk.update();
}

void hoofdmenuu::buttonscores(int ingedrukt2)
{
	if (ingedrukt2 == 0 || 2) {
		//draw the highscores button
		lcd.drawRect(57, 162, 206, 56, RGB(120, 120, 120));
		lcd.fillRect(60, 165, 200, 50, RGB(178, 34, 34));
		lcd.drawRect(60, 165, 200, 50, RGB(0, 0, 0));
		lcd.drawText(81, 183, "Highscores", RGB(0, 0, 0), RGB(178, 34, 34), 2);
	}
	if (ingedrukt2 == 1) {
		lcd.drawRect(57, 162, 206, 56, RGB(0, 0, 0));
	}
	nunchuk.update();
}

void hoofdmenuu::welkebutton()
{
	if (nunchuk.analogY > 155) {
		buttoncount--;
	}
	else if (nunchuk.analogY < 100) {
		buttoncount++;
	}
	if (buttoncount == 1) {
		buttonstart(1);
	}
	else {
		buttonstart(0);
	}
	if (buttoncount == 2) {
		buttonscores(1);
	}
	else if (buttoncount < 2) {
		buttonscores(0);
	}
	if (buttoncount > 2) {
		buttoncount = 2;
	}
	if (buttoncount < 0) {
		buttoncount = 0;
	}
	Serial.println(buttoncount);
}

void hoofdmenuu::hoofdmenuloop()
{
	_delay_ms(300);
	nunchuk.update();
	Serial.println(nunchuk.analogY);
	while (nunchuk.analogY < 125 || nunchuk.analogY > 137) {
		welkebutton();
		Serial.println(nunchuk.analogY);

	}
}

void hoofdmenuu::hoofdmenusetup()
{
	Serial.begin(9600);
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
