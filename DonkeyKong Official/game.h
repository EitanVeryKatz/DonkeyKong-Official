#pragma once
#include "player.h"
#include "boardGame.h"

class game
{
	static constexpr int BARREL_SPAWN_RATE = 20;
	void initGame(player& mario, boardGame& board); // Initialize the game
	void handleInput(player& mario, bool& running); // Handle user input
	void updateBarrels(boardGame& board, int& barrelCounter, int numBarrels, int iterationCounter); // Update barrels
	void gameLoop(player& mario, boardGame& board); // Main game loop
public:
	void pauseGame(); // Pause the game
	void displayMenu(); // Display the game menu
	void runGame(); // Run the game
};

