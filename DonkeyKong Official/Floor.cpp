//#include "Floor.h"
//#include "Ladder.h"
//#include <cstdlib>
//
//void Floor::randDir()
//{
//	int ranNum = randomBit(); // random number between 0 - 1
//	dir = FLOOR_DIR[ranNum];
//}
//
//void Floor::drawFloor() const
//{
//	gotoxy(xStart, y);
//	if (dir == FLOOR_DIR[LEFT]) // if is left draw first the arrow then the =
//	{
//		std::cout << getDir();
//		for (size_t i = xStart + 1; i <= xEnd; i++)
//		{
//			gotoxy(i, y);
//			std::cout << FLOOR_ICON;
//		}
//	}
//	else // else draw at first = and at the end >
//	{
//		for (size_t i = xStart; i < xEnd; i++)
//		{
//			gotoxy(i, y);
//			std::cout << FLOOR_ICON;
//		}
//		gotoxy(xEnd, y);
//		std::cout << getDir();
//	}
//}
//
//void Floor::initLadders() 
//{
//	(dir == '<') ? LadderArr[0].updateX(60): LadderArr[0].updateX(13);
//	LadderArr[0].drawLadder(y - 2, y - 1);
//}
