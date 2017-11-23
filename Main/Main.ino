/*
Name:		Main.ino
Created:	11/16/2017 1:22:40 PM
Author:	Albert
*/

#include "Communication.h"
#include "Hoofdmenu.h"

main() {
	init();
	hoofdmenuu h;
	Serial.begin(9600);
	h.hoofdmenusetup();
	while (1)
	{
		h.hoofdmenuloop();
	}
}