// Speelveld.h

#ifndef _SPEELVELD_h
#define _SPEELVELD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <ArduinoNunchuk.h>
#include <MI0283QT9.h>
#include "Locatie.h"
#include "Poppetje.h"
class Speelveld {
public:
	
	Location locationsOfMap[192];
	Speelveld(int startPositionForPlayer1X, int startPositionForPlayer1Y, int startPositionForPlayer2X, int startPositionForPlayer2Y);
void	setLCD(MI0283QT9 lcd);
void	setNunchuck(ArduinoNunchuk nunchuck);
void	SetupSpeelveld(MI0283QT9 lcd, ArduinoNunchuk nunchuck);
void	drawBegin();
protected:
private:
	ArduinoNunchuk nunchuk;
	MI0283QT9 lcdGame;
	Poppetje speler1;
	Poppetje speler2;

};


#endif

