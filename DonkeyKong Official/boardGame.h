#pragma once

#include "Floor.h"


class Floor;

class boardGame
{
	static constexpr int BOARD_WIDTH = 80;
	static constexpr int BOARD_HEIGHT = 25;
	Floor boardFloors[4];
	int floorCount = 4;

public :
	int getWidth() {return BOARD_WIDTH;}
	int getHeight() {return BOARD_HEIGHT;}
	int getFloorCount() {return floorCount;}
	Floor getFloor(int index) { return boardFloors[index];}
	void initFloors();
	void drawBoard();

};

