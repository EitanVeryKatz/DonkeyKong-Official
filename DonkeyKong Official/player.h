#pragma once

#include <iostream>
#include "gameConfig.h"
#include "boardGame.h"
#include "point.h"

class player
{
	static constexpr int startX = 30, startY = firstFloorY - 1, STAY = 4;
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);;
	char icon = '@';
	int midjump = 0;
	point position;
	int fallCounter = 0;
public:

	player() : position(startX, startY) {}

	void draw_USING_POINT() 
	{
		position.draw(icon);
	}

	void erase_USING_POINT()
	{
		position.draw(' ');
	}

	void resetPlayer()
	{
		fallCounter = 0;
		position.setPoint(startX, startY);
		position.setDirFromArrayPlayer(STAY);
	}
	void keyPressed_USING_POINT(char key); // Handle player's key press
	void moveInBoard_USING_POINT(); // handle player's movement
	bool isAtVerticalBorder(int currX, int dirX); // Check if player is at vertical border
	bool isAtHorizontalBorder(int currY, int dirY); // Check if player is at horizontal border
	void handleVerticalBorder(int currX, int currY, int dirY, int& newX, int& newY); // Handle vertical border
	void handleHorizontalBorder(int currX, int currY, int dirX, int& newX, int& newY); // Handle horizontal border
	void handleInsideBorders(int currX, int currY, int dirX, int dirY, int& newX, int& newY); // Handle inside borders
	void setGameBoard_USING_POINT(boardGame* gameBoard) { position.setGameBoard(gameBoard); }
	bool checkFail(); // Check if player failed
	bool checkWin(); // Check if player won
	bool isFalling(); // Check if player is falling
	
};

