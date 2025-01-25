#include "automatic_game.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "player.h"
#include "boardGame.h"
#include "gameConfig.h"
#include <sstream>

void automatic_game::resetStepsVec()
{
	for (auto& step : steps)
	{
		delete step;
	}
	steps.clear();
}

automatic_game::~automatic_game()
{
	resetStepsVec();
	if (resFile)
	{
		resFile->close();
		delete resFile;
	}
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
	
    std::getline(stepsFile, line);
    if (line.empty()) 
	{
    std::cout << "ERROR: invalid file format" << std::endl;
    return;
    }
	int seed = std::stoi(line);
	srand(seed);
    std::getline(stepsFile, line);
    if (line.empty()) 
	{
    std::cout << "ERROR: invalid file format" << std::endl;
    return;
    }
    maxBarrels = std::stoi(line);

    std::getline(stepsFile, line);
    if (line.empty()) 
	{
    std::cout << "ERROR: invalid file format" << std::endl;
    return;
    }
    gamesPlayedInOrder = std::stoi(line);
	if (!gamesPlayedInOrder)
	{
		resetLives();
		resetScore();
	}
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
	stepsFile.close();
}

void automatic_game::handleInput(player& mario)
{
	std::vector<key_and_time*>::iterator itr = steps.begin();
	if (itr != steps.end())
	{
		if ((*itr)->time == iterationCounter)
		{
			mario.keyPressed((*itr)->key, silent);
			itr = steps.erase(itr);
		}
	}
}

void automatic_game::win(player& mario, bool& running, boardGame& board)
{
	updateScore(1000);
	running = false;
	cmpToResFile();
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
			if (!silent)
				system("cls");
			cmpToResFile(cause);
		}
		else
		{
			firstGame = false;
			if (!silent)
			{
				Sleep(100); // wait for 100 ms to see failing cause of the player otherwise it will be too fast
				system("cls"); // clear the screen
				gotoxy(MessageX, MessageY);
				std::cout << "You have " << lives << " lives left" << std::endl; // display the message
				Sleep(breakTime);
			}
			cmpToResFile(cause);
			barrelCounter = 0;
			iterationCounter = 0;
			initGame(mario, board); // initialize the game
		}
	}
}

void automatic_game::initGame(player& mario, boardGame& board)
{
	iterationCounter = 0;
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
	if (!silent)
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
	for (size_t i = 0; i < stepsFileNames.size(); i++, level++)
	{
		std::string stepsFileName = stepsFileNames[i];
		int boardIndex = find_board_file_for_step_file(stepsFileName);
		if (boardIndex != -1)
		{
			loadSteps(stepsFileName);
			std::string resFileName = stepsFileNames[i].substr(0, stepsFileNames[i].find_last_of('.')) + ".result";
			resFile = new std::ifstream(resFileName);
			if (!resFile->is_open())
			{
				std::cout << "ERROR: unable to open result file" << std::endl;
				Sleep(breakTime);
				return;
			}
			runGame(boardFileNames[boardIndex]);
			if (resCmp)
			{
				system("cls");
				std::cout << "screen " << i + 1 << " match the result file" << std::endl;
				Sleep(breakTime);
			}
			else
			{
				system("cls");
				std::cout << "screen " << i + 1 << " does not match the result file" << std::endl;
				Sleep(breakTime);
			}
		}
		else
		{
			std::cout << "No board file found for " << stepsFileName << std::endl;
			Sleep(breakTime);
		}
		resFile->close();
		delete resFile;
		resFile = nullptr;
		if (!gamesPlayedInOrder)
			resetLives();
	}
	system("cls");
	gotoxy(0, 0);
	displayRes();
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
		if (needsRedraw && !silent)
		{
			drawLegend(board);
		}
		if (!silent)
			mario.draw(); // draw the player
		if (!mario.doeshasHammer() && !silent) {
			gotoxy(mario.getHammerX(), mario.getHammerY());
			std::cout << 'p';
		}

		if (mario.isSwingingHammer())
			mario.clearHammerSwing();

		handleInput(mario); // handle the user input
		updateNPCs(iterationCounter, board);
		if (!silent)
			Sleep(GAME_SPEED -40);
		iterationCounter++;
		mario.checkHasHmmer();
		fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure
		if (!running) // after fail break the loop if player failed
			break;
		if (mario.checkWin()) // if the player won
			win(mario, running, board); // handle player win
		if (!silent)
		{
			mario.erase(); // erase the player
			mario.inLegend(needsRedraw);
			mario.draw(); // draw the player
		}
		mario.move(silent); // move the player
		fail(mario, running, board, barrelCounter, iterationCounter); // handle player failure after movement
		std::fflush(stdin); // clear the input buffer
	}
}

void automatic_game::updateNPCs(int iterationCounter, boardGame& board)
{
	auto& npcVector = board.getNPCVector();
	for (std::vector<npc*>::iterator itr = npcVector.begin(); itr != npcVector.end();)
	{
		npc* pNPC = *itr;
		if (pNPC->isActive())
		{
			pNPC->update(score, needsRedraw, silent);
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

void automatic_game::handleBarrelSpawn(boardGame& board, int iterationCounter)
{
	if (iterationCounter % BARREL_SPAWN_RATE == 0 && activeBarrels < maxBarrels)
	{
		barrel* pBarrel = new barrel(board.getMonkeY());
		pBarrel->setGameBoard(&board);
		pBarrel->resetBarrel();
		if (!silent)
			pBarrel->draw();
		board.getNPCVector().push_back(pBarrel);
		activeBarrels++;
	}
}

void automatic_game::drawLegend(boardGame& b) const
{
	int lx = b.getLx(), ly = b.getLy();
	gotoxy(lx, ly);
	std::cout << "Lives: " << lives << std::endl;
	gotoxy(lx, ly + 1);
	std::cout << "Score: " << score << std::endl;
}

automatic_game::automatic_game(const std::string state)
{
	showCurserOnConsole(false);
	if (state == "-silent")
		silent = true;
}

void automatic_game::cmpToResFile(const int& cause) 
{
	int res_itr , res_lives , res_score ;
	char res_cond;
	std::string res_cause;
	std::string resLine;
	
	std::getline(*resFile, resLine);
	if (resLine.empty())
	{
		resCmp = false;
		return;
	}
	getResLine(res_itr, res_cond, res_lives, res_score, res_cause, resLine);

	if (cause != -1) // if cause not -1 it means the player failed
	{
		if (res_itr != iterationCounter || res_cond != 'f' || res_lives != lives || res_score != score || res_cause != CausesOfFailStrings[cause])
			resCmp = false;
	}
	else // if the player won
	{
		if (res_itr != iterationCounter || res_cond != 'w' || res_lives != lives || res_score != score)
			resCmp = false;
	}
}

void automatic_game::getResLine(int& res_itr, char& res_cond, int& res_lives, int& res_score,
	std::string& res_cause, const std::string& resLine) const
{
	std::stringstream ss(resLine);
	std::string segment;
	std::getline(ss, segment, ':');
	res_itr = std::stoi(segment);
	std::getline(ss, segment, ':');
	res_cond = segment[0];
	std::getline(ss, segment, ':');
	res_lives = std::stoi(segment);
	std::getline(ss, segment, ':');
	res_score = std::stoi(segment);
	std::getline(ss, segment, ':');
	res_cause = segment;
}

void automatic_game::displayRes() const
{
	if (resCmp)
		std::cout << "The results are the same!" << std::endl;
	else
		std::cout << "The results are different!" << std::endl;
}
