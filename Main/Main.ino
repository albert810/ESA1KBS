/*
Name:		Main.ino
Created:	11/16/2017 1:22:40 PM
Author:	Albert
*/

#include <MI0283QT9.h>
#include "LevelMenu.h"
#include "Bom.h"
#include "PageState.h"
#include "Poppetje.h"
#include "Locatie.h"
#include "Speelveld.h"
#include "Communication.h"
#include "Hoofdmenu.h"
#include <avr\interrupt.h>


PageState pagestate;//een pagestate voor het aanmaken
Communication c;//voor het aanzetten van de interrupt
hoofdmenuu h;//de hoofdmenu aanmaken

uint8_t counter = 0; // deze counter is speciaal voor de interrupt. Deze counter telt het aantal bitjes wat binnenkomt
uint8_t pos = 0;	//wat het resultaat is van het ontvangen IR signaal
enum ontvangenIRdata {

	IRomhoog=1,
	IRomlaag=2,
	IRrechts=3,
	IRlinks=4,
	IRbom=5
};

main() {
	init();
	Serial.begin(9600);
    PORTD |= (1 << PORTD3);//aanzetten van pin 3 interupt
	c.initInterrupt();//aanzetten van interupt
	h.setPageState(pagestate);
	h.hoofdmenusetup();
	


	while (1)
	{			
		//in het begin zit het programma in de hoofdmenu
		if (h.pageState.hoofdmenu)
			h.hoofdmenuloop();

		//wanneer vanaf het hoofdemenu de levelmenu is geselecteerd gaat het programma over naar het levelmenu
		if (h.levelmenu.pageState.levelmenu) {
			h.levelmenu.levelloop(h.lcd, h.nunchuk);
		}

		//wanneer het de level geselecteerd is begint het spel
		if (h.levelmenu.speelveld.spelersZijnIngesteld) {
			h.levelmenu.speelveld.verplaatsPoppetje();
			h.levelmenu.speelveld.tekenVerplaatsingPoppetje();
			h.levelmenu.speelveld.DropBomb(1);//checkt steeds of de bom is ingedrukt voor speler 1 of speler 2

		}
		//wanneer het spel afgelopen is gaat het programma naar een status die terug kan naar de menu
		if (h.levelmenu.speelveld.backToMainMenu)
		{
			h.levelmenu.speelveld.backToMainMenoLoop();
			if (h.levelmenu.speelveld.enableMainMenu)
			{
				h.levelmenu.speelveld.resetValuesOfTheGame();
				h.levelmenu.speelveld.enableMainMenu = 0;
				h.levelmenu.speelveld.backToMainMenu = 0;
				h.hoofdmenusetup();
				h.pageState.hoofdmenu = 1;

			}
		}
	}
}


//timer die reageert op hardware
ISR(INT1_vect) {
    Serial.println("");
	c.readPulses2();
	counter++;
	//wanneer hij alle vijf bits ontvangen heeft
	if (counter == 5) {
		pos = c.convertByte();
		if (pos == IRomhoog) {
			h.levelmenu.speelveld.speler2.yLocatie--;
			h.levelmenu.speelveld.vorigelocatieSpeler2 = h.levelmenu.speelveld.omhoog;//omhoog

		} 
		else if (pos == IRomlaag) {
			h.levelmenu.speelveld.speler2.yLocatie++;
			h.levelmenu.speelveld.vorigelocatieSpeler2 = h.levelmenu.speelveld.omlaag;//omlaag

		}
		else if (pos == IRrechts) {
			h.levelmenu.speelveld.speler2.xLocatie++;
			h.levelmenu.speelveld.vorigelocatieSpeler2 = h.levelmenu.speelveld.rechts;//rechts

		}
		else if (pos == IRlinks) {
			h.levelmenu.speelveld.speler2.xLocatie--;
			h.levelmenu.speelveld.vorigelocatieSpeler2 = h.levelmenu.speelveld.links;//links

		}
		else if (pos == IRbom) {
			h.levelmenu.speelveld.bomstatusSpeler2 = 1;
		}
		counter = 0;
	}
}