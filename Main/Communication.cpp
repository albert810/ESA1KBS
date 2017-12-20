// 
// 
// 


#include "Communication.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define IRONTVANGPIN      PINB
#define IRPINNUM          0
#define MAXONTV 2000

uint16_t pulses[100][2];  // 2 array's voor hoge en lage pulsen 
uint8_t currentpulse = 0; // houdt bij hoeveel pulsen er in 1 array zitten
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
		PORTB |= (1 << PORTB3);       // high ~1ms
		delayMicroseconds(10);         // 12ms
		PORTB &= ~(1 << PORTB3);           // low ~1ms
		delayMicroseconds(10);         // 12ms


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


	int * list = new int;
	list[4];
	for (int i = 0; i <= 4; i++) {
		list[i] = bitIsFalse;
	}


	//Elke bit van het object bij langs gaan, als hij 1 is dan komt het getal 100
	for (int i = 0; i <= 4; i++) {
		if (object & (1 << i)) {
			list[i] = bitIsTrue;
		}

	}

	return list;

}

void Communication::sendSingleData(int object)
{
	//als hij ooit een keer raar doet dan ligt het aan de malloc
	//int * listOfCommands = new int;
	int *listOfCommands = (int*)malloc(8 * sizeof(listOfCommands));
	/*Er wordt een array van 5 groot gemaakt van tijdsintervallen die aangeven of een bit 1 of 0 is
	1 = 300
	0 = 100
	*/
	listOfCommands = this->prepareDataCommands(object);

	//TODO:pulsen verzenden testen en timen 
	//startbit
	pulseIR(400);
	delayMicroseconds(200);

	for (int i = 0; i <= 4; i++) {
		Serial.println(listOfCommands[i]);
		pulseIR(listOfCommands[i]);
		delayMicroseconds(100);
	}
	//stopbit
	pulseIR(400);
	free(listOfCommands);
}

void Communication::testPulses() {
	pulseIR(300);
	delayMicroseconds(200);
	pulseIR(100);
	delayMicroseconds(200);
	pulseIR(300);
	delayMicroseconds(200);
	pulseIR(100);
	delayMicroseconds(200);
	pulseIR(300);
	Serial.println("pulse");



}


//=====================FUNCTIES ONTVANGER=======================================




void Communication::readPulses() {


	uint16_t highpulse, lowpulse, byteValue;  // tijdelijke opslag pulseduur en byte waarde
	highpulse = lowpulse = 0; // begin bij nul


	while (IRONTVANGPIN & (1 << IRPINNUM)) {
		// pin is hoog
		highpulse++;


		//wanneer tijd tussen pulsen langer is dan de maximale luistertijd(MAXONTV)
		//print of verstuurt de ontvanger de array van de pulsen die wel ontvangen zijn
		//vanaf dat moment is de array klaar en vormt een byte
		//onderscheid tussen byte's wordt dus op deze manier bepaald
		if ((highpulse >= MAXONTV) && (currentpulse != 0)) {
			convertByte();
			//printPulses();
			currentpulse = 0;
			return;
		}
	}
	// we didn't time out so lets stash the reading
	pulses[currentpulse][0] = highpulse;

	// zelfde while als bovenstaande maar dan met lowpulse(pulsen die daadwerkelijk gelezen worden)
	while (!(IRONTVANGPIN & _BV(IRPINNUM))) {
		// pin is laag
		lowpulse++;

		if ((lowpulse >= MAXONTV) && (currentpulse != 0)) {
			convertByte();
			//printPulses();
			currentpulse = 0;
			return;
		}
	}
	pulses[currentpulse][1] = lowpulse;

	// een hoog-laag puls gelezen, programma leest verder.

	currentpulse++;

}



void Communication::convertByte() {
	uint16_t factor, byteValue;
	factor = 1; // byte komt achterstevoren binnen dus lezen begint bij de LSB
	byteValue = 0; //tellen begint bij 0


	for (uint8_t i = 1; i < 5; i++) {
		if (pulses[i][1] > 350) {
			byteValue += factor;
			factor *= 2;
		}
		else {
			factor *= 2;
		}

	}
	Serial.print(byteValue);


}
//printfuncties voor de ontvangen byte's
//alle pulsen hoger dan 500 worden 1
//alles daaronder wordt een 0
//500 omdat dit is wat binnenkomt als de verzender een 1(300) verstuurd
//kan later gebruikt worden voor dataverwerking
void Communication::printPulses(void) {

	for (uint8_t i = 0; i < currentpulse; i++) {

		//if(pulses[i][1] > 500 && pulses[i][1] < 600){
		//Serial.print("1");


		//} else{
		//Serial.print("0");
		//}
		Serial.print(pulses[i][1]);
		Serial.println(" usec");
	}
	//}
	count++;
	//Serial.println("\nno");
	Serial.println(count);
}