#pragma once
#include "player.h"
#include "boardGame.h"
#include "utils.h"
#include "ghost.h"
#include <vector>
#include <string>
#include <algorithm>


class game
{	
	static constexpr int CAUSE_SIZE = 5;
	static constexpr int MAX_SCORE = 10000;
	bool save = false;
	int Seed;
	int lives = 3;
	int score = 0;
	int activeBarrels = 0;
	int maxBarrels;
	int firstScreen = 0;
	bool lost = false;
	bool singleGame = false;
	int level = 1;
	bool needsRedraw = true;
	std::ofstream* saveFile = nullptr;
	std::ofstream* resFile = nullptr;
	std::string currFileName;

	const std::string CausesOfFailStrings[CAUSE_SIZE] = {
		"BC", // Barrel Collision
		"BE", // Barrel Explosion
		"GC", // Ghost Collision
		"FD", // Fall to Death
		"OB"  // Out of Bounds
	};

	int iterationCounter = 0;
	void updateScore(int points);
	void initGame(player& mario, boardGame& board); // Initialize the game
	void handleInput(player& mario); // Handle user input
	void updateNPCs(int iterationCounter, boardGame &board);
	void handleBarrelSpawn(boardGame& board, int iterationCounter);
	void gameLoop(player& mario, boardGame& board); // Main game loop
	void setDifficulty(); // Print the game diffculty options
	void resetLives() { lives = 3; } // Reset the number of lives
	void resetScore() { score = 0; }
	void fail(player& mario, bool &running, boardGame& board, int & barrelCounter, int &iterationCounter); // Handle player fail
	void win(player& mario, bool& running, boardGame& board); // Handle player win
	bool firstGame = true;
	std::vector<std::string> boardFileNames;
	void getAllBoardFiles();
	void runGame(const std::string& fileName); // Run the game
	void pauseGame(); // Pause the game
	void printAndChooseBoard(std::string& fileName);
	bool fileChosen = false;
	void printBoardOptions(int currentPage, int boardsPerPage, int totalPages) const;
	void drawLegend(boardGame& b) const;
	void saveState(char key);
	void closeSaveFile();
public:
	void displayMenu(); // Display the game menu
	void writeResFile(bool won, const std::string& fileName, int cause = -1) const;
	game(const std::string state = "-");
	~game()
	{
		closeSaveFile();
	}
};

