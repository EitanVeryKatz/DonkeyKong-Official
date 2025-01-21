#pragma once

#include "gameConfig.h"
#include "point.h"
#include "gameObject.h"

class player : protected gameObject
{
	static constexpr Direction directionsPlayer[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	enum icons {WITHOUT_HAMMER, WITH_HAMMER};
	enum directions { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, STAY = 4 };
	enum failCauses
	{
		BC, // Barrel Collision
		BE, // Barrel Explosion
		GC, // Ghost Collision
		FD, // Fall to Death
		OB  // Out of Bounds
	};
	static constexpr int STOP = 0, JUMPING_FARME = 2, DIR_DOWN = 1;
	int startX, startY;
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);;
	static constexpr char iconArr[] = { '@' ,'a'};
	char currIcon = iconArr[WITHOUT_HAMMER];
	static constexpr char hammerIcon = 'p';
	point hammerLocation;
	point hammerLocationSecondary;
	bool hasHammer = false;
	int midjump = 0;
	bool midswing = false;
	int fallCounter = 0;
public:
	using gameObject::setGameBoard;
	using gameObject::draw;
	using gameObject::erase;
	using gameObject::inLegend;
	player(int x, int y) : gameObject(x, y, iconArr[0]), startX(x), startY(y) {}
	void resetPlayer()
	{
		changeIcon(iconArr[WITHOUT_HAMMER]);
		currIcon = iconArr[WITHOUT_HAMMER];
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
	void move() override; // handle player's movement
	bool isAtVerticalBorder(int currX, int dirX) const; // Check if player is at vertical border
	bool isAtHorizontalBorder(int currY, int dirY) const; // Check if player is at horizontal border
	void handleVerticalBorder(int currX, int currY, int dirY, int& newX, int& newY) const; // Handle vertical border
	void handleHorizontalBorder(int currX, int currY, int dirX, int& newX, int& newY) const; // Handle horizontal border
	void handleInsideBorders(int currX, int currY, int dirX, int dirY, int& newX, int& newY); // Handle inside borders
	bool checkFail(size_t& cause) const; // Check if player failed
	bool checkWin() const; // Check if player won
	bool isFalling() const; // Check if player is falling
	int getHammerY() const { return hammerLocation.getY(); }
	int getHammerX() const { return hammerLocation.getX(); }
	void setHammerLocation();
	void setHammerLocation(int x, int y);
	bool doeshasHammer() const { return hasHammer; }
	void drawHammer() const
	{
		hammerLocation.draw(hammerIcon);
	}
	void swingHammer();
	void clearHammerSwing();
};

