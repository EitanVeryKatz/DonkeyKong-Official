#pragma once
#include "point.h"
#include "boardGame.h"
class gameObject
{
	point position;
	char icon;

public:
	//gameObject(int x, int y, char icon) : position(x, y), icon(icon) {}
	gameObject(int x, int y) : position(x, y) {}
	gameObject(char icon) : icon(icon) {}
	void draw() const { position.draw(icon); }
	void erase() const { position.erase(); }
	void setPosition(int x, int y) { position.setPoint(x, y); }
	void setGameBoard(boardGame* pBoard) { position.setGameBoard(pBoard); }
	void setDir(Direction dir) { position.setDir(dir); }
	int getX() const { return position.getX(); }
	int getY() const { return position.getY(); }
	int getDirX() const { return position.getDirX(); }
	int getDirY() const { return position.getDirY(); }
	char getChar() { return position.getChar(); }
	char getChar(int x, int y) { return position.getChar(x, y); }
	bool isOnFloor() { return position.isOnFloor(); }
	bool isOnLadder() { return position.isOnLadder(); }
	void setDirY(int y) { position.setDirY(y); }
	void setDirX(int x) { position.setDirX(x); }
	void setIcon(char icon) { this->icon = icon; }
	void setFailChart(char c) { position.setFailChart(c); }
	char getFailChart() { return position.getFailChart(); }
	char getFailChart(int x, int y) { return position.getFailChart(x, y); }
	virtual void move() = 0;
	virtual ~gameObject() = default;
};

