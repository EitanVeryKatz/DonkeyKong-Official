#pragma once

#include "gameObject.h"

class npc : public gameObject
{
	bool active = true;
	bool smashed = false;
public:
	using gameObject::gameObject;
	bool isActive() const { return active; }
	void resetSmash() { smashed = false; }
	void setSmash() { smashed = true; }
	bool wasSmashed() { return smashed; }
	void makeActive() { active = true; }
	void deactivate() { active = false; }

};

