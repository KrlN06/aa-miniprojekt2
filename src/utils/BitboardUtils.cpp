//
// Created by Karol Nalepa on 18/05/2026.
//

#include "utils/BitboardUtils.h"

#include <iostream>
#include <cctype>
#include <stdexcept>
#include "board/Square.h"

void setBit(Bitboard& bb, int square){

    bb |= (1ULL << square);
}

void clearBit(Bitboard& bb, int square) {

    bb &= ~(1ULL << square);
}

bool getBit(const Bitboard& bb, int square) {

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

Square stringToSquare(const std::string& str)
{
    if (str.size() != 2) {
        throw std::invalid_argument("Invalid square format");
    }

    char file = static_cast<char>(std::toupper(str[0]));
    char rank = str[1];

    if (file < 'A' || file > 'H' ||
        rank < '1' || rank > '8') {
        throw std::invalid_argument("Invalid square format");
    }

    int fileIndex = file - 'A';
    int rankIndex = rank - '1';

    return static_cast<Square>(rankIndex * 8 + fileIndex);
}

std::string squareToString(Square square)
{
    int value = static_cast<int>(square);

    if (value < 0 || value > 63) {
        return "??";
    }

    char file = static_cast<char>('A' + (value % 8));
    char rank = static_cast<char>('1' + (value / 8));

    return std::string{file, rank};
}
