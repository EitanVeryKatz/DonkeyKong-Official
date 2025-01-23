#include "automatic_game.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "player.h"
#include "boardGame.h"
#include "gameConfig.h"

void automatic_game::resetStepsVec()
{
	for (auto& step : steps)
	{
		delete step;
	}
	steps.clear();
}

void automatic_game::getAllStepsFiles()
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		auto fileName = entry.path().filename();
		auto fileNameStr = fileName.string();
		if (fileNameStr.substr(0, 6) == "dkong_" && fileName.extension() == ".steps")
		{
			stepsFileNames.push_back(fileNameStr);
		}
		stepsFileNames.shrink_to_fit();
		std::sort(stepsFileNames.begin(), stepsFileNames.end());
	}
}

void automatic_game::getAllBoardFiles()
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		auto fileName = entry.path().filename();
		auto fileNameStr = fileName.string();
		if (fileNameStr.substr(0, 6) == "dkong_" && fileName.extension() == ".screen")
		{
			boardFileNames.push_back(fileNameStr);
		}
		boardFileNames.shrink_to_fit();
		std::sort(boardFileNames.begin(), boardFileNames.end());
	}
}

void automatic_game::loadSteps(const std::string& fileName)
{
	resetStepsVec();
	std::ifstream stepsFile(fileName);
	if (!stepsFile.is_open())
	{
		std::cout << "ERROR: unable to open file" << std::endl;
		return;
	}

	std::string line;
	// Skip the first line
	std::getline(stepsFile, line);
	std::getline(stepsFile, line);
	maxBarrels = std::stoi(line);

	while (!stepsFile.eof())
	{
		std::getline(stepsFile, line);
		if (!line.empty())
		{
			auto colonPos = line.find(':');
			if (colonPos != std::string::npos)
			{
				key_and_time *temp = new key_and_time;
				std::string itr_string = line.substr(0, colonPos);
				temp->time = std::stoi(itr_string);
				temp->key = line[colonPos + 1];
				steps.push_back(temp);
			}
		}
	}
}

void automatic_game::handleInput(player& mario)
{
	std::vector<key_and_time*>::iterator itr = steps.begin();
	while (itr != steps.end())
	{
		if ((*itr)->time == iterationCounter)
		{
			mario.keyPressed((*itr)->key);
		}
	}
}

void automatic_game::win(player& mario, bool& running, boardGame& board)
{
	updateScore(1000);
	running = false;
	if (level == static_cast<int>(boardFileNames.size()) || singleGame)
	{
		system("cls");
		//TODO: check the res file
	}
}

void automatic_game::fail(player& mario, bool& running, boardGame& board, int& barrelCounter, int& iterationCounter)
{
	size_t cause;
	if (mario.checkFail(cause))
	{
		lives--;
		if (lives == 0)
		{
			running = false;
			lost = true;
			system("cls");
			//TODO: check the res file
		}
		else
		{
			firstGame = false;
			if (!statesFlags[SILENT])
			{
				Sleep(100); // wait for 100 ms to see failing cause of the player otherwise it will be too fast
				system("cls"); // clear the screen
				gotoxy(MessageX, MessageY);
				std::cout << "You have " << lives << " lives left" << std::endl; // display the message
				Sleep(breakTime);
			}
			barrelCounter = 0, iterationCounter = 0;

			initGame(mario, board); // initialize the game
		}
	}
}

void automatic_game::initGame(player& mario, boardGame& board)
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
	if (firstGame && board.wasHammerLocationSetInBoard())
		mario.setHammerLocation(board.getStartHammerX(), board.getStartHammerY());
	if (!statesFlags[SILENT])
	{
		board.newDrawBoard(); // draw the board
		mario.drawHammer(); // draw the hammer
	}
}

void automatic_game::fileManager()
{
	getAllBoardFiles();
	getAllStepsFiles();
	if (boardFileNames.empty())
	{
		std::cout << "No board files found!" << std::endl;
		Sleep(breakTime);
		return;
	}
	if (stepsFileNames.empty())
	{
		std::cout << "No steps files found!" << std::endl;
		Sleep(breakTime);
		return;
	}
	for (size_t i = 0; i < stepsFileNames.size(); i++)
	{
		std::string stepsFileName = stepsFileNames[i];
		int boardIndex = find_board_file_for_step_file(stepsFileName);
		if (boardIndex != -1)
		{
			loadSteps(stepsFileName);
			runGame(boardFileNames[boardIndex]);
		}
		else
		{
			std::cout << "No board file found for " << stepsFileName << std::endl;
			Sleep(breakTime);
		}
	}
}

int automatic_game::find_board_file_for_step_file(const std::string& stepFileName)
{
	int index = -1;
	std::string boardFileName = stepFileName.substr(0, stepFileName.find_last_of('.')) + ".screen";
	for (size_t i = 0; i < boardFileNames.size(); i++)
	{
		if (boardFileNames[i] == boardFileName)
		{
			index = i;
			break;
		}
	}
	return index;
}

void automatic_game::runGame(const std::string& fileName)
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

void automatic_game::gameLoop(player& mario, boardGame& board)
{
	bool running = true;
	int barrelCounter = 0;
	iterationCounter = 0;
	while (running) // main game loop
	{
		if (needsRedraw && !statesFlags[SILENT])
		{
			drawLegend(board);
		}
		mario.draw(); // draw the player
		if (!mario.doeshasHammer()) {
			gotoxy(mario.getHammerX(), mario.getHammerY());
			std::cout << 'p';
		}

		if (mario.isSwingingHammer())
			mario.clearHammerSwing();

		handleInput(mario); // handle the user input
		updateNPCs(iterationCounter, board);
		if (!statesFlags[SILENT])
			Sleep(GAME_SPEED);
		iterationCounter++;
		mario.checkHasHmmer();
		fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure
		if (!running) // after fail break the loop if player failed
			break;
		if (mario.checkWin()) // if the player won
			win(mario, running, board); // handle player win
		if (!statesFlags[SILENT])
		{
			mario.erase(); // erase the player
			mario.move(); // move the player
			mario.inLegend(needsRedraw);
			mario.draw(); // draw the player
		}
		fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure after movement
		std::fflush(stdin); // clear the input buffer
	}
}

automatic_game::automatic_game(const std::string state)
{
	if (state == '-silent')
		statesFlags[SILENT] = true;
	fileManager();
}
