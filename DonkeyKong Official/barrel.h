#pragma once
#include <vector>
#include "gameConfig.h"
#include "iostream"
#include "point.h"

using std::vector;

class boardGame;

class barrel
{
	point position;
	point startingPos;
	static constexpr int FIRST_FLOOR_Y = 6;
	static constexpr char FLOOR_DIR_LEFT = '<';
	static constexpr int LEFT = 0, DOWN = 1, RIGHT = 2, STAY = 3, STOP = 0;
	static constexpr char ICON = 'O';
	bool active = true;
	int lastFloorY = FIRST_FLOOR_Y;
	int blastCenterX = 0;
	int blastCenterY = 0;
	bool blastParticlesVisable = false;
	int blastCounter = 0;
	bool exploaded = false;
	int fallCounter = 0;
public:
	static vector<int> startingXPos;
	void setBarrelPos(int x, int y) { position.setPoint(x, y); }
	void setStartPos(int x, int y) { startingPos.setPoint(x, y); }
	void draw_USING_POINT() { position.draw(ICON); }
	void erase_USING_POINT() { position.erase(); }
	void barrelFall_USING_POINT(); // handles barrel movement
	void handleExplosion();
	void deactivateBarrel();
	void handleOnFloor(int currX, int currY, int& newX, int& newY, char& dirChar); // handles barrel movement on floor
	void handleInAir(int currX, int currY, int& newX, int& newY); // handles barrel movement in air
	void updatePosition(int currX, int currY, int newX, int newY); // updates the position of the barrel
	void setBoard_USING_POINT(boardGame* board) { position.setGameBoard(board); };
	void explode();
	bool isActive() const { return active; }
	void clearBlast();
	bool isBlastShowing() { return blastParticlesVisable; }
	int getBlowCount() { return blastCounter; }
	void updateBlowCounter();
	void resetBlowCounter() { blastCounter = 0; }
	void resetBarrel_USING_POINT();
	bool checkSmash();
	void updateFallCount();
};

