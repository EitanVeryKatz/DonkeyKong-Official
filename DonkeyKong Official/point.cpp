#include "point.h"


bool point::isOnFloor()
{
	if (pBoard->getChar(x, y + 1) == '<' || pBoard->getChar(x, y + 1) == '>' || pBoard->getChar(x, y + 1) == '=')
	{
		return true;
	}
	return false;
}

bool point::isOnLadder()
{
	if (pBoard->getChar(x, y) == 'H' || (pBoard->getChar(x, y + 1) == 'H' && (pBoard->getChar(x, y) == '<' || pBoard->getChar(x, y) == '>' || pBoard->getChar(x, y) == '=')))
	{
		return true;
	}
	return false;
}
