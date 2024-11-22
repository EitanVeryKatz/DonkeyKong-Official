#pragma once

#include <windows.h>
class Floor;

void gotoxy(int x, int y);
void showCurserOnConsole(bool showFlag);

class DisplayLayout {//class to contain platforms, borders, and every non moving object displayed

private:
	int maxBoderX, minBorderX, maxBorderY, minBorderY;//border settings
	int PlatformNum = 0;
	Floor** platformArr = nullptr;
public:
	void addPlatform(Floor* newPlatform);//adds platform to platformArr and updates PlatformNum

};