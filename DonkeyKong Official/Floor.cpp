#include "Floor.h"


void Floor::drawFloor() const
{
	gotoxy(xStart, y);
	for (size_t i = xStart; i < xEnd; i++)
	{
		std::cout << dir;
	}
}
