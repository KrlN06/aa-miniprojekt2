//
// Created by Karol Nalepa on 18/05/2026.
//

#ifndef PROJEKT2_NALEPA_PETELICKI_BITBOARDUTILS_H
#define PROJEKT2_NALEPA_PETELICKI_BITBOARDUTILS_H
#include "Types.h"
#include "board/Square.h"
#include <string>

void setBit(Bitboard& bb, int square);
void clearBit(Bitboard& bb, int square);
bool getBit(const Bitboard& bb, int square);
void printBitboard(Bitboard bb);

Square stringToSquare(const std::string& str);
std::string squareToString(Square square);

#endif //PROJEKT2_NALEPA_PETELICKI_BITBOARDUTILS_H
