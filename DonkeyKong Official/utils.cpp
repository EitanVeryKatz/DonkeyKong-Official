#include "utils.h"
#include <iostream>
#include <algorithm>
#include <conio.h>


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


void clear_key_buffer() 
{
	while (_kbhit()) 
	{
		(void)_getch();  // Consume the key in the buffer
	}
}





