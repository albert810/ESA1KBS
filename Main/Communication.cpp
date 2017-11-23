// 
// 
// 


#include "Communication.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define IRRECV_PIN PIND
#define IRRECV 2
#define MAXLISTEN 400
#define RESOLUTION 10
uint16_t pulses[100][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing
int count = 0;

Communication::Communication() {


}

void Communication::pulseIR(long microsecs)
{
	cli();  // this turns off any background interrupts
			//8 en 11 doen het
	DDRB |= (1 << DDB3); //pin 11 output

	while (microsecs > 0) {
		// 38 kHz = 13 microseconds high and 13 microseconds low
		PORTB |= (1 << PORTB3);       // high 3ms
		delayMicroseconds(10);         // 10ms
		PORTB &= ~(1 << PORTB3);           // low 3ms
		delayMicroseconds(10);         // 10ms


									   // so 26 microseconds altogether
		microsecs -= 26;
	}

	sei();  // this turns them back on
	
}

void Communication::enableTimer1()
{
	cli();          // disable global interrupts
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B

					// set compare match register to desired timer count:
	OCR1A = 15624;

	// turn on CTC mode:
	TCCR1B |= (1 << WGM12);

	// Set CS10 and CS12 bits for 1024 prescaler:
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);

	// enable timer compare interrupt:
	TIMSK1 |= (1 << OCIE1A);

	// enable global interrupts:
	sei();

}

int* Communication::prepareDataCommands(int object)
{

	//maak lege lijst en zorg er voor dat (voor het bericht) de bit op  0 staat dus op false
	int *list= new int;
	list[4] ;
	for (int i = 0; i <= 4; i++) {
		list[i] = bitIsFalse;
	}
	

	//Elke bit van het object bij langs gaan, als hij 1 is dan komt het getal 100
	for (int i = 0; i <= 4; i++){
		if (object & (1 << i)) {
			list[i] = bitIsTrue;
		}
		
	}
	
	return list;

}

void Communication::sendSingleData(int object)
{
	int * listOfCommands = new int;

/*Er wordt een array van 4 groot gemaakt van tijdsintervallen die aangeven of een bit 1 of 0 is 
1 = 100
0 = 200
*/
	listOfCommands = this->prepareDataCommands(object);

	//TODO:pulsen verzenden testen en timen 
	for (int i = 0; i <= 4; i++) {
		pulseIR(listOfCommands[i]);
	}

	
}

//=====================FUNCTIES ONTVANGER=======================================
void Communication::initReceiver() {

	Serial.begin(9600);
	Serial.println("READY");

}

void Communication::readPulse() {
	uint16_t hipulse, lowpulse;
	hipulse = lowpulse = 0;

	while (IRRECV_PIN & (1 << IRRECV)) {
		hipulse++;
		delayMicroseconds(RESOLUTION);
		//als de puls te lang duurt of als er niets ontvangen is
		if ((hipulse >= MAXLISTEN) && (currentpulse != 0)) {
			currentpulse = 0;
			
			return;
		}
	}
	pulses[currentpulse][0] = hipulse;

	while (!(IRRECV_PIN & _BV(IRRECV))) {
		lowpulse++;
		delayMicroseconds(RESOLUTION);
		if ((lowpulse >= MAXLISTEN) && (currentpulse != 0)) {
			currentpulse = 0;
			return;
		}

	}
	pulses[currentpulse][1] = lowpulse;
	
	//hi-low puls combinatie gelezen, kan verder
	printPulses();
	currentpulse++;
}
void Communication::printPulses() {
	for (uint8_t i = 0; i < currentpulse; i++) {

		if (pulses[i][1] * RESOLUTION > 400 && pulses[i][1] * RESOLUTION < 600) {
			Serial.println("1");
		}
		else {
			Serial.println("0");
		}
		count++;
		Serial.println(count);
	}
}
