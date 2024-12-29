#include "point.h"
#include "boardGame.h"

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

char point::getChar()
{
	return pBoard->getChar(x, y);
}

char point::getChar(int _x, int _y)
{
	return pBoard->getChar(_x, _y);
}

char point::getFailChart()
{
	return pBoard->getFailChart(x, y);
}

char point::getFailChart(int _x, int _y)
{
	return pBoard->getFailChart(_x, _y);
}

void point::setFailChart(char c)
{
	pBoard->UpdateFailChart(x, y, c);
}

void point::setFailChart(int x, int y, char c)
{
	pBoard->UpdateFailChart(x, y, c);
}


