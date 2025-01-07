#pragma once
#include "point.h"
class bad_guys
{
protected:
	char icon;
	point position;
	bool active = true;
	bool smashed = false;

public:
	void setIcon(char c) { icon = c; }
	void draw() const { position.draw(icon); }
	void erase() const { position.erase(); }
	void setPos(int x, int y) { position.setPoint(x, y); }
	void setGameBoard(boardGame* gameBoard) { position.setGameBoard(gameBoard); }
	void setDir(Direction d) { position.setDir(d); }
	bool isActive() const { return active; }
	bool isSmashed() const { return smashed; }
	virtual ~bad_guys() = default;
};

