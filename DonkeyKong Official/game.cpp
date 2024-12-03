﻿#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

constexpr int ESC = 27;

game::game()
{
	displayMenu();
}

void game::displayMenu()
{
	std::cout << R"( 
		    ____   ___  _   _ _  _________   __
			|  _ \ / _ \| \ | | |/ / ____\ \ / /
			| | | | | | |  \| | ' /|  _|  \ V / 
			| |_| | |_| | |\  | . \| |___  | |  
			|____/_\___/|_|_\_|_|\_\_____| |_|  
			| |/ / _ \| \ | |/ ___|             
			| ' / | | |  \| | |  _              
			| . \ |_| | |\  | |_| |             
			|_|\_\___/|_| \_|\____|             )" << std::endl;

	std::cout << "******************************************************************************" << std::endl;
	std::cout << "Chose from the options below by using the keyboard:" << std::endl;
	std::cout << "\n";
	std::cout << "1. Start Game" << std::endl;
	std::cout << "\n";
	std::cout << "8. Present instructions and keys" << std::endl;
	std::cout << "\n";
	std::cout << "9. Exit" << std::endl;
	std::cout << "\n";
	while (true) // menu loop
	{
		 if (_kbhit())
        {
            char key = _getch();
            if (key == '1')
            {
                runGame();
            }
			else if (key == '8')
			{
				system("cls");
				std::cout << "Instructions:" << std::endl;
				std::cout << "Use the 'a' key to move left,\n'd' key to move right,\n'w' key to jump or climb up a ladder,\n's' key to stop,\n'x' key to go down on ladder" << std::endl;
				std::cout << "Press 'esc' to pause the game\n" << std::endl;
				std::cout << "\n";
				std::cout << "Press any key to return to the menu" << std::endl;
				_getch();
				system("cls");
				displayMenu(); // any other way?
				break;
			}
			else if (key == '9')
			{
				break;
			}
        }
		 Sleep(100);
	}
}

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
	mario.resetPlayer();
	board.newDrawBoard();
	board.initBarrels();
}

void game::handleInput(player& mario, bool& running)
{
	if (_kbhit())
	{
		char key = _getch();
		if (key == ESC)
		{
			pauseGame();
		}
		else
			mario.keyPressed(key);
	}
}

void game::updateBarrels(boardGame& board, int& barrelCounter, int numBarrels, int iterationCounter)
{
	for (int i = 0; i < barrelCounter; i++) // update all barrels
	{
		barrel* pBarrel = &board.getBarrel(i);
		if (board.getBarrel(i).isActive()) // if barrel is active
		{
			pBarrel->erase(); // erase the barrel
			pBarrel->barrelFall(); // make the barrel fall
			pBarrel->draw(); // draw the barrel
		}
		else
		{
			if (pBarrel->isBlastShowing()) // if the barrel is exploding
			{
				if (pBarrel->getBlowCount() == 2) // if the explosion is over
				{
					pBarrel->clearBlast(); // clear the explosion
				}
				else
				{
					pBarrel->updateBlowCounter(); // update the explosion counter
				}
			}
		}
	}
	if (iterationCounter % BARREL_SPAWN_RATE == 0 && barrelCounter < numBarrels) // if it's time to add a new barrel
	{
		barrel* pBarrel = &board.getBarrel(barrelCounter); // get the next barrel
		pBarrel->draw(); // draw the barrel
		barrelCounter++; // increment the barrel counter
	}
}

void game::gameLoop(player& mario, boardGame& board)
{
	const int livesX = 2, livesY = 2, livesMessageX = 30, livesMessageY = 12;
	const int breakTime = 2000;
	bool running = true;
	int barrelCounter = 0;
	int iterationCounter = 0;
	while (running) // main game loop
	{
		gotoxy(livesX, livesY);
		std::cout << "Lives: " << lives << std::endl;
		mario.draw();
		handleInput(mario, running);
		updateBarrels(board, barrelCounter, board.getBarrelsNum(), iterationCounter);
		Sleep(100);
		iterationCounter++;
		if (mario.checkFail())
		{
			lives--;
			if (lives == 0)
			{
				running = false;
				system("cls");
				gotoxy(livesMessageX, livesMessageY);
				std::cout << "Game Over" << std::endl;
				Sleep(breakTime);
				displayMenu();
			}
			else
			{
				system("cls");
				gotoxy(livesMessageX, livesMessageY);
				std::cout << "You have " << lives << " lives left" << std::endl;
				Sleep(breakTime);
				initGame(mario, board);
			}
		}
		else if (mario.checkWin())
		{
			running = false;
			system("cls");
			gotoxy(livesMessageX, livesMessageY);
			std::cout << "You won!" << std::endl;
			Sleep(breakTime);
			displayMenu();
		}
		mario.erase();
		mario.moveInBoard();
	}
}

void game::pauseGame()
{
	const int messageX = 2;
	const int messageY = 2;
	gotoxy(messageX, messageY);
	std::cout << "Press 'esc' to resume the game" << std::endl;
	while (true)
	{
		if (_kbhit())
		{
			char key = _getch();
			if (key == ESC)
			{
				gotoxy(messageX, messageY);
				std::cout << "                              " << std::endl;
				break;
			}
		}
		Sleep(100);
	}
}
