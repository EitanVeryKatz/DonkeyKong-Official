#pragma once

#include "barrel.h"
#include "gameConfig.h"
class barrel;

class boardGame
{
	barrel barrels[BARRELS_NUM];
	const char* boardLayout[BOARD_HEIGHT] =
	{   //           1         2         3         4         5         6         7                  
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                       &                                      Q", // 1
		  "Q  Lives:                               &     $                                Q", // 2
		  "Q                                    == ==  =====                              Q", // 3
		  "Q                                               H                              Q", // 4
		  "Q                                               H                              Q", // 5
		  "Q                                               H                              Q", // 6
		  "Q                                        >>>>>>>>>>>>>>>>>>                    Q", // 7
		  "Q                              <<<<<<<<<<<<<              H                    Q", // 8
		  "Q                                                         H                    Q", // 9
		  "Q                                                         H                    Q", // 10
		  "Q                                                         H                    Q", // 11
		  "Q                                           <<<<<<<<<<<<<<<<<<<<<<<            Q", // 12
		  "Q                                           H                                  Q", // 13
		  "Q  >>>>>      <<<<<<<     <<<=>>>>>>>====>>>>>                                 Q", // 14
		  "Q      H                                H                                      Q", // 15
		  "Q      H                                H                                      Q", // 16
		  "Q      >>>>>>>>>>>>>>>>                 H                                      Q", // 17
		  "Q                     H                  <<<<<<====<<<                         Q", // 18
		  "Q                     H                            H                           Q", // 19
		  "Q            ========                              H                           Q", // 20
		  "Q                                                  H                           Q", // 21
		  "Q  ==========                                      H                           Q", // 22
		  "Q           ================================================================   Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	char failChart[BOARD_WIDTH][BOARD_HEIGHT];

public :
	char getChar(int x, int y) { return boardLayout[y][x]; }
	void newDrawBoard();
	barrel& getBarrel(int index) { return barrels[index]; }
	void UpdateFailChart(int x, int y, char c) { failChart[x][y] = c; }
	char getFailChart(int x, int y) { return failChart[x][y]; }
	void initBarrels();
	void initFailChart();
	boardGame()
	{
		initFailChart();
	}
};

