#include "Ladder.h"
#include <iostream>

void Ladder::drawLadder(int mY, int MY) // sets the y values of ladders and drwa it on board
{
	minY = mY;
	maxY = MY;
	for (int i = minY; i <= maxY; i++)
	{
		gotoxy(X, i);
		std::cout << LADDER_ICON;
	}
}


