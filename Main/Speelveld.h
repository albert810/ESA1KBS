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
#include "Communication.h"
class Speelveld {
public:
	
	Communication   c; // voor het instellen van de communicatie. met deze klasse kunnen we bepaalde waardes verzenden

//===================instellen programma===============
				Speelveld(int startPositionForPlayer1X, int startPositionForPlayer1Y, int startPositionForPlayer2X, int startPositionForPlayer2Y);
				Speelveld();
void			constructorAlternatief(int startPositionForPlayer1X, int startPositionForPlayer1Y, int startPositionForPlayer2X, int startPositionForPlayer2Y);
void			setLCD(MI0283QT9 lcd);
void			setNunchuck(ArduinoNunchuk nunchuck);
void			SetupSpeelveld(MI0283QT9 lcd, ArduinoNunchuk nunchuck, uint8_t level, int locatienummer);//instellen van de level
void			drawBegin(uint8_t level, int locatieNummer);//maak de map aan met locaties  (ook met niet begaanbare en onverwoestbare locaties)
void			backToMainMenoLoop();
boolean			backToMainMenu;//wanneer de spel afgelopen is, word deze boolean gebruikt
boolean			enableMainMenu;//wanneer het spel afgelopen is EN er is gedrukt dat je weer terug wilt dan gaat hij terug
void			resetValuesOfTheGame();// alle waardes word gereset
ArduinoNunchuk	nunchuk;
uint8_t			level;
enum levels
{
	level1 = 1,
	level2 = 2,
	level3 = 3,
	randomMap = 4
};

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
void			levensTekenen(uint8_t speler);
Poppetje		speler1;
Poppetje		speler2;
boolean			spelersZijnIngesteld;

//===================Muren=========================
void	maakOnbegaanbareMuren();//maak muren die niet kapot kunnen en waar je niet door kunt


//===================locatie====================
int				locatieNummer=0;
MI0283QT9		lcdGame;
Location		locationsOfMap[175];//alle locaties van de map aanmaken
void			maakRandomMapEenMap();//geen tijd voor gehad dit te implementeren
void			maakVerwoestbareMuur(int  xLocatie, int yLocatie);//een locatie maken met een muur die kapot kan
void			maakLevel(uint8_t level);//een level maken met ongebaanbare muren.
void			vernietigLocatie(int  xLocatie, int yLocatie);// een locatie wordt vernietigd
int				vanXenYNaarLocatieNummer(int x, int y);//een methode om de locatienummer van de map te achterhalen aan de hand van x en y
int				vorigelocatieSpeler1;//het opslaan van de vorige locatie van de spelen (word gedifineerd in de enum)
int				vorigelocatieSpeler2;//het opslaan van de vorige locatie van de spelen (word gedifineerd in de enum)
/*
Een enum voor het helpen opslaan van de vorige locatie. Word gebruikt in de methode verplaatspoppetje en tekenverplaatsingpoppetje
*/
enum locatiesVoorScherm
{
	omhoog = 5,
	omlaag = 6,
	links = 7,
	rechts = 8

};

//===================bom=====================
int			bomID;//het ID voor de trein
void		ontploffingBom(uint8_t xLocatie, uint8_t yLocatie);//deze methode bevat 4 lijn ontploffingen met 4 assen noord zuid oost en west
void		ontploffingBomVanLijn(char as, uint8_t xLocatie, uint8_t yLocatie);//deze as van de lijn zal kapot gaan
uint16_t	explosieGrootte;
uint8_t		rangeBomb = 12;

void		tekenBom(uint8_t xLocatie, uint8_t yLocatie);
void		tekenOntploffing(uint8_t xLocatie, uint8_t yLocatie);
void		bomOpruimen(uint8_t xLocatie, uint8_t yLocatie);
void		tekenOpruiming(uint8_t xLocatie, uint8_t yLocatie);
boolean		bomstatusSpeler2;
void		DropBomb(int speler);//een methode die bijna alle methodes van de bom gebruikt. wanneer het ontploft wordt.

//
enum bomcooldownsEnTiming {
	cooldownBomLimiet = 10,
	aftellenTotExplosieBomLimiet = 70,
	aftellenTotOpruimingBom =30
};

//om aan te geven welke as de bom van de lijn is. Wordt gebruikt van welke kant van de X as
//Het is gebasseerd op "WASD" voor het geval je je afvraagt waarom deze waardes.
enum bomLijnAs
{
	xAsRechts = 'd',
	xAsLinks = 'a',
	yAsBoven = 'w',
	yAsOnder = 's'
};

enum IRcommandos {
	verzendBom =5,
	verzendSpelerOmhoog=1,
	verzendSpelerOmlaag=2,
	verzendSpelerNaarRechts=3,
	verzendSpelerNaarLinks =4,
	cooldownBewegenSpeler = 3
};

protected:
private:


};


#endif

