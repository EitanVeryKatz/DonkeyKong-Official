#pragma once

#include "Floor.h"
#include "Ladder.h"

class Ladder;
class Floor;

class boardGame
{
	static constexpr int NUM_OF_FLOORS = 5;
	static constexpr int BOARD_WIDTH = 80;
	static constexpr int BOARD_HEIGHT = 25;
	Floor boardFloors[NUM_OF_FLOORS];


	const char* boardLayout[BOARD_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                &&                                                            Q", // 1
		  "Q                &&    $                                                       Q", // 2
		  "Q             ==========                                                       Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                                                                              Q", // 5
		  "Q      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                                       Q", // 6
		  "Q                                      H                                       Q", // 7
		  "Q                                      H                                       Q", // 8
		  "Q                                    <<<<<<<<<<<<<<<<<<<<<<                    Q", // 9
		  "Q                                          H           H                       Q", // 10
		  "Q                                          H           H                       Q", // 11
		  "Q                      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                 Q", // 12
		  "Q                           H                                                  Q", // 13
		  "Q                           H                                                  Q", // 14
		  "Q            <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<              Q", // 15
		  "Q                                     H                                        Q", // 16
		  "Q                                     H                                        Q", // 17
		  "Q                      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                   Q", // 18
		  "Q                                                                              Q", // 19
		  "Q                                                                              Q", // 20
		  "Q                                                                              Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                                                                              Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

public :
	char getChar(int x, int y) { return boardLayout[y][x]; }
	void initLadders();
	int getWidth() {return BOARD_WIDTH;}
	int getHeight() {return BOARD_HEIGHT;}
	int getFloorCount() {return NUM_OF_FLOORS;}
	Floor getFloor(int index) { return boardFloors[index];}
	void initFloors();
	void drawBoard();
	void newDrawBoard();

};

