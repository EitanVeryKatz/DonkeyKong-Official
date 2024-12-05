#pragma once

#include <iostream>
#include "gameConfig.h"
#include "boardGame.h"
#include "point.h"

class player
{
	static constexpr int startX = 6, startY = 17;
	static constexpr int firstFloorY = 18;
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; };
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int x = startX, y = startY;
	int prevX = x, prevY = y;
	Direction dir{ 0,0 };
	char icon = '@';
	int midjump = 0;
	bool onLadder = false;
	bool isOnFloor;
	boardGame* board;
	int lastFloorY = firstFloorY;
	int currentFloorY = firstFloorY;
	point position;

	void draw(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}
public:

	player() : position(startX, startY) {}

	void draw() const
	{
		draw(icon);
	}
	void erase()
	{
		draw(' ');
	}
	void resetPlayer()
	{
		x = startX;
		y = startY;
		dir = { 0,0 };
		lastFloorY = firstFloorY;
		currentFloorY = firstFloorY;
	}
	void keyPressed(char key);
	void moveInBoard();
	void moveInBoard_USING_POINT();
	void newIsOnFloor();
	void setGameBoard(boardGame* gameBoard) { board = gameBoard; }
	void newIsOnLadder();
	bool checkFail();
	bool checkWin();
};

