// PageState.h

#ifndef _PAGESTATE_h
#define _PAGESTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class PageState {

public:
	PageState();
	boolean hoofdmenu;
	boolean game;
	boolean levelmenu;
	boolean currentStatus;

	void setHoofdMenu(boolean state);
	void setGame(boolean state);
	void setLevelmenu(boolean state);
};



#endif

