#pragma once

#include "Floor.h"
#include "Ladder.h"

class Floor;

class boardGame
{
	static constexpr int BOARD_WIDTH = 80;
	static constexpr int BOARD_HEIGHT = 25;
	Floor boardFloors[4];
	int floorCount = 4;
	Ladder LadderArr[3];


public :
	void initLadders();
	int getWidth() {return BOARD_WIDTH;}
	int getHeight() {return BOARD_HEIGHT;}
	int getFloorCount() {return floorCount;}
	Floor getFloor(int index) { return boardFloors[index];}
	void initFloors();
	void drawBoard();

};

