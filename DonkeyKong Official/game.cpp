#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "gameConfig.h"
#include <filesystem>
#include <__msvc_filebuf.hpp>
#include <algorithm> 

using std::string;

constexpr int ESC = 27;
constexpr int breakTime = 2000;
constexpr int MessageX = 30, MessageY = 12;



void game::fail(player& mario, bool& running, boardGame& board, int& barrelCounter, int& iterationCounter)
{
	if (mario.checkFail()) // if the player failed
	{
		lives--; // decrement the number of lives
		if (lives == 0) // if no more lives
		{
			Sleep(100); // wait for 100 ms to see failing cause of the player otherwise it will be too fast
			running = false; // end the game
			lost = true;
			system("cls"); // clear the screen
			printFailMessage(); // display the fail message
			playFailSong();
			Sleep(breakTime);
			system("cls"); // clear the screen
			needToDraw = true;
			return;
		}
		else // if there are more lives
		{
			firstGame = false;
			Sleep(100); // wait for 100 ms to see failing cause of the player otherwise it will be too fast
			system("cls"); // clear the screen
			gotoxy(MessageX, MessageY);
			std::cout << "You have " << lives << " lives left" << std::endl; // display the message
			Sleep(breakTime);
			barrelCounter = 0, iterationCounter = 0;
			needToDraw = true;
			initGame(mario, board); // initialize the game
		}
	}
}

void game::win(player& mario, bool& running, boardGame& board)
{
	running = false; // end the game
	needToDraw = true;
	if (level == boardFileNames.size() || singleGame)
	{
		system("cls"); // clear the screen
		gotoxy(MessageX, MessageY);
		printWinningMessage(); // display the winning message
		playWinningSong();
		Sleep(breakTime);
		system("cls"); // clear the screen
	}
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
				string fileName;
				printAndChooseBoard(fileName); // print the board options
				if (fileChosen)
				{
					setDifficulty(); // set the diffculty
					lost = false;
					for (int i = 0; !singleGame && !lost && i < boardFileNames.size(); i++) // if the user chose to play all the boards play all boards
					{
						runGame(boardFileNames[i]); // run the game
						
						// TODO : maybe start with 5 lives and not reset lives between games
						level++;
						updateScore(1000);
					}
					if (singleGame)
					{
						runGame(fileName); // run the game
						if (!lost)
							updateScore(1000);
					}
				}
				resetLives(); // reset the number of lives after the game ends
				resetScore();
				level = 1;
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
				printGoodbyeMessage(); // print the goodbye message
				Sleep(breakTime);
				break; // exit the loop
			}
			else if (key == '2')
				debug = !debug;
        }
		 Sleep(100);
	}
}

void game::runGame(const std::string& fileName)
{
	boardGame board(fileName); // create a board
	board.setNewBoardFile(true); // flag that new file is loading
	if (!board.getOpen())
	{
		system("cls");
		gotoxy(MessageX, MessageY);
		std::cout << "ERROR: unable to open file";
		Sleep(breakTime);
		return;
	}
	if (!board.getValidity())
	{
		system("cls");
		gotoxy(MessageX - 20, MessageY);
		if (level != boardFileNames.size() && !singleGame)
			std::cout << "One or more objects on board are invallid trying next board!";
		else
			std::cout << "One or more objects on board are invallid! returning to menu";
		Sleep(breakTime);
		return;
	}
	player mario(board.getMarioStartX(), board.getMarioStartY()); // create a player
	initGame(mario, board); // initialize the game
	gameLoop(mario, board); // run the game loop
	board.setNewBoardFile(false); // when finished the game set the flag to false
}



