// 
// 
// 

#include "Locatie.h"
//==============constructor==================
Location::Location()
{
}

//==================getters en setters================

int Location::getXLocation()
{
	return this->XLocation;
}

int Location::getYLocation()
{
	return this->YLocation;
}

void Location::setLocationX(int x)
{
	this->XLocation = x;
}

void Location::setLocationY(int y)
{
	this->YLocation = y;
}
