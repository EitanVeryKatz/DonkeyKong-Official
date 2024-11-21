#pragma once

#include <cstdlib>
#include "gameConfig.h"
#include <iostream>

class Floor
{
	char dir = '<';
	
	
public:
	int xStart = 3, xEnd = 75, y = 10, sizeOfFloor;
	void drawFloor();
};



//bla bla bla
