#pragma once

#include <cstdlib>
#include "gameConfig.h"
#include <iostream>
#include "Ladder.h"
#include "utils.h"

class Ladder;

class Floor
{
	static constexpr int RIGHT = 0;
	static constexpr int LEFT = 1;
    static constexpr char FLOOR_DIR[] = {'>','<'};
	static constexpr char FLOOR_ICON = '=';
	static constexpr int numOfLadders = 1;
	Ladder LadderArr[numOfLadders];
	char dir;
public:
	int xStart, xEnd, y, sizeOfFloor;
	void randDir();
	void drawFloor() const;
	void initLadders();
	int getNumOfLadders() { return numOfLadders; }
	char getDir() const { return dir; }
	Ladder& getLadderAtIndex(int index) { return LadderArr[index]; }
};



