

#include "../include/utils/BitboardUtils.h"
#include <iostream>

int main()
{
    Bitboard bb = 0;

    setBit(bb, 0);
    setBit(bb, 4);
    setBit(bb, 63);

    printBitboard(bb);

    return 0;
}
