#pragma once
#include "player.h"
#include "boardGame.h"

class game
{
	void initGame(player& mario, boardGame& board);
	void handleInput(player& mario, bool& running);
	void updateBarrels(boardGame& board, int& barrelCounter, int numBarrels, int iterationCounter);
	void gameLoop(player& mario, boardGame& board);
public:
	void runGame();
};

