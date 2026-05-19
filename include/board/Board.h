//
// Created by Karol Nalepa on 18/05/2026.
//

#ifndef PROJEKT2_NALEPA_PETELICKI_BOARD_H
#define PROJEKT2_NALEPA_PETELICKI_BOARD_H
#include "utils/Types.h"
#include "pieces/Pieces.h"


class Board {

    public:
    Bitboard whitePawns;
    Bitboard blackPawns;
    Bitboard whiteKnights;
    Bitboard blackKnights;
    Bitboard whiteBishops;
    Bitboard blackBishops;
    Bitboard whiteRooks;
    Bitboard blackRooks;
    Bitboard whiteQueens;
    Bitboard blackQueens;
    Bitboard whiteKing;
    Bitboard blackKing;

    Bitboard whitePieces;
    Bitboard blackPieces;
    Bitboard occupied;

    void setupStartingPosition();
    bool isOccupied(int square);
    Piece getPiece(int square);

};



#endif //PROJEKT2_NALEPA_PETELICKI_BOARD_H
