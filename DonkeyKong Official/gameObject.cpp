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

void gameObject::setFailChart(char c)
{
	pBoard->UpdateFailChart(position.getX(), position.getY(), c);
}

void gameObject::setFailChart(int x, int y, char c)
{
	pBoard->UpdateFailChart(x, y, c);
}

void gameObject::restoreBoardChar(int x, int y)
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

void gameObject::ghostColide(int x, int y)
{
	for (auto itr = pBoard->getNPCVectorBegin(); itr != pBoard->getNPCVectorEnd(); ++itr)
	{
		if ((*itr)->getX() == x && (*itr)->getY() == y && dynamic_cast<ghost*>(*itr))
		{
			ghost* pGhost = dynamic_cast<ghost*>(*itr);
			pGhost->changeDirection();
		}
		
	}
}
