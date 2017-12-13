// LevelMenu.h

#ifndef _LEVELMENU_h
#define _LEVELMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <MI0283QT9.h>
#include <ArduinoNunchuk.h>
#include "Speelveld.h"
#include "PageState.h"

class LevelMenu {
public:

	//buttons tekenen
	void button1( MI0283QT9 lcd);
	void button2( MI0283QT9 lcd);
	void button3(MI0283QT9 lcd);
	void button4(MI0283QT9 lcd);

	void levelsetup(MI0283QT9 lcd, ArduinoNunchuk nunchuk);
	void levelloop(MI0283QT9 lcd, ArduinoNunchuk nunchuk);
	void welkelevel(MI0283QT9 lcd, ArduinoNunchuk nunchuk);
	int levelcount = 1;
	Speelveld speelveld = Speelveld();
	void setPageState(PageState Currentpage);
	PageState pageState;
	enum buttonName
	{
		level1 = 1,
		level2 = 2,
		level3 = 3,
		randomMap = 4
	};

	enum nunchuckDirections
	{
		naarOnderGrensNunchuck= 125,
		naarBovenGrensNunchuck=137

	};
	
};
#endif

