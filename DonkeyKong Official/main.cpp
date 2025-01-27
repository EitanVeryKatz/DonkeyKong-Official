
#include "game.h"
#include "automatic_game.h"
#include <ctime>
#include <stdlib.h>
#include "gameConfig.h"

int main(int argc, char* argv[])
{

	masterGame*pgame = nullptr;
	
	if (argc > 1){
		if (strcmp(argv[1], "-save") == 0) {
			pgame = new game(argv[1]);
		}
		else if (strcmp(argv[1], "-load") == 0) {
			if (argc > 2) {
				pgame = new automatic_game(argv[2]);
			}
			else {
				pgame = new automatic_game();
			}
		}
		else {
			pgame = new game();
		}
	}
	else
	{
		pgame = new game();
	}
	pgame->run();
	delete pgame;
	return 0;
}