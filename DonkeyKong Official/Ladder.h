#pragma once

#include "gameConfig.h"

class Ladder
{
	static constexpr char LADDER_ICON = 'H';
	int minY,maxY,X = 20;//ladder location on screen
	

public:
	void drawLadder(int mY, int MY);
	int getX() const { return X; }
	int getMinY() const { return minY; }
	int getMaxY() const { return maxY; }
	void updateX(int newX) { X = newX; }
};

