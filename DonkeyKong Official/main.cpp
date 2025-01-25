
#include "game.h"
#include "automatic_game.h"
#include <ctime>
#include <stdlib.h>
#include "gameConfig.h"

int main(int argc, char* argv[])
{
	
	if (argc > 1)
	{
		if (strcmp(argv[1], "-save") == 0)
		{
			game g (argv[1]);
			g.displayMenu();
		}
		else if (strcmp(argv[1], "-load") == 0)
		{
			if (argc > 2)
			{
				automatic_game ag(argv[2]);
				ag.fileManager();
			}
			else
			{
				automatic_game ag;
				ag.fileManager();
			}

		}
		else
		{
			game g;
			g.displayMenu();
		}
	}
	else
	{
		game g;
		g.displayMenu();
	}
	return 0;
}