/*
Name:		Main.ino
Created:	11/16/2017 1:22:40 PM
Author:	Albert
*/

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
	c.enableTimer1();

	h.setPageState(pagestate);
	h.hoofdmenusetup();

	while (1)
	{	
		if (h.pageState.hoofdmenu) 
			h.hoofdmenuloop();

		if (h.speelveld.spelersZijnIngesteld) {
			h.speelveld.verplaatsPoppetje();
			delay(100);
			h.speelveld.tekenVerplaatsingPoppetje();
		}
		
	}
}

//links is rechts -------rechts is links


//timer die reageert op hardware
//hier moet nog een klasse etc van gemaakt worden
ISR(TIMER1_COMPA_vect)
{

}

