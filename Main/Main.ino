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
#include "Hoofdmenu.cpp"
#include <avr\interrupt.h>


PageState pagestate;
Communication c;
hoofdmenuu h;
int counter = 0;


main() {
	init();
	Serial.begin(9600);
	//c.enableTimer1();

	h.setPageState(pagestate);
	h.hoofdmenusetup();

	while (1)
	{
		if (h.pageState.hoofdmenu)
			h.hoofdmenuloop();

		if (h.levelmenu.pageState.levelmenu) {
			h.levelmenu.levelloop(h.lcd, h.nunchuk);
		}

		if (h.levelmenu.speelveld.spelersZijnIngesteld) {
			h.levelmenu.speelveld.verplaatsPoppetje();
			h.levelmenu.speelveld.tekenVerplaatsingPoppetje();
			h.levelmenu.speelveld.DropBomb(1);//checkt steeds of de bom is ingedrukt voor speler 1 vandaar die 1

		}

	}
}

//links is rechts -------rechts is links


//timer die reageert op hardware
//hier moet nog een klasse etc van gemaakt worden
ISR(TIMER1_COMPA_vect)
{
	//bom 
	




}

