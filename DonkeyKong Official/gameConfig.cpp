#include "gameConfig.h"
#include <iostream>
#include <algorithm>


class Floor;

void gotoxy(int x, int y)
{
	std::cout.flush();
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showCurserOnConsole(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

//void initGame()
//{
//	int iterationCounter = 0;
//	int barrelCounter = 0;
//	showCurserOnConsole(false);
//	player mario;
//	boardGame board;
//	originalBoard originalBoard;
//	mario.setGameBoard(&board);
//	mario.setOriginalBoard(&originalBoard);
//	board.newDrawBoard();
//	const int numBarrels = board.getBarrelsNum();
//	while (true)
//	{
//		mario.draw();
//		if (_kbhit())
//		{
//			char key = _getch();
//			if (key == ESC)
//				break;
//			mario.keyPressed(key);
//		}
//		// update and draw each barrel
//		for (int i = 0; i < barrelCounter; i++)
//		{
//			if (!board.getBarrel(i).isActive())
//				continue;
//			barrel* pBarrel = &board.getBarrel(i);
//			pBarrel->erase();
//			pBarrel->barrelFall();
//			pBarrel->draw();
//		}
//
//		// add a new barrel every 60 iterations
//		if (iterationCounter % 60 == 0 && barrelCounter < numBarrels)
//		{
//			barrel* pBarrel = &board.getBarrel(barrelCounter);
//			pBarrel->setBoard(&originalBoard);
//			pBarrel->draw();
//			barrelCounter++;
//		}
//		Sleep(100);
//		iterationCounter++;
//		mario.erase();
//		mario.moveInBoard();
//	}
//	gotoxy(0, 27);
//}


