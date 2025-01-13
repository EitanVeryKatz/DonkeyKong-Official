#pragma once

#include "gameObject.h"

class npc : public gameObject
{
	bool active = true;
	bool smashed = false;
public:
	npc(int x, int y, char icon): gameObject(x,y,icon) {}
	npc(char icon):gameObject(icon){}
	bool isActive() const { return active; }
	void resetSmash() { smashed = false; }
	void setSmash() { smashed = true; }
	bool wasSmashed() { return smashed; }
	void makeActive() { active = true; }
	void deactivate() { active = false; }
	bool checkSmash() {return getFailChart() == 'p';}
	virtual void move() = 0;
	void update(int &score, bool& needToRedraw);
	virtual ~npc() {};

};

