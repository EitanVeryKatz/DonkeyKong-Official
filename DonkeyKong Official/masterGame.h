#pragma once
#include "player.h"
#include "boardGame.h"
class masterGame
{
	static constexpr int CAUSE_SIZE = 5;
	static constexpr int MAX_SCORE = 10000;
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
	bool firstGame = true;
	std::vector<std::string> boardFileNames;

	const std::string CausesOfFailStrings[CAUSE_SIZE] = {
		"BC", // Barrel Collision
		"BE", // Barrel Explosion
		"GC", // Ghost Collision
		"FD", // Fall to Death
		"OB"  // Out of Bounds
	};

	int iterationCounter = 0;
	void updateScore(int points) {
		score += points;
		needsRedraw = true;
	}
	void initGame(player& mario, boardGame& board); // Initialize the game
	virtual void initialDraw(player& mario, boardGame& board) = 0; // Draw the initial board
	virtual void handleInput(player& mario) = 0; // Handle user input
	void updateNPCs(int iterationCounter, boardGame& board);
	void handleBarrelSpawn(boardGame& board, int iterationCounter);
	virtual void gameLoop(player& mario, boardGame& board); // Main game loop

	void resetLives() { lives = 3; } // Reset the number of lives
	void resetScore() { score = 0; }
	virtual void fail(player& mario, bool& running, boardGame& board, int& barrelCounter, int& iterationCounter); // Handle player fail
	virtual	void win(player& mario, bool& running, boardGame& board); // Handle player win
	
	
	virtual void getAllBoardFiles();
	virtual void runGame(const std::string& fileName); // Run the game
	
	void drawLegend(boardGame& b) const;
	masterGame(const std::string state = "-");
public:
	void displayMenu(); // Display the game menu
	void writeResFile(bool won, const std::string& fileName, int cause = -1) const;
	 
	virtual ~masterGame();
};

