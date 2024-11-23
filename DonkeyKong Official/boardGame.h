#pragma once

#include "Floor.h"
#include "Ladder.h"

class Floor;

class boardGame
{
	static constexpr int NUM_OF_FLOORS = 5;
	static constexpr int BOARD_WIDTH = 80;
	static constexpr int BOARD_HEIGHT = 25;
	Floor boardFloors[NUM_OF_FLOORS];



public :
	void initLadders();
	int getWidth() {return BOARD_WIDTH;}
	int getHeight() {return BOARD_HEIGHT;}
	int getFloorCount() {return NUM_OF_FLOORS;}
	Floor getFloor(int index) { return boardFloors[index];}
	void initFloors();
	void drawBoard();

};

