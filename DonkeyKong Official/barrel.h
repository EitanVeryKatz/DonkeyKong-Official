#pragma once
#include "gameConfig.h"
#include "iostream"
#include "point.h"

class boardGame;

class barrel
{
	point position;
	static constexpr int FIRST_FLOOR_Y = 6;
	static constexpr char FLOOR_DIR_LEFT = '<';
	static constexpr int startX_1 = 39, startY = 3, startX_2 = 42, LEFT = 0, DOWN = 1, RIGHT = 2, STAY = 3;
	int startX = rand() % 2 == 0 ? startX_1 : startX_2;
	static constexpr char ICON = 'O';
	bool active = true;
	int lastFloorY = FIRST_FLOOR_Y;
	int blastCenterX = 0;
	int blastCenterY = 0;
	bool blastParticlesVisable = false;
	int blastCounter = 0;
	bool exploaded = false;
public:
	barrel();
	void draw_USING_POINT() { position.draw(ICON); }
	void erase_USING_POINT() { position.erase(); }
	void barrelFall_USING_POINT();
	void handleExplosion();
	void deactivateBarrel();
	void handleOnFloor(int currX, int currY, int& newX, int& newY, char& dirChar);
	void handleInAir(int currX, int currY, int& newX, int& newY);
	void updatePosition(int currX, int currY, int newX, int newY);
	void setBoard_USING_POINT(boardGame* board) { position.setGameBoard(board); };
	void explode();
	bool isActive() const { return active; }
	void clearBlast();
	bool isBlastShowing() { return blastParticlesVisable; }
	int getBlowCount() { return blastCounter; }
	void updateBlowCounter();
	void resetBlowCounter() { blastCounter = 0; }
	void resetBarrel_USING_POINT();
};

