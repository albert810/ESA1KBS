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
	void initReceiver();
	void readPulse();
	void printPulses();
	enum bitIdentity {
		
		bitIsTrue = 100,
		bitIsFalse = 200,
		stopBit = 300

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

