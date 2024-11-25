#include <iostream>
#include <windows.h>
#include <conio.h>
#include "gameConfig.h"
#include "player.h"
#include "Floor.h"
#include "boardGame.h"



constexpr int ESC = 27;

int main()
{
	showCurserOnConsole(false);
	player mario;
	boardGame board;
	mario.setGameBoard(&board);
	board.initFloors();
	board.newDrawBoard();

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

		Sleep(100);
		mario.erase();
		mario.moveInBoard(board);
	}
}