void game::initGame(player& mario, boardGame& board)
{
	clear_key_buffer(); // clear the input buffer
	activeBarrels = 0; // reset the number of active barrels
	board.initFailChart(); // initialize the fail chart
	board.initBarrels();  // initialize the barrels
	if (!firstGame)
		board.resetGhosts();
	mario.setGameBoard(&board); // set the board of the player
	mario.setHemmerBoard(&board);
	mario.resetPlayer(); // reset player's position
	board.newDrawBoard(); // draw the board
	mario.drawHammer(); // draw the hammer
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
			mario.keyPressed(key); // handle the key
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
			if (pBarrel.isActive()) {
				pBarrel.draw_USING_POINT(); // draw the barrel
				if (pBarrel.wasSmashed()) {
					updateScore(100);
					pBarrel.resetSmash();
				}
			}
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

void game::updateGhosts(boardGame& board)
{
	for (std::vector<ghost>::iterator itr = board.getGhostsBegin(); itr != board.getGhostsEnd(); ++itr)
	{
		if (itr->isActive())
		{	
			itr->erase();
			itr->moveGhost();
			if (itr->isSmashed()) {
				updateScore(150);
				itr->resetSmashed();
			}
			itr->draw();
		}
	}
}


void game::gameLoop(player& mario, boardGame& board)
{
	bool running = true;
	int barrelCounter = 0; 
	int iterationCounter = 0;
	int legendX = board.getLx(), legendY = board.getLy();
	while (running) // main game loop
	{
		if (needToDraw)
		{
			gotoxy(legendX, legendY);
			std::cout << "Lives: " << lives << std::endl;
			gotoxy(legendX, legendY + 1);
			std::cout << "Score: " << score << std::endl;
			needToDraw = false;
		}

		mario.draw(); // draw the player
		if (!mario.doeshasHammer()) {
			gotoxy(mario.getHammerX(), mario.getHammerY());
			std::cout << 'p';
		}

		if(mario.isSwingingHammer())
			mario.clearHammerSwing();

		handleInput(mario); // handle the user input
		updateBarrels(board, barrelCounter, iterationCounter); // update the barrels
		updateGhosts(board);
		Sleep(GAME_SPEED);
		iterationCounter++;
		mario.checkHasHmmer();

		
		if (!debug)
			fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure
		if (!running) // after fail break the loop if player failed
			break;
		if (mario.checkWin()) // if the player won
			win(mario, running, board); // handle player win
		mario.erase(); // erase the player
		mario.moveInBoard(); // move the player
		mario.draw(); // draw the player
		if (!debug)
			fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure after movement
		std::fflush(stdin); // clear the input buffer
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
				needToDraw = true;
				break;
			}
		}
		Sleep(100);
	}
}

void game::setDifficulty()
{
	system("cls");
	int centerX = 27; 
	int centerY = 11; 
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

void game::getAllBoardFiles()
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		auto fileName = entry.path().filename();
		auto fileNameStr = fileName.string();
		if (fileNameStr.substr(0,5) == "board" && fileName.extension() == ".screen")
		{
			boardFileNames.push_back(fileNameStr);
		}
		boardFileNames.shrink_to_fit();
		std::sort(boardFileNames.begin(), boardFileNames.end());
	}
}

void game::printAndChooseBoard(string& fileName)
{
	const int boardsPerPage = 5;
	int currentPage = 0;
	int totalPages = (boardFileNames.size() + boardsPerPage - 1) / boardsPerPage;
	bool needsRedraw = true; // Flag to control screen redraw
	while (true)
	{
		if (needsRedraw) // Only redraw the screen when needed
		{
			system("cls");
			if (!boardFileNames.empty())
			{
				std::cout << "Choose a board from the list below:\n" << std::endl;

				// Calculate the start and end indices for the current page
				int start = currentPage * boardsPerPage;
				int end = min(start + boardsPerPage, (int)boardFileNames.size());

				// Special option for playing all boards on the first page
				if (currentPage == 0)
				{
					std::cout << "1) Play all boards in order" << std::endl;
				}

				// Display the options for the current page
				for (int i = start; i < end; ++i)
				{
					std::cout << (currentPage == 0 ? (i - start + 2) : (i - start + 1)) << ") " << boardFileNames[i] << std::endl;
				}

				// Indicate navigation instructions
				if (totalPages > 1)
					std::cout << "\nPress 'a' for previous page, 'd' for next page, or ESC to return to the menu\n" << std::endl;
			}
			else
			{
				std::cout << "No board files found! returning to menu." << std::endl;
				return;
			}

			needsRedraw = false; // Redraw done, no need to redraw again until triggered
		}

		// Handle user input
		if (_kbhit())
		{
			char key = _getch();

			// Handle numeric keys for selecting a board
			if (key >= '1' && key <= '5')
			{
				int option = key - '1';

				if (currentPage == 0 && option == 0) // "1" to play all boards
				{
					fileChosen = true;
					singleGame = false;
					return;
				}

				int index = currentPage * boardsPerPage + (currentPage == 0 ? (option - 1) : option);

				if (index >= 0 && index < boardFileNames.size()) // Check if the option corresponds to a valid index
				{
					fileName = boardFileNames[index];
					fileChosen = true;
					singleGame = true;
					return;
				}
			}
			// Navigate pages
			if (key == 'a' && currentPage > 0)
			{
				currentPage--;
				needsRedraw = true; // Trigger screen redraw
			}
			else if (key == 'd' && currentPage < totalPages - 1)
			{
				currentPage++;
				needsRedraw = true; // Trigger screen redraw
			}
			else if (key == 27) // ESC key
			{
				fileChosen = false;
				return;
			}
		}
	}
}




void game::updateScore(int points) {
	score += points;
}


