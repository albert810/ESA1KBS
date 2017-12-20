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
	lcd.drawRect(57, 102, 206, 56, RGB(120, 120, 120));
	if (ingedrukt == 1) {		
		lcd.drawRect(57, 102, 206, 56, RGB(0, 0, 0));
	}
	nunchuk.update();
}

void hoofdmenuu::buttonscores(int ingedrukt2)
{
	lcd.drawRect(57, 162, 206, 56, RGB(120, 120, 120));
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
	lcd.drawText(tekstdraaigetal, 230, "Draai de potentiometer om de helderheid in te stellen", RGB(0, 0, 0), RGB(120, 120, 120), 1);
	tekstdraaigetal--;
	nunchuk.update();
	while (nunchuk.analogY < naarOnderGrens || nunchuk.analogY > naarBovenGrens) {
		welkebutton();
	}
	if (nunchuk.cButton) {
		_delay_ms(10);
		if (buttoncount == 1) {
			//verwijst door als button 1 met button c ingedrukt word naar de game
			this->pageState.setHoofdMenu(false);
			this->levelmenu.levelsetup(this->lcd, this->nunchuk);
			
		//>>>>>>>	this->pageState.setLevelmenu(true);			
		}
		else if (buttoncount == 2) {
			//verwijst door als button 2 met button c ingedrukt word
			
		}
		if (nunchuk.zButton) {
			hoofdmenusetup();
		}
	}
	//helderheid scherm
	//zet de input pin op A0
	ADMUX = 0;
	//5 volt
	ADMUX |= (1 << REFS0);
	//clock 128
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	//adc aanzetten
	ADCSRA |= (1 << ADEN);
	//start
	ADCSRA |= (1 << ADSC);
	//wachten
	while (ADCSRA & (1 << ADSC))
		;
	potwaarde = ADC / 10;
	lcd.led(potwaarde);	
	nunchuk.cButton = false;
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
	drawbuttons(lcd);
	welkebutton();
}

void hoofdmenuu::drawbuttons(MI0283QT9 lcd)
{
	//draw the start button	
	lcd.drawRect(57, 102, 206, 56, RGB(120, 120, 120));
	lcd.fillRect(60, 105, 200, 50, RGB(178, 34, 34));
	lcd.drawRect(60, 105, 200, 50, RGB(0, 0, 0));
	lcd.drawText(83, 115, "Start", RGB(0, 0, 0), RGB(178, 34, 34), 4.5);
	//draw the highscores button
	lcd.drawRect(57, 162, 206, 56, RGB(120, 120, 120));
	lcd.fillRect(60, 165, 200, 50, RGB(178, 34, 34));
	lcd.drawRect(60, 165, 200, 50, RGB(0, 0, 0));
	lcd.drawText(83, 183, "Highscores", RGB(0, 0, 0), RGB(178, 34, 34), 2);
}
void hoofdmenuu::setPageState(PageState Currentpage)
{
	this->pageState = Currentpage;
}
