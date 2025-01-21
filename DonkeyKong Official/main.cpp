
#include "game.h"
#include <stdlib.h>
#include "gameConfig.h"
int main(int argc, char* argv[])
{
	srand(SEED);
	if (argc > 1)
	{
		game g(argv[1]);
		g.displayMenu();
	}
	else
	{
		game g;
		g.displayMenu();
	}
	return 0;
}