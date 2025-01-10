#pragma once
#include <vector>
#include "gameConfig.h"
#include "iostream"
#include "point.h"
#include "gameObject.h"
#include "npc.h"

using std::vector;

class boardGame;

class barrel:public npc
{
	
	point startingPos;
	static constexpr char FLOOR_DIR_LEFT = '<';
	static constexpr int LEFT = 0, DOWN = 1, RIGHT = 2, STAY = 3, STOP = 0;
	static constexpr char ICON = 'O';
	
	int blastCenterX = 0;
	int blastCenterY = 0;
	bool blastParticlesVisable = false;
	int blastCounter = 0;
	bool exploaded = false;
	int fallCounter = 0;
	
public:
	static vector<int> startingXPos;
	void setBarrelPos(int x, int y) {setPosition(x, y); }
	void setStartPos(int x, int y) { startingPos.setPoint(x, y); }
	void barrelFall(); // handles barrel movement
	void handleExplosion();
	void deactivateBarrel();
	void handleOnFloor(int currX, int currY, int& newX, int& newY, char& dirChar); // handles barrel movement on floor
	void handleInAir(int currX, int currY, int& newX, int& newY); // handles barrel movement in air
	void updatePosition(int currX, int currY, int newX, int newY); // updates the position of the barrel
	void setBoard(boardGame* board) { setGameBoard(board); };
	void explode();
	
	void clearBlast();
	bool isBlastShowing() { return blastParticlesVisable; }
	int getBlowCount() { return blastCounter; }
	void updateBlowCounter();
	void resetBlowCounter() { blastCounter = 0; }
	void resetBarrel();
	bool checkSmash();
	
	void updateFallCount();
};

