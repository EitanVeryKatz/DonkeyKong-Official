#include "npc.h"

void npc::update(int& score, bool& needToRedraw)
{
	if (isActive())
	{
		erase();
		move();
		if (wasSmashed())
		{
			resetSmash();
			score += 150;
			needToRedraw = true;
		}
		if (isActive())
		{
			draw();
		}
	}
}
