#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

constexpr int ESC = 27;

void game::runGame()
{
	player mario;
	boardGame board;
	initGame(mario, board);
	gameLoop(mario, board);
}

void game::initGame(player& mario, boardGame& board)
{
	showCurserOnConsole(false);
	mario.setGameBoard(&board);
	board.newDrawBoard();
}

void game::handleInput(player& mario, bool& running)
{
	if (_kbhit())
	{
		char key = _getch();
		if (key == ESC)
			running = false;
		else
			mario.keyPressed(key);
	}
}

void game::updateBarrels(boardGame& board, int& barrelCounter, int numBarrels, int iterationCounter)
{
	for (int i = 0; i < barrelCounter; i++)
	{
		barrel* pBarrel = &board.getBarrel(i);
		if (board.getBarrel(i).isActive())
		{
			pBarrel->erase();
			pBarrel->barrelFall();
			pBarrel->draw();
		}
		else
		{
			if (pBarrel->isBlastShowing())
			{
				if (pBarrel->getBlowCount() == 2)
				{
					pBarrel->clearBlast();
				}
				else
				{
					pBarrel->updateBlowCounter();
				}
			}
		}
	}
	if (iterationCounter % 20 == 0 && barrelCounter < numBarrels)
	{
		barrel* pBarrel = &board.getBarrel(barrelCounter);
		pBarrel->setBoard(&board);
		pBarrel->draw();
		barrelCounter++;
	}
}

void game::gameLoop(player& mario, boardGame& board)
{
	bool running = true;
	int barrelCounter = 0;
	int iterationCounter = 0;
	while (running)
	{
		mario.draw();
		handleInput(mario, running);
		updateBarrels(board, barrelCounter, board.getBarrelsNum(), iterationCounter);
		Sleep(100);
		iterationCounter++;
		mario.erase();
		mario.moveInBoard();
	}
}
