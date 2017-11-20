/*
 Name:		Main.ino
 Created:	11/16/2017 1:22:40 PM
 Author:	Albert
*/

#include <GraphicsLib.h>
#include <DS1307.h>
#include <ArduinoNunchuk.h>
#include <Wire.h>
#include <MI0283QT9.h>
#include "Hoofdmenu.h"
#include <wiring_private.h>


MI0283QT9 lcd; //I2C (GLCD-Shield or MI0283QT Adapter v2)
ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
	
	Serial.begin(9600);
	nunchuk.init();
	//init display
	lcd.begin();

	//make the screen grey
	lcd.fillScreen(RGB(120, 120, 120)); 
	//draw the start button
	lcd.fillRect(60, 105, 200, 50, RGB(178, 34, 34));
	lcd.drawRect(60, 105, 200, 50, RGB(0, 0, 0));
	lcd.drawText(83, 115, "Start", RGB(0, 0, 0), RGB(178,34,34), 4.5);
	//draw the highscores button
	lcd.fillRect(60, 165, 200, 50, RGB(178, 34, 34));
	lcd.drawRect(60, 165, 200, 50, RGB(0, 0, 0));
}
void loop()
{
	
}

