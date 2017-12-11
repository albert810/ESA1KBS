// hoofdmenu.h
#include <ArduinoNunchuk.h>
#include <MI0283QT9.h>


#ifndef _HOOFDMENUU_h
#define _HOOFDMENUU_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "LevelMenu.h"
class hoofdmenuu {

public:
	hoofdmenuu();
	void buttonstart(int);
	void buttonscores(int);
	void welkebutton();
	void hoofdmenuloop();
	void hoofdmenusetup();
	ArduinoNunchuk nunchuk = ArduinoNunchuk();
	void setPageState(PageState Currentpage);
	PageState pageState;
	LevelMenu levelmenu;
	MI0283QT9 lcd; //I2C (GLCD-Shield or MI0283QT Adapter v2
private:
	int buttoncount = 1;
	
};


#endif

