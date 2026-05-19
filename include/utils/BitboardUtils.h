//
// Created by Karol Nalepa on 18/05/2026.
//

#ifndef PROJEKT2_NALEPA_PETELICKI_BITBOARDUTILS_H
#define PROJEKT2_NALEPA_PETELICKI_BITBOARDUTILS_H
#include "Types.h"

void setBit(Bitboard& bb, int square);
void clearBit(Bitboard& bb, int square);
bool getBit(Bitboard& bb, int square);
void printBitboard(Bitboard bb);

#endif //PROJEKT2_NALEPA_PETELICKI_BITBOARDUTILS_H
