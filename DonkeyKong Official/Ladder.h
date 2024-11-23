#pragma once

#include "boardGame.h"
#include "gameConfig.h"
class Ladder
{
	static constexpr char LADDER_ICON = 'H';
	int minY,maxY,X;//ladder location on screen
	

public:
	void drawLadder();
	void setX(); // random function to determine the x of the ladder in a floor (needs to be implemented)
};

