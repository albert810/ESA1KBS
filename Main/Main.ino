/*
 Name:		Main.ino
 Created:	11/16/2017 1:22:40 PM
 Author:	Albert
*/
#include "Communication.cpp"
#include "Communication.h"
#include <GraphicsLib.h>
#include <DS1307.h>
#include <ArduinoNunchuk.h>
#include <Wire.h>
#include <MI0283QT9.h>
#include "Hoofdmenu.h"
#include <wiring_private.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "Hoofdmenu.cpp"

volatile uint8_t teller = 0;
int counter = 0;
Communication c;

void setup()
{
	/*c.enableTimer1();

	
	// set timer 1 prescale factor to 64
	sbi(TCCR1B, CS10);
	sbi(TCCR1B, CS12);
	// put timer 1 in 8-bit phase correct pwm mode
	sbi(TCCR1A, WGM10);
	*/
	
}


void loop()
{
	
}

/*
ISR(TIMER1_COMPA_vect)
{
	counter++;
	if (counter >= 60) {
		//Serial.println("een seconde");
		Serial.println("hai");
		counter = 0;
	}
	
}*/