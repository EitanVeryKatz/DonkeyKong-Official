#pragma once
#include "player.h"
#include "boardGame.h"

class game
{

	int lives = 3;
	int activeBarrels = 0;
	int maxBarrels;
	void initGame(player& mario, boardGame& board); // Initialize the game
	void handleInput(player& mario); // Handle user input
	void updateBarrels(boardGame& board, int& barrelCounter, int iterationCounter); // Update barrels
	void gameLoop(player& mario, boardGame& board); // Main game loop
	void printMenu(); // Print the game menu
	void printInstructions(); // Print the game instructions
	void setDiffculty(); // Print the game diffculty options
	void resetLives() { lives = 3; } // Reset the number of lives
	void fail(player& mario, bool &running, boardGame& board, int & barrelCounter, int &iterationCounter); // Handle player fail
public:
	void pauseGame(); // Pause the game
	void displayMenu(); // Display the game menu
	void runGame(); // Run the game
	void playFailSong();
	game(); // Constructor
};

