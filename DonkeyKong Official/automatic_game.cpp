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

/**
 * @brief Retrieves all step files in the current directory.
 * 
 * This function iterates through the current directory and collects all files 
 * that have a filename starting with "dkong_" and an extension of ".steps". 
 * The collected filenames are stored in the stepsFileNames vector. 
 * The vector is then sorted in ascending order.
 */
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



/**
 * @brief Loads the steps from a given file.
 * 
 * This function reads a file containing steps for the game. It initializes the 
 * random seed, maximum number of barrels, and the order of games played. It also 
 * parses the steps and stores them in the steps vector.
 * 
 * @param fileName The name of the file containing the steps.
 */
void automatic_game::loadSteps(const std::string& fileName)
{
	resetStepsVec();
	std::ifstream stepsFile(fileName);
	if (!stepsFile.is_open())
	{
		std::cout << "ERROR: unable to open steps file" << std::endl;
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

/**
 * @brief Handles the input for the player in automatic mode.
 * 
 * This function iterates through the steps vector and checks if the current 
 * iteration counter matches the time for the next step. If it does, it simulates 
 * a key press for the player and removes the step from the vector.
 * 
 * @param mario The player object that will receive the input.
 */
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

/**
 * @brief Handles the player's failure in the game.
 * 
 * This function checks if the player has failed. If the player has failed, it decreases the number of lives.
 * If the player has no lives left, it stops the game and compares the result with the expected result.
 * If the player still has lives left, it reinitializes the game and displays the remaining lives.
 * 
 * @param mario The player object.
 * @param running A boolean indicating if the game is running.
 * @param board The game board object.
 * @param barrelCounter The counter for the barrels.
 * @param iterationCounter The counter for the iterations.
 */
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



void automatic_game::initialDraw(player& mario, boardGame& board) {
	if (!silent) {
		board.newDrawBoard(); // draw the board
		mario.drawHammer(); // draw the hammer
	}
}

/**
 * @brief Manages the game files and runs the game.
 * 
 * This function retrieves all board and step files, checks for their existence,
 * and iterates through each step file to load the steps and corresponding board file.
 * It then runs the game and compares the results with the expected results.
 * If no board or step files are found, it displays an appropriate message and returns.
 */
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
        int boardIndex = findBoardFile(stepsFileName);
        if (boardIndex != -1)
        {
            loadSteps(stepsFileName);
            std::string resFileName = stepsFileNames[i].substr(0, stepsFileNames[i].find_last_of('.')) + ".result";
            resFile = new std::ifstream(resFileName);
            if (!resFile->is_open())
            {
                std::cout << "ERROR: unable to open result file trying the next one" << std::endl;
                Sleep(breakTime);
                continue;
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

int automatic_game::findBoardFile(const std::string& stepFileName) const
{
	int notFound = -1;
	std::string boardFileName = stepFileName.substr(0, stepFileName.find_last_of('.')) + ".screen";
	for (size_t i = 0; i < boardFileNames.size(); i++)
	{
		if (boardFileNames[i] == boardFileName)
			return i;
	}
	return notFound;
}



/**
 * @brief Main game loop for automatic mode.
 * 
 * This function runs the main game loop for the automatic mode. It handles drawing the player,
 * processing user input, updating NPCs, checking for player failure or win conditions, and moving the player.
 * The loop continues running until the player either wins or fails.
 * 
 * @param mario The player object.
 * @param board The game board object.
 */


void automatic_game::handleNPCDraw(npc* pNPC) {
	if (!silent)
		pNPC->draw();
}



automatic_game::automatic_game(const std::string state)
{
	showCurserOnConsole(false);
	if (state == "-silent")
		silent = true;
}


/**
* @brief Compares the current game state with the expected result from the result file.
* 
* This function reads a line from the result file and parses it to extract the expected 
* iteration counter, condition (win or fail), number of lives, score, and cause of failure.
* It then compares these values with the current game state. If any of the values do not match,
* the function sets the resCmp flag to false.
* 
* @param cause The cause of failure, if any. If the player failed, this parameter should be 
*              the index of the failure cause in the CausesOfFailStrings array. If the player 
*              won, this parameter should be -1.
*/
void automatic_game::cmpToResFile(const size_t& cause) 
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


/**
 * @brief Parses a result line from the result file.
 * 
 * This function takes a result line from the result file and extracts the iteration counter,
 * condition (win or fail), number of lives, score, and cause of failure. It uses a stringstream
 * to split the line by colons and convert the segments to the appropriate data types.
 * 
 * @param res_itr Reference to an integer to store the iteration counter.
 * @param res_cond Reference to a char to store the condition (win or fail).
 * @param res_lives Reference to an integer to store the number of lives.
 * @param res_score Reference to an integer to store the score.
 * @param res_cause Reference to a string to store the cause of failure.
 * @param resLine The result line from the result file.
 */
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
