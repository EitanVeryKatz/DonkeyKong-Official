#pragma once

#include "barrel.h"
#include "gameConfig.h"
#include "npc.h"
#include <vector>


using std::vector;

class npc;
class barrel;
class ghost;

class boardGame
{
	static constexpr int L_LENGTH = 8;
	static constexpr int L_HEIGHT = 2;
	int startXMario, startYMario;
	int monkeX, monkeY;
	int Lx, Ly;
	bool validPlayerPos = false;
	bool validMonkeyPos = false;
	bool validPrincessPos = false;
	bool validLPos = false;
	bool validBarrelSpawningPos = false;
	char activeBoard[BOARD_HEIGHT][BOARD_WIDTH] = {};
	char failChart[BOARD_WIDTH][BOARD_HEIGHT];
	void readBoardFromFile(const std::string& fileName);
	bool succOpen = false;
	bool newBoardFile = false;
	vector <npc*> npcVector;
	void checkLegendValidity(int x, int y);
public :
	boardGame(const std::string& fileName);
	~boardGame();
	char getChar(int x, int y) const; // get the char of the board at the given coordinates
	void newDrawBoard() const; // draw the board
	void UpdateFailChart(int x, int y, char c) { failChart[x][y] = c; } // update the fail chart at the given coordinates
	char getFailChart(int x, int y) const { return failChart[x][y]; } // get the char of the fail chart at the given coordinates
	void initBarrels(); // initialize the barrels
	void initFailChart(); // initialize the fail chart
	void initActiveBoard(); 
	void resetGhosts();
	int getMarioStartX() const { return startXMario; }
	int getMarioStartY() const { return startYMario; }
	int getMonkeX() const { return monkeX; }
	int getMonkeY() const { return monkeY; }
	int getLx() const { return Lx; }
	int getLy() const { return Ly; }
	bool checkOnFloor (int x, int y) const;
	bool getValidity() const { return validPlayerPos && validMonkeyPos && validPrincessPos && validLPos && validBarrelSpawningPos;}
	bool getOpen() const { return succOpen; }
	bool getNewBoardFile() const { return newBoardFile; }
	void setNewBoardFile(bool b) { newBoardFile = b; }
	void resetNPCVector();
	vector<npc*>& getNPCVector() { return npcVector; }
	vector<npc*>::iterator getNPCVectorBegin() { return npcVector.begin(); }
	vector<npc*>::iterator getNPCVectorEnd() { return npcVector.end(); }
	bool checkValidChar(int x, int y) const;
};

