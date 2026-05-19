//
// Created by Karol Nalepa on 18/05/2026.
//

#include "utils/BitboardUtils.h"

#include <iostream>

void setBit(Bitboard& bb, int square){

    bb |= (1ULL << square);
}

void clearBit(Bitboard& bb, int square) {

    bb &= ~(1ULL << square);
}

bool getBit(Bitboard& bb, int square) {

    return (bb & (1ULL << square)) != 0;
}

void printBitboard(Bitboard bb) {

    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {

            int square = rank * 8 + file;
            std::cout << getBit(bb, square) << " ";
        }

        std::cout << std::endl;
    }
}
