#pragma once
#include "player.h"
#include "boardGame.h"

class game
{
	int lives = 3;
	static constexpr int BARREL_SPAWN_RATE = 20;
	void initGame(player& mario, boardGame& board); // Initialize the game
	void handleInput(player& mario); // Handle user input
	void updateBarrels(boardGame& board, int& barrelCounter, int numBarrels, int iterationCounter); // Update barrels
	void gameLoop(player& mario, boardGame& board); // Main game loop
	void printMenu(); // Print the game menu
	void printInstructions(); // Print the game instructions
	void resetLives() { lives = 3; } // Reset the number of lives
public:
	void pauseGame(); // Pause the game
	void displayMenu(); // Display the game menu
	void runGame(); // Run the game
	game(); // Constructor
};

