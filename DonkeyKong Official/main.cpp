#include <iostream>
#include <windows.h>
#include <conio.h>
#include "gameConfig.h"
#include "player.h"
#include "boardGame.h"
#include "barrel.h"


constexpr int ESC = 27;

//int main()
//{
//	showCurserOnConsole(false);
//	player mario;
//	boardGame board;
//	mario.setGameBoard(&board);
//	board.newDrawBoard();
//	board.startBarrelSequence();
//	while (true)
//	{
//		board.updateBarrels();
//
//		mario.draw();
//		if (_kbhit())
//		{
//			char key = _getch();
//			if (key == ESC)
//				break;
//			mario.keyPressed(key);
//		}
//
//		Sleep(160);
//		mario.erase();
//		mario.moveInBoard();
//	}
//	gotoxy(0, 27);
//}


int main()
{
    showCurserOnConsole(false);
    player mario;
    boardGame board;
    mario.setGameBoard(&board);
    board.newDrawBoard();
    board.startBarrelSequence();
    while (true)
    {
        // Erase mario and barrels
        mario.erase();
        board.eraseBarrels();

        // Update positions
        mario.moveInBoard();
        board.updateBarrels();

        // Draw board elements that might have been erased
        board.reDrawOriginal();

        // Draw mario and barrels
        mario.draw();
        board.drawBarrels();

        if (_kbhit())
        {
            char key = _getch();
            if (key == ESC)
                break;
            mario.keyPressed(key);
        }

        Sleep(160);
    }
    gotoxy(0, 27);
}