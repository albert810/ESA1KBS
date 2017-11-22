/*
 Name:		Main.ino
 Created:	11/16/2017 1:22:40 PM
 Author:	Albert
*/
#include "Communication.cpp"

#include "Communication.h"
#include <GraphicsLib.h>
#include <DS1307.h>
#include <ArduinoNunchuk.h>
#include <Wire.h>
#include <MI0283QT9.h>
#include "Hoofdmenu.h"
#include <wiring_private.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint8_t teller = 0;
int counter = 0;
int buttoncount = 0;
MI0283QT9 lcd; //I2C (GLCD-Shield or MI0283QT Adapter v2)
ArduinoNunchuk nunchuk = ArduinoNunchuk();
Communication c;
void setup()
{
	/*c.enableTimer1();

	
	// set timer 1 prescale factor to 64
	sbi(TCCR1B, CS10);
	sbi(TCCR1B, CS12);
	// put timer 1 in 8-bit phase correct pwm mode
	sbi(TCCR1A, WGM10);
	*/
	
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

void buttonstart(int ingedrukt) {
		//draw the start button
		lcd.fillRect(60, 105, 200, 50, RGB(178, 34, 34));
		lcd.drawRect(60, 105, 200, 50, RGB(0, 0, 0));
		lcd.drawText(83, 115, "Start", RGB(0, 0, 0), RGB(178, 34, 34), 4.5);
		if (ingedrukt == 1) {
			lcd.drawRect(55, 95, 220, 70, RGB(0, 0, 0));
	}
}

void buttonscores(int ingedrukt2) {
	//draw the highscores button
	lcd.fillRect(60, 165, 200, 50, RGB(178, 34, 34));
	lcd.drawRect(60, 165, 200, 50, RGB(0, 0, 0));
	lcd.drawText(81, 183, "Highscores", RGB(0, 0, 0), RGB(178, 34, 34), 2);
	if (ingedrukt2 == 1) {
		lcd.drawRect(55, 155, 220, 70, RGB(0, 0, 0));
	}
}

void welkebutton() {
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
		buttonscores;
	}
	else {
		buttonscores(0);
	}
	if (buttoncount > 2) {
		buttoncount = 2;
	}
	Serial.println(buttoncount);
}

void loop()
{
	
}

/*
ISR(TIMER1_COMPA_vect)
{
	counter++;
	if (counter >= 60) {
		//Serial.println("een seconde");
		Serial.println("hai");
		counter = 0;
	}
	
}*/