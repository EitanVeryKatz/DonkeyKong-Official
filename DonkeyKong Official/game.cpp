#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "gameConfig.h"


constexpr int ESC = 27;
constexpr int breakTime = 2000;
constexpr int MessageX = 30, MessageY = 12;

game::game()
{
	displayMenu();
}

void game::fail(player& mario, bool& running, boardGame& board, int& barrelCounter, int& iterationCounter)
{
	if (mario.checkFail()) // if the player failed
	{
		lives--; // decrement the number of lives
		if (lives == 0) // if no more lives
		{
			Sleep(100); // wait for 100 ms to see failing cause of the player otherwise it will be too fast
			running = false; // end the game
			system("cls"); // clear the screen
			printFailMessage(); // display the fail message
			playFailSong();
			Sleep(breakTime);
			system("cls"); // clear the screen
			return;
		}
		else // if there are more lives
		{
			Sleep(100); // wait for 100 ms to see failing cause of the player otherwise it will be too fast
			system("cls"); // clear the screen
			gotoxy(MessageX, MessageY);
			std::cout << "You have " << lives << " lives left" << std::endl; // display the message
			Sleep(breakTime);
			barrelCounter = 0, iterationCounter = 0;
			std::fflush(stdin); // clear the input buffer
			initGame(mario, board); // initialize the game
		}
	}
}

void game::win(player& mario, bool& running, boardGame& board)
{
	running = false; // end the game
	system("cls"); // clear the screen
	gotoxy(MessageX, MessageY);
	printWinningMessage(); // display the winning message
	playWinningSong();
	Sleep(breakTime);
	system("cls"); // clear the screen
}

void game::displayMenu()
{
	showCurserOnConsole(false);
	printMenu(); // print the menu
	while (true) // menu loop
	{
		if (_kbhit()) // if the user pressed a key
        {
			char key = _getch(); // get the key
			if (key == '1') // if the user pressed '1'
            {
				setDifficulty(); // set the diffculty
				runGame(); // run the game
				resetLives(); // reset the number of lives after the game ends
				printMenu(); // print the menu
            }
			else if (key == '8')
			{
				system("cls");
				printInstructions(); // print the instructions
				(void)_getch(); // wait for any key
				printMenu(); // print the menu
				continue; // continue to the next iteration
			}
			else if (key == '9')
			{
				system("cls");
				gotoxy(MessageX, MessageY);
				std::cout << "Goodbye!" << std::endl;
				Sleep(breakTime); 
				break; // exit the loop
			}
        }
		 Sleep(100);
	}
}

void game::runGame()
{
	player mario; // create a player
	boardGame board; // create a board
	initGame(mario, board); // initialize the game
	gameLoop(mario, board); // run the game loop
}



void game::initGame(player& mario, boardGame& board)
{
	activeBarrels = 0; // reset the number of active barrels
	board.initFailChart(); // initialize the fail chart
	board.initBarrels();  // initialize the barrels
	mario.setGameBoard_USING_POINT(&board); // set the board of the player
	mario.resetPlayer(); // reset player's position
	board.newDrawBoard(); // draw the board
}

void game::handleInput(player& mario)
{
	if (_kbhit()) // if the user pressed a key
	{
		char key = _getch(); // get the key
		if (key == ESC) // if the user pressed 'esc'
		{
			pauseGame(); // pause the game
		}
		else
			mario.keyPressed_USING_POINT(key); // handle the key
	}
}

