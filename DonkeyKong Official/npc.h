#pragma once

#include <iostream>
#include "gameConfig.h"
#include "boardGame.h"
#include "point.h"
#include "gameObject.h"

class npc:public gameObject
{
	bool active = true;
	bool smashed = false;
public:
	using gameObject::gameObject;
	bool isActive() const { return active; }
	void resetSmash() { smashed = false; }
	bool wasSmashed() { return smashed; }
	void makeActive() { active = true; }
	void deactivate() { active = false; }

};

