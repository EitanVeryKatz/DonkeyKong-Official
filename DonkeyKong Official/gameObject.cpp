#include "gameObject.h"


bool gameObject::isOnFloor() const
{
	if (pBoard->getChar(position.getX(), position.getY() + 1) == '<' || pBoard->getChar(position.getX(), position.getY() + 1) == '>' || pBoard->getChar(position.getX(), position.getY() + 1) == '=')
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

int gameObject::getDirX() const
{
	return position.getNextPos().getX() - position.getX();
}

int gameObject::getDirY() const
{
	return position.getNextPos().getY() - position.getY();
}

void gameObject::move(direction d)
{
	position.setNewPos(d);
}

void gameObject::restoreBoardChar(int x, int y) const
{
	gotoxy(x, y);
	std::cout << pBoard->getChar(x, y);
}

