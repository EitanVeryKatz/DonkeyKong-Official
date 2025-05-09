﻿#include "game.h"
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
			
			initGame(mario, board); // initialize the game
		}
	}
}

void game::win(player& mario, bool& running, boardGame& board)
{
	updateScore(1000);
	running = false; // end the game
	if (level == static_cast<int>(boardFileNames.size()) || singleGame)
	{
		system("cls"); // clear the screen
		gotoxy(MessageX, MessageY);
		printWinningMessage(); // display the winning message

		// Calculate the position to center the score
		std::string scoreMessage = "Your final score is: " + std::to_string(score);
		int centerX = static_cast<int>((BOARD_WIDTH - scoreMessage.length()) / 2);
		int centerY = BOARD_HEIGHT / 2;

		gotoxy(centerX, centerY + 5); // Move to the calculated position
		std::cout << scoreMessage; // display the score

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
						level++;
					}
					if (singleGame)
					{
						runGame(fileName); // run the game
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
			std::cout << "One or more objects on board are invalid trying next board!";
		else
			std::cout << "One or more objects on board are invalid! returning to menu";
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
	board.initActiveBoard(); // initialize the active board
	needsRedraw = true;
	clear_key_buffer(); // clear the input buffer
	activeBarrels = 0; // reset the number of active barrels
	board.initFailChart(); // initialize the fail chart
	board.initBarrels();  // initialize the barrels
	if (!firstGame)
		board.resetGhosts();
	mario.setGameBoard(&board); // set the board of the player
	mario.resetPlayer(); // reset player's position
	if(firstGame && board.wasHammerLocationSetInBoard())
		mario.setHammerLocation(board.getStartHammerX(), board.getStartHammerY());
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

void game::gameLoop(player& mario, boardGame& board)
{
	bool running = true;
	int barrelCounter = 0; 
	int iterationCounter = 0;
	while (running) // main game loop
	{
		if (needsRedraw)
		{
			drawLegend(board);
		}
		mario.draw(); // draw the player
		if (!mario.doeshasHammer()) {
			gotoxy(mario.getHammerX(), mario.getHammerY());
			std::cout << 'p';
		}

		if(mario.isSwingingHammer())
			mario.clearHammerSwing();

		handleInput(mario); // handle the user input
		updateNPCs(iterationCounter, board);
		Sleep(GAME_SPEED);
		iterationCounter++;
		mario.checkHasHmmer();
		fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure
		if (!running) // after fail break the loop if player failed
			break;
		if (mario.checkWin()) // if the player won
			win(mario, running, board); // handle player win
		mario.erase(); // erase the player
		mario.move(); // move the player
		mario.inLegend(needsRedraw);
		mario.draw(); // draw the player
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

/// @brief Retrieves all board files from the current directory.
/// This function iterates through the current directory and collects all files
/// that start with "board" and have a ".screen" extension. The collected file names
/// are stored in the boardFileNames vector. The vector is then sorted in alphabetical order.
void game::getAllBoardFiles()
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		auto fileName = entry.path().filename();
		auto fileNameStr = fileName.string();
		if (fileNameStr.substr(0,6) == "dkong_" && fileName.extension() == ".screen")
		{
			boardFileNames.push_back(fileNameStr);
		}
		boardFileNames.shrink_to_fit();
		std::sort(boardFileNames.begin(), boardFileNames.end());
	}
}

/// @brief Displays the board selection menu and allows the user to choose a board.
/// This function presents a paginated list of available board files to the user.
/// The user can navigate through the pages using 'a' and 'd' keys and select a board
/// by pressing the corresponding numeric key. The user can also choose to play all boards
/// or return to the menu by pressing the ESC key.
/// @param fileName Reference to a string where the chosen board file name will be stored.
void game::printAndChooseBoard(string& fileName)
{
    const int boardsPerPage = 9; // Keep 9 to display 9 screens per page
    int currentPage = 0;
    int totalPages = (static_cast<int>(boardFileNames.size()) + boardsPerPage - 2) / (boardsPerPage - 1); // Adjust total pages calculation
    bool redrawRequired = true; // Flag to control screen redraw
    while (true)
    {
        if (redrawRequired) // Only redraw the screen when needed
        {
            system("cls");
			if (!boardFileNames.empty()) // Check if there are board files available
            {
                printBoardOptions(currentPage, boardsPerPage, totalPages);
            }
			else // No board files found in the directory display a message and return to the menu
            {
				string message = "No board files found! returning to menu.";
                int centerX = (BOARD_WIDTH - static_cast<int>(message.length())) / 2; 
                gotoxy(centerX, MessageY);
				std::cout << message << std::endl;
				Sleep(breakTime);
                return;
            }

            redrawRequired = false; // Redraw done, no need to redraw again until triggered
        }

        // Handle user input
        if (_kbhit())
        {
            char key = _getch();

            // Handle numeric keys for selecting a board
            if (key >= '1' && key <= '9')
            {
                int option = key - '1';

                if (currentPage == 0 && option == 0) // "1" to play all boards
                {
                    fileChosen = true;
                    singleGame = false;
                    return;
                }

                int index = currentPage * (boardsPerPage - 1) + (currentPage == 0 ? (option - 1) : option);

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
                redrawRequired = true; // Trigger screen redraw
            }
            else if (key == 'd' && currentPage < totalPages - 1)
            {
                currentPage++;
                redrawRequired = true; // Trigger screen redraw
            }
            else if (key == ESC) // ESC key
            {
                fileChosen = false;
                return;
            }
        }
    }
}

/// @brief Prints the board options for the user to choose from.
/// This function displays a list of available board files, allowing the user to select one.
/// It also provides navigation instructions for moving between pages of board options.
/// @param currentPage The current page number being displayed.
/// @param boardsPerPage The number of boards to display per page.
/// @param totalPages The total number of pages available.
void game::printBoardOptions(int currentPage, int boardsPerPage, int totalPages) const
{
	const int centerX = 35; // Adjust as needed for your console width
	std::cout << std::string(centerX - 10, ' ') << "Choose a board from the list below:\n" << std::endl;

	// Calculate the start and end indices for the current page
	int start = currentPage * (boardsPerPage - 1);
	int end = min(start + (currentPage == 0 ? (boardsPerPage - 1) : boardsPerPage), (int)boardFileNames.size());

	// Special option for playing all boards on the first page
	if (currentPage == 0)
	{
		std::cout << std::string(centerX - 10, ' ') << "1) Play all boards in order" << std::endl;
	}

	// Display the options for the current page
	for (int i = start; i < end; ++i)
	{
		std::cout << std::string(centerX - 10, ' ') << (currentPage == 0 ? (i - start + 2) : (i - start + 1)) << ") " <<
			boardFileNames[i] << std::endl;
	}

	// Indicate navigation instructions
	if (totalPages > 1)
		std::cout << std::string(centerX - 10, ' ') <<
			"\nPress 'a' for previous page, 'd' for next page, or ESC to return to the menu\n" << std::endl;

	// Display the current page number
	std::cout << std::string(centerX - 10, ' ') << "Page " << (currentPage + 1) << " of " << totalPages << std::endl;
}

void game::drawLegend(boardGame& b) const
{
	int lx = b.getLx(),ly = b.getLy();
	gotoxy(lx, ly);
	std::cout << "Lives: " << lives << std::endl;
	gotoxy(lx, ly + 1);
	std::cout << "Score: " << score << std::endl;
}


void game::updateScore(int points)
{
	score += points;
	if (score > MAX_SCORE)
	{
		score = MAX_SCORE;
	}
	needsRedraw = true;
}


/// @brief Updates the state of all NPCs (non-player characters) in the game.
/// This function iterates through the vector of NPCs and updates their state.
/// If an NPC is active, it calls its update method. If the NPC becomes inactive
/// and is a barrel, it handles the barrel's explosion and removes it from the vector.
/// If the NPC is not a barrel, it simply removes it from the vector.
/// The function also handles the spawning of new barrels at regular intervals.
/// @param iterationCounter The current iteration count of the game loop.
/// @param board Reference to the boardGame object containing the NPCs.
void game::updateNPCs(int iterationCounter, boardGame& board)
{
	auto& npcVector = board.getNPCVector();
	for (std::vector<npc*>::iterator itr = npcVector.begin(); itr != npcVector.end();)
	{
		npc* pNPC = *itr;
		if (pNPC->isActive())
		{
			pNPC->update(score, needsRedraw);
			pNPC->inLegend(needsRedraw);
			if (pNPC->isActive())
			{
				++itr;
			}
			else if (barrel* pBarrel = dynamic_cast<barrel*>(pNPC))
			{
				if (!pBarrel->isBlastShowing())
				{
					delete pNPC;
					itr = npcVector.erase(itr);
				}
				activeBarrels--;
			}
			else
			{
				delete pNPC;
				itr = npcVector.erase(itr);
			}
		}
		else
		{
			if (barrel* pBarrel = dynamic_cast<barrel*>(pNPC))
			{
				pBarrel->expHandler();
			}
			++itr;
		}
	}
	if (board.getValidBarrelSpawningPos()) // if there are not any valid position to spawn on the board it will not spawn any barrels
		handleBarrelSpawn(board, iterationCounter);
}

void game::handleBarrelSpawn(boardGame& board, int iterationCounter)
{
	if (iterationCounter % BARREL_SPAWN_RATE == 0 && activeBarrels < maxBarrels)
	{
		barrel* pBarrel = new barrel(board.getMonkeY());
		pBarrel->setGameBoard(&board);
		pBarrel->resetBarrel();
		pBarrel->draw();
		board.getNPCVector().push_back(pBarrel);
		activeBarrels++;
	}
}
