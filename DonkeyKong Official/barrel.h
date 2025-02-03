#pragma once
#include <vector>
#include "gameConfig.h"
#include "point.h"
#include "npc.h"

using std::vector;

class boardGame;

class barrel:public npc
{
	//													LEFT    DOWN    RIGHT   STAY 
	static constexpr Direction directionsBarrel[] = { {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	enum directions { LEFT, DOWN, RIGHT, STAY };
	static constexpr char FLOOR_DIR_LEFT = '<';
	static constexpr int STOP = 0;
	static constexpr char ICON = 'O';
	int startX, startY;
	int blastCenterX = 0;
	int blastCenterY = 0;
	bool blastParticlesVisable = false;
	int blastCounter = 0;
	bool exploaded = false;
	int fallCounter = 0;
	

public:
	barrel(int monkeY);
	static vector<int> startingXPos;
	void move(bool silent) override; // handles barrel movement
	void handleExplosion(bool silent);
	void handleOnFloor(int currX, int currY, int& newX, int& newY, char& dirChar); // handles barrel movement on floor
	void handleInAir(int currX, int currY, int& newX, int& newY); // handles barrel movement in air
	void updatePosition(int currX, int currY, int newX, int newY, bool silent); // updates the position of the barrel
	void explode(bool silent);
	void clearBlast(bool silent);
	bool isBlastShowing() const { return blastParticlesVisable; }
	int getBlowCount() const { return blastCounter; }
	void updateBlowCounter();
	void resetBlowCounter() { blastCounter = 0; }
	void resetBarrel();
	void updateFallCount();
	int genStartX() const { return startingXPos[rand() % startingXPos.size()]; }
	void expHandler(bool silent);
};

