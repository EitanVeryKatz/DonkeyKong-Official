#include "Ladder.h"
#include <iostream>

void Ladder::drawLadder()
{
	for (size_t i = minY; i < maxY; i++)
	{
		gotoxy(X, i);
		std::cout << LADDER_ICON;
	}
}
