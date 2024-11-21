#include "Floor.h"


void Floor::drawFloor()
{
	gotoxy(this->xStart, this->y);
	for (size_t i = this->xStart; i < this->xEnd; i++)
	{
		std::cout << this->dir;
	}
}
