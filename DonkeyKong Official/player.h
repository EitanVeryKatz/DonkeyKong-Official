#pragma once

#include "gameConfig.h"
#include "point.h"
#include "gameObject.h"

class player : public gameObject
{
	static constexpr Direction directionsPlayer[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	enum directions { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, STAY = 4 };
	static constexpr int STOP = 0, JUMPING_FARME = 2;
	int startX, startY;
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);;
	static constexpr char iconArr[] = { '@' ,'a'};
	char currIcon = iconArr[0];
	static constexpr char hammerIcon = 'p';
	point hammerLocation;
	bool hasHammer = false;
	int midjump = 0;
	bool midswing = false;
	int fallCounter = 0;
public:

	player(int x, int y) : gameObject(x, y, iconArr[0]), startX(x), startY(y) {}


	void resetPlayer()
	{
		changeIcon(iconArr[0]);
		currIcon = iconArr[0];
		midjump = 0;
		fallCounter = 0;
		setPosition(startX, startY);
		setDir(directionsPlayer[STAY]);
		hasHammer = false;
		midswing = 0;
		setHammerLocation();
	}
	bool isSwingingHammer() const { return midswing; }
	void keyPressed(char key); // Handle player's key press
	void checkHasHmmer();
	void moveInBoard(); // handle player's movement
	bool isAtVerticalBorder(int currX, int dirX); // Check if player is at vertical border
	bool isAtHorizontalBorder(int currY, int dirY); // Check if player is at horizontal border
	void handleVerticalBorder(int currX, int currY, int dirY, int& newX, int& newY); // Handle vertical border
	void handleHorizontalBorder(int currX, int currY, int dirX, int& newX, int& newY); // Handle horizontal border
	void handleInsideBorders(int currX, int currY, int dirX, int dirY, int& newX, int& newY); // Handle inside borders
	bool checkFail(); // Check if player failed
	bool checkWin(); // Check if player won
	bool isFalling(); // Check if player is falling
	int getHammerY() const { return hammerLocation.getY(); }
	int getHammerX() const { return hammerLocation.getX(); }
	void setHammerLocation();
	bool doeshasHammer() const { return hasHammer; }
	void drawHammer() const
	{
		hammerLocation.draw(hammerIcon);
	}
	void swingHammer();
	void clearHammerSwing();
};

