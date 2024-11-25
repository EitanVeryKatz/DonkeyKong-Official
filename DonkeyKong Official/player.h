#pragma once

#include <iostream>
#include "gameConfig.h"
#include "Floor.h"
#include "boardGame.h"


class player
{
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; };
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int x = 14, y = 10;
	int prevX = x, prevY = y;
	Direction dir{ 0,0 };
	char icon = '@';
	Floor currentFloor;
	bool midjump = false;
	bool onLadder = false;
	bool isOnFloor;
	boardGame* board;
	void draw(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}

public:
	void draw() const
	{
		draw(icon);
	}
	void erase()
	{
		draw(' ');
	}
	void keyPressed(char key);
	void moveInBoard(boardGame& board);
	void onFloor(int* floorIndex, boardGame& board);
	void newIsOnFloor();
	bool isOnLadder();
	void setGameBoard(boardGame* gameBoard) { board = gameBoard; }
	void newIsOnLadder();
};

