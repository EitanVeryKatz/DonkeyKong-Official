#pragma once

#include <cstdlib>
#include "gameConfig.h"
#include <iostream>
#include "Ladder.h"

class Ladder;

class Floor
{
	static constexpr int RIGHT = 0;
	static constexpr int LEFT = 1;
	static constexpr int SAME = 2;
	static constexpr char FLOOR_DIR[] = {'>','<','='};
	int numOfLadders = 3;
	
public:
	int xStart, xEnd, y, sizeOfFloor;
	char dir;
	void randDir();
	void drawFloor() const;
	void initLadders();
	// set random number of ladders between 1-3
	int  getNumOfLadders() { return numOfLadders; }
};



