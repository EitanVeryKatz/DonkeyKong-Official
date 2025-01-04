#pragma once
#include "player.h"
#include "boardGame.h"
#include "utils.h"
#include "ghost.h"
#include <vector>
#include <string>


class game
{
	int lives = 3;
	int score = 0;
	int activeBarrels = 0;
	int maxBarrels;
	int firstScreen = 0;
	void setfirstScreen(int index) { firstScreen = index; }
	void updateScore(int points);
	void initGame(player& mario, boardGame& board); // Initialize the game
	void handleInput(player& mario); // Handle user input
	void updateBarrels(boardGame& board, int& barrelCounter, int iterationCounter); // Update barrels
	void updateGhosts(boardGame& board);
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
public:
	void displayMenu(); // Display the game menu
	game() { getAllBoardFiles(); }
};

