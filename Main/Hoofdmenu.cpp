/*
* Hoofdmenu.cpp
*
* Created: 17-11-2017
* Author: henry
*/


#include <DS1307.h>
#include "Hoofdmenu.h"
#include <ArduinoNunchuk.h>
#include <Wire.h>
#include <MI0283QT9.h>
/*declaratie variabelen*/

using namespace std;

MI0283QT9 lcd; //I2C (GLCD-Shield or MI0283QT Adapter v2)

Hoofdmenu::Hoofdmenu() {

	//init display
	lcd.begin();

	//clear screen
	lcd.fillScreen(RGB(226, 30, 30)); //achtergrond

}


