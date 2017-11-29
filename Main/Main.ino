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
#include <wiring_private.h>


Communication c;
int counter = 0;
hoofdmenuu h;
int bomafgaan = 0;
int toetsen = 0;
main() {
	Serial.begin(9600);
	init();
	
	c.enableTimer1();
	// set timer 1 prescale factor to 64
	sbi(TCCR1B, CS10);
	sbi(TCCR1B, CS12);
	// put timer 1 in 8-bit phase correct pwm mode
	sbi(TCCR1A, WGM10);

	
	
	


	h.hoofdmenusetup();

	while (1)
	{
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

