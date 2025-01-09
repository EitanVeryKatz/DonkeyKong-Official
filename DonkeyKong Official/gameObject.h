#pragma once
#include "movingPoint.h"
#include "boardGame.h"

struct direction;
class gameObject
{
	movingPoint position;
	boardGame* pBoard = nullptr;
	
	char icon;

public:

	gameObject(char icon) : icon(icon) {}
	gameObject(int x, int y, char icon) : position(x, y)
	{
		this->icon = icon;
	}
	void setFailChart(char c);
	void setPosition(int x, int y) { position.setPoint(x, y); }
	void setGameBoard(boardGame* pBoard) { this->pBoard = pBoard; }
	void draw() const { position.draw(icon); }
	void erase() const { position.erase(); }
	void changeIcon(char c) { icon = c; }
	bool isOnFloor() const;
	bool isOnLadder() const;
	// only npc need to have setFailChart
	char getFailChart() const;
	int getDirX() const { return position.getDirX(); };
	int getDirY() const { return position.getDirY(); };
	void stop() { position.setDir({ 0,0 }); }
	void move(direction d);
	void restoreBoardChar(int x, int y) const;
	int getX() const { return position.getX(); }
	int getY() const { return position.getY(); }
	char getChar() const { return pBoard->getChar(position.getX(), position.getY()); }
	char getChar(int x, int y) const { return pBoard->getChar(x, y); }
	direction calcDir(int newX, int newY) const;
};

