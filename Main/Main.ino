/*
Name:		Main.ino
Created:	11/16/2017 1:22:40 PM
Author:	Albert
*/

#include "Game.h"
#include "Communication.h"
#include "Hoofdmenu.h"

main() {
	init();
	hoofdmenuu h;
	h.hoofdmenusetup();
	while (1)
	{
		h.hoofdmenuloop();
	}
}