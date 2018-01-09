// Communication.h

#ifndef _COMMUNICATION_h
#define _COMMUNICATION_h

class Communication
{
public:
	Communication();

	void pulseIR(long microsecs);
	void enableTimer1();
	void sendSingleData(int object);
	void testPulses();
	void initInterrupt();
	void readPulses();
	void readPulses2();
	void printPulses();

	int* prepareDataCommands(int object);
	int convertByte();
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

