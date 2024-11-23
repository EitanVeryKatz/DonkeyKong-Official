#pragma once

#include <cstdlib>
#include "gameConfig.h"
#include <iostream>

class Floor
{
	static constexpr int RIGHT = 0;
	static constexpr int LEFT = 1;
	static constexpr int SAME = 2;
	static constexpr char FLOOR_DIR[] = {'>','<','='};
public:
	int xStart, xEnd, y, sizeOfFloor;
	char dir;
	void randDir();
	void drawFloor() const;
};



