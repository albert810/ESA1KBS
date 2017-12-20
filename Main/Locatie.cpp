// 
// 
// 

#include "Locatie.h"
//==============constructor==================
Location::Location()
{
}

int Location::vanLocationNummerNaarX(int locatienummer)
{
	/*
	double num = 23.345;
	int intpart = (int)num;
	double decpart = num - intpart;
	printf("Num = %f, intpart = %d, decpart = %f\n", num, intpart, decpart);
	*/
	double locatieDouble = locatienummer*1.0;
	locatieDouble = (locatieDouble / 16)+1;
	int intpart = (int)locatieDouble;
	double decpart = locatieDouble - intpart;
	
	//Serial.println(decpart*16);

	return decpart*16;
}

int Location::vanLocationNummerNaarY(int locatienummer)
{
	int result = locatienummer / 16 + 1;
	return result;
}

//==================getters en setters================

