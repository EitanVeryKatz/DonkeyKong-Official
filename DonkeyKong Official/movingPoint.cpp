#include "movingPoint.h"

void movingPoint::setNewPos(direction d)
{
	dir = d;
	x += dir.x;
	y += dir.y;
}
