// Communication.h

#ifndef _COMMUNICATION_h
#define _COMMUNICATION_h

class Communication
{
public:
	Communication();
	void pulseIR(long microsecs);
	void enableTimer1();
	int* prepareDataCommands(int object);
	void sendSingleData(int object);
	void testPulses();
	void initInterrupt();
	void initReceiver();
	void readPulses();
	void readPulses2();
	void convertByte();
	void printPulses();
	void testVoorAlbert();
	enum bitIdentity {

		bitIsTrue = 300,
		bitIsFalse = 100,
		

	};

protected:



private:
	
};

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

