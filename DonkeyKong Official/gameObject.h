#pragma once

#include "point.h"
class boardGame;
class gameObject
{
	point position;
	char icon;
protected:
	boardGame* pBoard = nullptr;
	void setPosition(int x, int y) { position.setPoint(x, y); }
	void setDir(Direction dir) { position.setDir(dir); }
	void changeIcon(char c) { icon = c; }
	void setX(int x) { position.setX(x); }
	void setY(int y) { position.setY(y); }
	void setDirX(int x) { position.setDirX(x); }
	void setDirY(int y) { position.setDirY(y); }
	void setFailChart(char c) const;
	void setFailChart(int x, int y, char c) const;
public:
	gameObject(int x, int y, char icon) : position(x, y), icon(icon) {}
	gameObject(char icon) : icon(icon) {}
	void draw() const { position.draw(icon); }
	virtual void move(bool silent = false) = 0;
	void erase() const { position.erase(); }
	void setGameBoard(boardGame* pBoard) { this->pBoard = pBoard; }
	bool isOnFloor() const;
	bool isOnFloor(int x, int y) const;
	bool isOnLadder() const;
	char getFailChart() const;
	char getFailChart(int x, int y) const;
	void restoreBoardChar(int x, int y) const;
	int getX() const { return position.getX(); }
	int getY() const { return position.getY(); }
	int getDirX() const { return position.getDirX(); }
	int getDirY() const { return position.getDirY(); }
	char getChar() const;
	char getChar(int x, int y) const;
	void inLegend(bool &needToRedraw) const;
	virtual ~gameObject() = default;
};

