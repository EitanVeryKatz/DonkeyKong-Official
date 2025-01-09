#pragma once
#include <iostream>
#include "gameConfig.h"
#include "boardGame.h"
#include "point.h"
#include "gameObject.h"

class hammer: public gameObject
{
private:
	int dirX;
public:
	
	using gameObject::gameObject;
	void move(int marioX, int marioY);
	void setDir(direction dir) { dirX = dir.x; }
};

