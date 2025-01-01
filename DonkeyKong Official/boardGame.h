#pragma once

#include "barrel.h"
#include "gameConfig.h"
#include <vector>

using std::vector;

class barrel;
class ghost;

class boardGame
{
	int startXMario, startYMario;
	int monkeX, monkeY;
	int Lx, Ly;
	barrel barrels[BARRELS_NUM];
	bool validPlayerPos = false;;
	char activeBoard[BOARD_HEIGHT][BOARD_WIDTH];
	char failChart[BOARD_WIDTH][BOARD_HEIGHT];
	void readBoardFromFile(const std::string& fileName);
	bool succOpen = false;
public :
	char getChar(int x, int y) { return activeBoard[y][x]; } // get the char of the board at the given coordinates
	void newDrawBoard() const; // draw the board
	barrel& getBarrel(int index) { return barrels[index]; } // get the barrel at the given index
	void UpdateFailChart(int x, int y, char c) { failChart[x][y] = c; } // update the fail chart at the given coordinates
	char getFailChart(int x, int y) const { return failChart[x][y]; } // get the char of the fail chart at the given coordinates
	void initBarrels(); // initialize the barrels
	void initFailChart(); // initialize the fail chart
	boardGame(const std::string& fileName);
	//void initGhosts();
	void initActiveBoard();
	void resetGhosts();
	vector <ghost> ghosts;
	int getMarioStartX() const { return startXMario; }
	int getMarioStartY() const { return startYMario; }
	int getMonkeX() const { return monkeX; }
	int getMonkeY() const { return monkeY; }
	bool checkPlayerPos (int x, int y) const;
	bool getValidity() const { return validPlayerPos; }
	bool getOpen() const { return succOpen; }
};

