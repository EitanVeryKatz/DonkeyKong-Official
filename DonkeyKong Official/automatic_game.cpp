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
