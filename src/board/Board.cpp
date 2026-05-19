//
// Created by Karol Nalepa on 18/05/2026.
//

#include "../../include/board/Board.h"
#include  "../include/utils/BitboardUtils.h"
#include "board/Square.h"

void Board::setupStartingPosition() {

    whitePawns = 0;
    whiteKnights = 0;
    whiteBishops = 0;
    whiteRooks = 0;
    whiteQueens = 0;
    whiteKing = 0;

    blackPawns = 0;
    blackKnights = 0;
    blackBishops = 0;
    blackRooks = 0;
    blackQueens = 0;
    blackKing = 0;

    whitePieces = 0;
    blackPieces = 0;
    occupied = 0;

    setBit(whitePawns, A2);
    setBit(whitePawns, B2);
    setBit(whitePawns, C2);
    setBit(whitePawns, D2);
    setBit(whitePawns, E2);
    setBit(whitePawns, F2);
    setBit(whitePawns, G2);
    setBit(whitePawns, H2);

    setBit(whiteRooks, A1);
    setBit(whiteRooks, H1);

    setBit(whiteKnights, B1);
    setBit(whiteKnights, G1);

    setBit(whiteBishops, C1);
    setBit(whiteBishops, F1);

    setBit(whiteQueens, D1);
    setBit(whiteKing, E1);


    setBit(blackPawns, A7);
    setBit(blackPawns, B7);
    setBit(blackPawns, C7);
    setBit(blackPawns, D7);
    setBit(blackPawns, E7);
    setBit(blackPawns, F7);
    setBit(blackPawns, G7);
    setBit(blackPawns, H7);

    setBit(blackRooks, A8);
    setBit(blackRooks, H8);

    setBit(blackKnights, B8);
    setBit(blackKnights, G8);

    setBit(blackBishops, C8);
    setBit(blackBishops, F8);

    setBit(blackQueens, D8);
    setBit(blackKing, E8);

    whitePieces =
        whitePawns |
        whiteKnights |
        whiteBishops |
        whiteRooks |
        whiteQueens |
        whiteKing;

    blackPieces =
            blackPawns |
            blackKnights |
            blackBishops |
            blackRooks |
            blackQueens |
            blackKing;

    occupied = whitePieces | blackPieces;

}

bool Board::isOccupied(int square) {
    return getBit(occupied, square);
}

Piece Board::getPiece(int square) {

    if (getBit(whitePawns, square)) {
        return WHITE_PAWN;
    }

    if (getBit(whiteKnights, square)) {
        return WHITE_KNIGHT;
    }

    if (getBit(whiteBishops, square)) {
        return WHITE_BISHOP;
    }

    if (getBit(whiteRooks, square)) {
        return WHITE_ROOK;
    }

    if (getBit(whiteQueens, square)) {
        return WHITE_QUEEN;
    }

    if (getBit(whiteKing, square)) {
        return WHITE_KING;
    }

    if (getBit(blackPawns, square)) {
        return BLACK_PAWN;
    }

    if (getBit(blackKnights, square)) {
        return BLACK_KNIGHT;
    }

    if (getBit(blackBishops, square)) {
        return BLACK_BISHOP;
    }

    if (getBit(blackRooks, square)) {
        return BLACK_ROOK;
    }

    if (getBit(blackQueens, square)) {
        return BLACK_QUEEN;
    }

    if (getBit(blackKing, square)) {
        return BLACK_KING;
    }

    return NONE;
}

