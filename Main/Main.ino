/*
Name:		Main.ino
Created:	11/16/2017 1:22:40 PM
Author:	Albert
*/

#include "Poppetje.h"
#include "Locatie.h"
#include "Speelveld.h"
#include "Communication.h"
#include "Hoofdmenu.h"
#include <avr\interrupt.h>



Communication c;
int counter = 0;
hoofdmenuu h;
int bomafgaan = 0;
int toetsen = 0;
main() {
	Serial.begin(9600);
	init();
	
	c.enableTimer1();


	
	
	
	
	//c.sendSingleData(3);

	h.hoofdmenusetup();

	while (1)
	{
		//c.readPulses();
		h.hoofdmenuloop();
		
	}
}




//timer die reageert op hardware
//hier moet nog een klasse etc van gemaakt worden
ISR(TIMER1_COMPA_vect)
{
	if (h.speelveld.spelersZijnIngesteld) {



		toetsen++;
		if (toetsen == 10) {
			//nunchucktoetsbom
			if (h.nunchuk.zButton) {
				bomafgaan = 1;
				h.speelveld.speler1.dropBomb();
				Serial.println("bom op de grond gooien");
				h.nunchuk.zButton = 0;
			}
			toetsen = 0;
		}


		if (bomafgaan) {
			counter++;
			if (counter == 180) {
				Serial.println("bom ontploft");
				h.speelveld.speler1.removeBomb();
				h.speelveld.speler1.drawPoppetje(h.speelveld.speler1.currentXLocation, h.speelveld.speler1.currentYlocation);
				bomafgaan = 0;
				counter = 0;
			}

		}

	}
	
}

