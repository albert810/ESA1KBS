// 
// 
// 

#include "PageState.h"

PageState::PageState()
{
	this->hoofdmenu = 1;
}

void PageState::setHoofdMenu(boolean state)
{
	this->hoofdmenu = state;
}

void PageState::setGame(boolean state)
{
	this->game = state;
}

void PageState::setLevelmenu(boolean state)
{
	this->levelmenu = state;
}
