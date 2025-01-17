#include "gameObject.h"
#include "boardGame.h"
#include "ghost.h"

bool gameObject::isOnFloor() const
{
	if (pBoard->getChar(position.getX(), position.getY() + 1) == '<' || pBoard->getChar(position.getX(), position.getY() + 1) == '>' || pBoard->getChar(position.getX(), position.getY() + 1) == '=')
	{
		return true;
	}
	return false;
}

bool gameObject::isOnFloor(int x, int y) const
{
	if (pBoard->getChar(x, y + 1) == '<' || pBoard->getChar(x, y + 1) == '>' || pBoard->getChar(x, y + 1) == '=')
	{
		return true;
	}
	return false;
}

bool gameObject::isOnLadder() const
{
	if (pBoard->getChar(position.getX(), position.getY()) == 'H' || (pBoard->getChar(position.getX(), position.getY() + 1) == 'H' && (pBoard->getChar(position.getX(), position.getY()) == '<' || pBoard->getChar(position.getX(), position.getY()) == '>' || pBoard->getChar(position.getX(), position.getY()) == '=')))
	{
		return true;
	}
	return false;
}

char gameObject::getFailChart() const
{
	return pBoard->getFailChart(position.getX(), position.getY());
}

char gameObject::getFailChart(int x, int y) const
{
	return pBoard->getFailChart(x, y);
}

void gameObject::setFailChart(char c) const
{
	pBoard->UpdateFailChart(position.getX(), position.getY(), c);
}

void gameObject::setFailChart(int x, int y, char c) const
{
	pBoard->UpdateFailChart(x, y, c);
}

void gameObject::restoreBoardChar(int x, int y) const
{
	gotoxy(x, y);
	std::cout << pBoard->getChar(x, y);
}

char gameObject::getChar() const
{
	return pBoard->getChar(getX(), getY());
}

char gameObject::getChar(int x, int y) const
{
	return pBoard->getChar(x, y);
}

void gameObject::inLegend(bool& needToRedraw) const
{
	int currX = getX(), currY = getY();
	int LStartX = pBoard->getLx(), LStartY = pBoard->getLy();
	if (currX >= LStartX && currX < LStartX + L_LENGTH && currY >= LStartY && currY < LStartY + L_HEIGHT)
	{
		needToRedraw = true;
	}
}

