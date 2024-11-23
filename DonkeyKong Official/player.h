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
	int x = 6, y = 1;
	Direction dir{ 0,0 };
	char icon = '@';
	Floor** platformArr;
	bool midjump = false;
	bool onLadder = false;
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
	bool onFloor(int* floorIndex, boardGame& board);
	void moveWithFloor(const Floor& f, boardGame& board, int floorIndex);
	void updatePlatformArr(Floor** newPlatformArr);
};

