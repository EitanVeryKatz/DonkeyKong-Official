#pragma once
#include "gameObject.h"
class bad_guys : public gameObject
{
	bool active = true;
	bool smashed = false;
public:
	bool isActive() const { return active; }
};

