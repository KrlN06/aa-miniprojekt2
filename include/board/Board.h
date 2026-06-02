//
// Created by Karol Nalepa on 18/05/2026.
//

#ifndef PROJEKT2_NALEPA_PETELICKI_BOARD_H
#define PROJEKT2_NALEPA_PETELICKI_BOARD_H
#include "utils/Types.h"
#include "pieces/Pieces.h"
#include "move/Move.h"


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
    bool isOccupied(int square) const;
    Piece getPiece(int square) const;
    void printBoard() const;
    bool isWhitePiece(int square) const;
    bool isBlackPiece(int square) const;
    void makeMove(const Move& move);
    void removePiece(Piece piece, Square square);
    void addPiece(Piece piece, Square square);
    void updateOccupancy();

    Square getWhiteKingSquare() const;
    Square getBlackKingSquare() const;

    static int getRank(Square square);
    static int getFile(Square square);

private:
    Square whiteKingSquare;
    Square blackKingSquare;

};



#endif //PROJEKT2_NALEPA_PETELICKI_BOARD_H
