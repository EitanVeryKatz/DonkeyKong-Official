#pragma once

#include "gameObject.h"

class npc : protected gameObject
{
	bool active = true;
	bool smashed = false;
public:
	using gameObject::setPosition;
	using gameObject::setGameBoard;
	using gameObject::draw;
	npc(int x, int y, char icon): gameObject(x,y,icon) {}
	npc(char icon):gameObject(icon){}
	bool isActive() const { return active; }
	void resetSmash() { smashed = false; }
	void setSmash() { smashed = true; }
	bool wasSmashed() const { return smashed; }
	void makeActive() { active = true; }
	void deactivate() { active = false; }
	bool checkSmash() const {return getFailChart() == 'p';}
	virtual void move() = 0;
	void update(int &score, bool& needToRedraw);
	virtual ~npc() = default;

};

