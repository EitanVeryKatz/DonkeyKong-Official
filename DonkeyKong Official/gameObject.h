#pragma once

#include "point.h"
class boardGame;
class gameObject
{
	point position;
	char icon;
protected:
	boardGame* pBoard = nullptr;

public:
	gameObject(int x, int y, char icon) : position(x, y), icon(icon) {}
	gameObject(char icon) : icon(icon) {}
	void draw() const { position.draw(icon); }
	void erase() const { position.erase(); }
	void setGameBoard(boardGame* pBoard) { this->pBoard = pBoard; }
	bool isOnFloor() const;
	bool isOnFloor(int x, int y) const;
	bool isOnLadder() const;
	char getFailChart() const;
	char getFailChart(int x, int y) const;
	void setFailChart(char c);
	void setFailChart(int x, int y, char c);
	void restoreBoardChar(int x, int y);
	void changeIcon(char c) { icon = c; }
	void setPosition(int x, int y) { position.setPoint(x, y); }
	void setDir(Direction dir) { position.setDir(dir); }
	int getX() const { return position.getX(); }
	int getY() const { return position.getY(); }
	void setX(int x) { position.setX(x); }
	void setY(int y) { position.setY(y); }
	int getDirX() { return position.getDirX(); }
	int getDirY() { return position.getDirY(); }
	void setDirX(int x) { position.setDirX(x); }
	void setDirY(int y) { position.setDirY(y); }
	char getChar() const;
	char getChar(int x, int y) const;
	virtual ~gameObject() = default;
};

