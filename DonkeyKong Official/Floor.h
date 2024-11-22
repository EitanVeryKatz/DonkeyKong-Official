#pragma once

#include <cstdlib>
#include "gameConfig.h"
#include <iostream>

class Floor
{
	
public:
	int xStart, xEnd, y, sizeOfFloor;
	char dir;
	void drawFloor() const;
};



