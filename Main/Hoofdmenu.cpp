/*
* Hoofdmenu.cpp
*
* Created: 17-11-2017
* Author: henry
*/

#include <GraphicsLib.h>
#include <ArduinoNunchuk.h>
#include <MI0283QT9.h>
#include <DS1307.h>
#include <wiring_private.h>

/*declaratie variabelen*/

MI0283QT9 lcd; //I2C (GLCD-Shield or MI0283QT Adapter v2)
ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
	nunchuk.init();
	//init display
	lcd.begin();

	//clear screen
	lcd.fillScreen(RGB(226, 30, 30)); //achtergrond

}
void loop()
{
	nunchuk.update(); //refresh nunchuk parameters

}