void game::updateBarrels(boardGame& board, int& barrelCounter, int iterationCounter)
{
	for (int i = 0; i < barrelCounter; i++) // update all barrels
	{
		barrel& pBarrel = board.getBarrel(i); // get the barrel

		if (pBarrel.isActive()) // if barrel is active
		{
			pBarrel.erase_USING_POINT(); // erase the barrel
			pBarrel.barrelFall_USING_POINT(); // make the barrel fall
			if (pBarrel.isActive())
				pBarrel.draw_USING_POINT(); // draw the barrel
			else
				activeBarrels--; // decrement the number of active barrels
		}
		else if (!pBarrel.isActive() && activeBarrels < maxBarrels && !pBarrel.isBlastShowing()) // if the barrel is not active and there are less than the maximum number of barrels and the barrel is not exploding
		{
			pBarrel.resetBarrel_USING_POINT(); // reset the barrel
			activeBarrels++; // increment the number of active barrels
		}
			


		
		if (pBarrel.isBlastShowing()) // if the barrel is exploding
		{
			if (pBarrel.getBlowCount() == 2) // if the explosion is over
			{
				pBarrel.clearBlast(); // clear the explosion
				activeBarrels--; // decrement the number of active barrels

			}
			else if(pBarrel.getBlowCount() == 1)//if explosion ongoing
			{
				pBarrel.explode();//continue explosion
				pBarrel.updateBlowCounter(); // update the explosion counter
				
			}//if explosion just began on this iteration
			else {
				pBarrel.updateBlowCounter();//update the explosion counter
			}
		}
			
	}
	if (iterationCounter % BARREL_SPAWN_RATE == 0 && barrelCounter < BARRELS_NUM && barrelCounter < maxBarrels) // if it's time to add a new barrel and there are less than the maximum number of barrels
		{
			barrel* pBarrel = &board.getBarrel(barrelCounter); // get the next barrel
			pBarrel->draw_USING_POINT(); // draw the barrel
			barrelCounter++; // increment the barrel counter
			activeBarrels++; // increment the number of active barrels
		}
	}


void game::gameLoop(player& mario, boardGame& board)
{
	const int livesX = 9, livesY = 2;
	bool running = true;
	int barrelCounter = 0; 
	int iterationCounter = 0;
	while (running) // main game loop
	{
		gotoxy(livesX, livesY);
		std::cout << lives << std::endl;
		mario.draw_USING_POINT(); // draw the player
		handleInput(mario); // handle the user input
		updateBarrels(board, barrelCounter, iterationCounter); // update the barrels
		Sleep(GAME_SPEED);
		iterationCounter++;
		fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure
		if (!running) // after fail break the loop if player failed
			break;
		if (mario.checkWin()) // if the player won
			win(mario, running, board); // handle player win
		mario.erase_USING_POINT(); // erase the player
		mario.moveInBoard_USING_POINT(); // move the player
		mario.draw_USING_POINT(); // draw the player
		fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure after movement
	}
}



void game::pauseGame()
{
	const int messageX = 2;
	const int messageY = 2;
	gotoxy(messageX, messageY);
	std::cout << "Press 'esc' to resume the game" << std::endl; // display the pause message
	while (true) // pause loop
	{
		if (_kbhit()) // if the user pressed a key
		{
			char key = _getch(); // get the key
			if (key == ESC) // if pressed ESC resume the game
			{
				gotoxy(messageX, messageY); 
				std::cout << "                              " << std::endl; // clear the message
				gotoxy(messageX + 1, messageY);
				std::cout << "Lives:";
				break;
			}
		}
		Sleep(100);
	}
}

void game::setDifficulty()
{
	system("cls");
	int centerX = 27; // Assuming the console width is 80
	int centerY = 11; // Assuming the console height is 25
	gotoxy(centerX, centerY - 2);
	std::cout << "Chose the difficulty level:" << std::endl;
	gotoxy(centerX, centerY);
	std::cout << "1. Easy" << std::endl;
	gotoxy(centerX, centerY + 1);
	std::cout << "2. Medium" << std::endl;
	gotoxy(centerX, centerY + 2);
	std::cout << "3. Hard" << std::endl;
	std::cout << "\n";
	while (true)
	{
		if (_kbhit()) // if the user pressed a key
		{
			// set the difficulty according to the user's choice
			char key = _getch();
			if (key == '1')
			{
				maxBarrels = diffculty[LOW_DIFFCULTY];
				break;
			}
			else if (key == '2')
			{
				maxBarrels = diffculty[MEDIUM_DIFFCULTY];
				break;
			}
			else if (key == '3')
			{
				maxBarrels = diffculty[HIGH_DIFFCULTY];
				break;
			}
		}
	}
}





