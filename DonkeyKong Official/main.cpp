#include <iostream>
#include <windows.h>
#include <conio.h>
#include "gameConfig.h"
#include "player.h"
#include "boardGame.h"
#include "barrel.h"


constexpr int ESC = 27;

int main()
{
	int barrelCounter = 0;
	showCurserOnConsole(false);
	player mario;
	boardGame board;
	mario.setGameBoard(&board);
	board.newDrawBoard();

	while (true)
	{
		if (barrelCounter == board.getBarrelCount() - 1)
		{
			// create new barrel array will add later
		}

		mario.draw();
		if (_kbhit())
		{
			char key = _getch();
			if (key == ESC)
				break;
			mario.keyPressed(key);
		}

		Sleep(160);
		//b.erase();
		//b.barrelFall();
		mario.erase();
		mario.moveInBoard();
	}
	gotoxy(0, 27);
}