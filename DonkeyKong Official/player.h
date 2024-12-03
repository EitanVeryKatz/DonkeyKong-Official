#pragma once

#include <iostream>
#include "gameConfig.h"
#include "boardGame.h"

class player
{
	static constexpr int startX = 6, startY = 17;
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; };
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int x = startX, y = startY;
	int prevX = x, prevY = y;
	Direction dir{ 0,0 };
	char icon = '@';
	bool midjump = false;
	bool onLadder = false;
	bool isOnFloor;
	boardGame* board;
	int lives = 3;

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
	void resetPlayer()
	{
		x = startX;
		y = startY;
		dir = { 0,0 };
	}
	void keyPressed(char key);
	void moveInBoard();
	void newIsOnFloor();
	void setGameBoard(boardGame* gameBoard) { board = gameBoard; }
	void newIsOnLadder();
	bool checkFail();
	bool checkWin();
};

