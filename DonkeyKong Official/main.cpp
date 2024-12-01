#include <iostream>
#include <windows.h>
#include <conio.h>
#include "gameConfig.h"
#include "player.h"
#include "boardGame.h"
#include "barrel.h"
#include "originalBoard.h"

constexpr int ESC = 27;

int main()
{
	int iterationCounter = 0;
	int barrelCounter = 0;
	showCurserOnConsole(false);
	player mario;
	boardGame board;
	originalBoard originalBoard;
	mario.setGameBoard(&board);
	mario.setOriginalBoard(&originalBoard);
	board.newDrawBoard();
	const int numBarrels = board.getBarrelsNum();
	while (true)
	{
		mario.draw();
		if (_kbhit())
		{
			char key = _getch();
			if (key == ESC)
				break;
			mario.keyPressed(key);
		}
		// update and draw each barrel
		for (int i = 0; i < barrelCounter; i++)
		{
			if (!board.getBarrel(i).isActive())
				continue;
			barrel* pBarrel = &board.getBarrel(i);
			pBarrel->erase();
			pBarrel->barrelFall();
			pBarrel->draw();
		}

		// add a new barrel every 60 iterations
		if (iterationCounter % 60 == 0 && barrelCounter < numBarrels)
		{
			barrel* pBarrel = &board.getBarrel(barrelCounter);
			pBarrel->setBoard(&originalBoard);
			pBarrel->draw();
			barrelCounter++;
		}
		Sleep(100);
		iterationCounter++;
		mario.erase();
		mario.moveInBoard();
	}
	gotoxy(0, 27);
}