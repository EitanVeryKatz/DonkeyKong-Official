#pragma once

#include <iostream>
#include "gameConfig.h"
#include "boardGame.h"
#include "point.h"
#include "gameObject.h"

class player : public gameObject
{
	static constexpr direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	static constexpr int STAY = 4, STOP = 0, DOWN = 1, JUMPING_FARME = 2, UP = -1;
	int startX, startY;
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);;
	static constexpr char iconArr[] = { '@' ,'a'};
	//char currIcon = iconArr[0];
	static constexpr char hammerIcon = 'p';
	gameObject hammerLocation; // need to change hammer to the new moving point
	bool hasHammer = false;
	int midjump = 0;
	bool midswing = false;
	//point position;
	int fallCounter = 0;
public:

	player(int x, int y) : gameObject(x, y, iconArr[0]), startX(x), startY(y),hammerLocation(hammerIcon) {}

	void resetPlayer()
	{
		changeIcon(iconArr[0]);
		midjump = 0;
		fallCounter = 0;
		setPosition(startX, startY);
		stop();
		hasHammer = true;
		midswing = 0;
		setHammerLocation();
	}
	bool isSwingingHammer() { return midswing; }
	void keyPressed(char key); // Handle player's key press
	void checkHasHmmer();
	void playerMovement(); // handle player's movement
	bool isAtVerticalBorder(int currX, int dirX); // Check if player is at vertical border
	bool isAtHorizontalBorder(int currY, int dirY); // Check if player is at horizontal border
	void handleVerticalBorder(int currX, int currY, int dirY, int& newX, int& newY); // Handle vertical border
	void handleHorizontalBorder(int currX, int currY, int dirX, int& newX, int& newY, int& dirY); // Handle horizontal border
	void handleInsideBorders(int currX, int currY, int dirX, int dirY, int& newX, int& newY); // Handle inside borders
	bool swingHit(int swingx, int swingy);
	void setHemmerBoard(boardGame* gameBoard) { hammerLocation.setGameBoard(gameBoard); }
	bool checkFail(); // Check if player failed
	bool checkWin(); // Check if player won
	bool isFalling(); // Check if player is falling
	int getHammerY() { return hammerLocation.getY(); }
	int getHammerX() { return hammerLocation.getX(); }
	void setHammerLocation();
	bool doeshasHammer() { return hasHammer; }
	void drawHammer()
	{
		hammerLocation.draw();
	}
	void swingHammer();
	void clearHammerSwing();
	
};

