#include "utils.h"



int randomBit() {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }
    return rand() % 2;
}

