// hoofdmenu.h
#include <ArduinoNunchuk.h>
#include <MI0283QT9.h>
#include "LevelMenu.h"

#ifndef _HOOFDMENUU_h
#define _HOOFDMENUU_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class hoofdmenuu {

public:
	hoofdmenuu();
	//buttons tekenen voor de menu
	void buttonstart(int);
	void buttonscores(int);
	void welkebutton();//methode voor het nagaan welke button er geslecteerd is
	void hoofdmenuloop();//een stand die in de main komt die steeds kijkt wat er gebeurt
	void hoofdmenusetup();// het instellen van de hoofdmenu
	ArduinoNunchuk nunchuk = ArduinoNunchuk();
	void drawbuttons(MI0283QT9 lcd);
	void setPageState(PageState Currentpage);
	PageState pageState;
	LevelMenu levelmenu;
	int tekstdraaigetal = 150;//waarde voor het laten draaien van de tekst
	uint16_t potwaarde = 100;//potwaarde voor de helderheid
	MI0283QT9 lcd; //I2C (GLCD-Shield or MI0283QT Adapter v2

private:
	int buttoncount = 1;
	
	enum nunchuckDirection
	{
		naarBovenGrens=137,
		naarOnderGrens=125
	};

};


#endif

