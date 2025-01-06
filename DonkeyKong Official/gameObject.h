#pragma once
#include "point.h"
#include "boardGame.h"
class gameObject
{
	point position;
	char icon;

public:
	gameObject(int x, int y, char icon) : position(x, y), icon(icon) {}
	void draw() const { position.draw(icon); }
	void erase() const { position.erase(); }
	void setPosition(int x, int y) { position.setPoint(x, y); }
};

