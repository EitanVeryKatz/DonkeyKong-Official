#pragma once

#include "barrel.h"
#include "gameConfig.h"
#include "npc.h"
#include <vector>

using std::vector;

class barrel;
class ghost;

class boardGame
{
	int startXMario, startYMario;
	int monkeX, monkeY;
	int Lx, Ly;
	
	bool validPlayerPos = false;
	bool validMonkeyPos = false;
	bool validPrincessPos = false;
	char activeBoard[BOARD_HEIGHT][BOARD_WIDTH] = {};
	char failChart[BOARD_WIDTH][BOARD_HEIGHT];
	void readBoardFromFile(const std::string& fileName);
	bool succOpen = false;
	bool newBoardFile = false;
	barrel barrels[BARRELS_NUM];
	vector <ghost> ghosts;
public :
	boardGame(const std::string& fileName);
	char getChar(int x, int y) { return activeBoard[y][x]; } // get the char of the board at the given coordinates
	void newDrawBoard() const; // draw the board
	
	void UpdateFailChart(int x, int y, char c) { failChart[x][y] = c; } // update the fail chart at the given coordinates
	char getFailChart(int x, int y) const { return failChart[x][y]; } // get the char of the fail chart at the given coordinates
	void initBarrels(); // initialize the barrels
	void initFailChart(); // initialize the fail chart
	barrel& getBarrel(int i) { return barrels[i]; }
	void initActiveBoard();
	void resetGhosts();
	int getMarioStartX() const { return startXMario; }
	int getMarioStartY() const { return startYMario; }
	int getMonkeX() const { return monkeX; }
	int getMonkeY() const { return monkeY; }
	int getLx() const { return Lx; }
	int getLy() const { return Ly; }
	bool checkOnFloor (int x, int y) const;
	bool getValidity() const { return (validPlayerPos && validMonkeyPos && validPrincessPos); }
	bool getOpen() const { return succOpen; }
	bool getNewBoardFile() const { return newBoardFile; }
	void setNewBoardFile(bool b) { newBoardFile = b; }
	
	
	vector<ghost>::iterator getGhostsBegin() { return ghosts.begin(); }
	vector<ghost>::iterator getGhostsEnd() { return ghosts.end(); }
};

