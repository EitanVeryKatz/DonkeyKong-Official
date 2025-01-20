
#include "game.h"
#include <stdlib.h>
#include "gameConfig.h"
int main()
{
	srand(SEED);
	game g;
	g.displayMenu();
	return 0;
}