#include "Floor.h"
#include <cstdlib>

void Floor::randDir()
{
	int ranNum = rand() % 3; // random number between 0 - 2
	dir = FLOOR_DIR[ranNum];
}

void Floor::drawFloor() const
{
	gotoxy(xStart, y);
	for (size_t i = xStart; i < xEnd; i++)
	{
		std::cout << dir;
	}
}

void Floor::initLadders()
{

}
