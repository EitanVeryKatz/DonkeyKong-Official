#pragma once
#include "player.h"
#include "boardGame.h"
#include <vector>
 constexpr int MessageX = 30, MessageY = 12;
 constexpr int breakTime = 2000;
class masterGame
{	
protected:
	static constexpr int CAUSE_SIZE = 5;
	static constexpr int MAX_SCORE = 10000;
	int Seed;
	int lives = 3;
	int score = 0;
	int maxBarrels;
	int firstScreen = 0;
	bool lost = false;
	bool singleGame = false;
	int level = 1;
	bool needsRedraw = true;
	int activeBarrels = 0;
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
		if (score > MAX_SCORE)
		{
			score = MAX_SCORE;
		}
		needsRedraw = true;
	}
	void initGame(player& mario, boardGame& board); // Initialize the game
	virtual void initialDraw(player& mario, boardGame& board) = 0; // Draw the initial board
	virtual void handleInput(player& mario) = 0; // Handle user input
	void updateNPCs(int iterationCounter, boardGame& board);
	virtual void updatePositionNPC(npc*& pNPC) = 0;
	void handleBarrelSpawn(boardGame& board, int iterationCounter);
	virtual void handleNPCDraw(npc* pNPC) = 0;
	virtual void gameLoop(player& mario, boardGame& board) = 0; // Main game loop

	void resetLives() { lives = 3; } // Reset the number of lives
	void resetScore() { score = 0; }
	virtual void fail(player& mario, bool& running, boardGame& board, int& barrelCounter, int& iterationCounter) =0; // Handle player fail
	virtual	void win(player& mario, bool& running, boardGame& board) = 0; // Handle player win
	
	
	 void getAllBoardFiles();
	void runGame(const std::string& fileName); // Run the game
	virtual void initSaveFile(const std::string& fileName) = 0;
	
	void drawLegend(boardGame& b) const;
public:
	virtual void run() = 0;

	
};

