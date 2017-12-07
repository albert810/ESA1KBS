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
	

//===================instellen programma===============
				Speelveld(int startPositionForPlayer1X, int startPositionForPlayer1Y, int startPositionForPlayer2X, int startPositionForPlayer2Y);
				Speelveld();
void			constructorAlternatief(int startPositionForPlayer1X, int startPositionForPlayer1Y, int startPositionForPlayer2X, int startPositionForPlayer2Y);
void			setLCD(MI0283QT9 lcd);
void			setNunchuck(ArduinoNunchuk nunchuck);
void			SetupSpeelveld(MI0283QT9 lcd, ArduinoNunchuk nunchuck);
void			drawBegin();

ArduinoNunchuk	nunchuk;


//===================spelers+poppetje==================
void			verplaatsPoppetje();
void			tekenVerplaatsingPoppetje();
Poppetje		speler1;
Poppetje		speler2;
boolean			spelersZijnIngesteld;

//===================Muren=========================
void	maakOnbegaanbareMuren();
void	DropBomb(int speler);


//===================locatie====================
int				locatieNummer=0;
MI0283QT9		lcdGame;
Location		locationsOfMap[192];
void			maakRandomMapEenMap();
void			maakVerwoestbareMuur(uint8_t xLocatie, uint8_t yLocatie);
/*
Een enum voor het helpen opslaan van de vorige locatie. Word gebruikt in de methode verplaatspoppetje en tekenverplaatsingpoppetje
*/
enum locatiesVoorScherm
{
	omhoog = 0,
	omlaag = 1,
	links = 2,
	rechts = 3

};

//===================bom=====================
int			bomID;
void		ontploffingBom(uint8_t xLocatie, uint8_t yLocatie);
uint16_t	explosieGrootte;
uint8_t		rangeBomb = 12;
int			vorigeLocatie;
void		tekenBom(uint8_t xLocatie, uint8_t yLocatie);
void		tekenOntploffing(uint8_t xLocatie, uint8_t yLocatie);
protected:
private:


};


#endif

