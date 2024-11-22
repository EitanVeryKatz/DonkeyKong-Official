#include "gameConfig.h"
#include <iostream>
#include <algorithm>

class Floor;

void gotoxy(int x, int y)
{
	std::cout.flush();
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showCurserOnConsole(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void DisplayLayout::addPlatform(Floor* newPlatform) {
	Floor** newArr = new Floor * [PlatformNum + 1];
	if (PlatformNum > 0) {//if currently game cpntains platforms
		std::copy(platformArr, platformArr + PlatformNum, newArr);//copy existing platforms to new arr
		delete[]platformArr;//deleto old arr
	}
	newArr[PlatformNum] = newPlatform;//ad new platform to arr
	platformArr = newArr;//update arr to current
	PlatformNum++;//update number of platforms
}
