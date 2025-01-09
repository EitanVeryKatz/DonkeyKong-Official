#include "hammer.h"

void hammer::move(int marioX,int marioY) {
	setPosition(marioX + dirX, marioY);
}