#pragma once

#include "barrel.h"
class barrel;

class boardGame
{
	static constexpr int BOARD_WIDTH = 80;
	static constexpr int BOARD_HEIGHT = 25;
	static constexpr int BARRELS_NUM = 10;
	barrel barrels[BARRELS_NUM];
	const char* boardLayout[BOARD_HEIGHT] =
	{   //           1         2         3         4         5         6         7                  
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                       &                                      Q", // 1
		  "Q                                       &    $                                 Q", // 2
		  "Q                                    == ====H====                              Q", // 3
		  "Q                                           H                                  Q", // 4
		  "Q                                           H                                  Q", // 5
		  "Q                                >>>>>>H>>>>>>>>>>>>>>>                        Q", // 6
		  "Q                                      H                                       Q", // 7
		  "Q                                      H                                       Q", // 8
		  "Q                                    <<<<<<H<<<<<<<<<<<H<<<                    Q", // 9
		  "Q                                          H           H                       Q", // 10
		  "Q                                          H           H                       Q", // 11
		  "Q                      >>>>>H>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                 Q", // 12
		  "Q                           H                                                  Q", // 13
		  "Q                           H                                                  Q", // 14
		  "Q            <<<<<<<<<<<<<<<<<<<<<<<<<H<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<        Q", // 15
		  "Q                                     H                                        Q", // 16
		  "Q                                     H                                        Q", // 17
		  "Q   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                       Q", // 18
		  "Q                                                                              Q", // 19
		  "Q                                                                              Q", // 20
		  "Q                                                                              Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                                                                              Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

public :
	char getChar(int x, int y) { return boardLayout[y][x]; }
	int getWidth() {return BOARD_WIDTH;}
	int getHeight() {return BOARD_HEIGHT;}
	void newDrawBoard();
	barrel& getBarrel(int index) { return barrels[index]; }
	int getBarrelsNum() { return BARRELS_NUM; }
};

