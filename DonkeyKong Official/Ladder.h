#pragma once

#include "gameConfig.h"

class Ladder
{
	static constexpr char LADDER_ICON = 'H';
	int minY,maxY,X = 20;//ladder location on screen
	

public:
	void drawLadder(int mY, int MY);
	int getX() { return X; }
	int getMinY() { return minY; }
	int getMaxY() { return maxY; }
};

