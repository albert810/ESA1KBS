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
void			SetupSpeelveld(MI0283QT9 lcd, ArduinoNunchuk nunchuck, uint8_t level, int locatienummer);
void			drawBegin(uint8_t level, int locatieNummer);

ArduinoNunchuk	nunchuk;
enum nunchuckDirections
{
	grensNaarBovenNunchuck = 155,
	grensNaarOnderNunchuck = 100,

	grensNaarRechtsNunchuck = 155,
	grensNaarLinksNunchuck = 100
};

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
Location		locationsOfMap[175];
void			maakRandomMapEenMap();
void			maakVerwoestbareMuur(int  xLocatie, int yLocatie);
void			maakLevel(uint8_t level);
int				vanXenYNaarLocatieNummer(int x, int y);
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
void		ontploffingBomVanLijn(char as, uint8_t xLocatie, uint8_t yLocatie);
uint16_t	explosieGrootte;
uint8_t		rangeBomb = 12;
int			vorigelocatieSpeler1;
int			vorigelocatieSpeler2=5;
void		tekenBom(uint8_t xLocatie, uint8_t yLocatie);
void		tekenOntploffing(uint8_t xLocatie, uint8_t yLocatie);
void		bomOpruimen(uint8_t xLocatie, uint8_t yLocatie);
void		tekenOpruiming(uint8_t xLocatie, uint8_t yLocatie);

//om aan te geven welke as de bom van de lijn is. Wordt gebruikt van welke kant van de X as
//Het is gebasseerd op "WASD" voor het geval je je afvraagt waarom deze waardes.
enum bomLijnAs
{
	xAsRechts = 'd',
	xAsLinks = 'a',
	yAsBoven = 'w',
	yAsOnder = 's'
};
protected:
private:


};


#endif

