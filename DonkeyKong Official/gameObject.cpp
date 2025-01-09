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

void gameObject::move(direction d)
{
	position.setNewPos(d);
	restoreBoardChar(getX() - d.x, getY() - d.y);
}

void gameObject::restoreBoardChar(int x, int y) const
{
	gotoxy(x, y);
	std::cout << pBoard->getChar(x, y);
}

direction gameObject::calcDir(int newX, int newY) const
{
	direction d;
	int dirX = newX - getX();
	int dirY = newY - getY();
	d.x = dirX;
	d.y = dirY;
	return d;
}

void gameObject::setFailChart(char c) {
	pBoard->UpdateFailChart(getX(), getY(), c);
}