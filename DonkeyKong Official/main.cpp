
#include "game.h"
#include <ctime>
#include <stdlib.h>
#include "gameConfig.h"
int main(int argc, char* argv[])
{
	int currentSeed = SEED;
	if (argc == 1 || (argc > 1 && strcmp(argv[1], "-save") == 0)) {
		currentSeed = static_cast<int>(time(nullptr));//generate random seed based on current time
	}
	srand(currentSeed);
	
	if (argc > 1)
	{
		game g(currentSeed,argv[1]);
		g.displayMenu();
	}
	else
	{
		game g(currentSeed);
		g.displayMenu();
	}
	return 0;
}