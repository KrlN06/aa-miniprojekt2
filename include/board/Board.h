//
// Created by Karol Nalepa on 18/05/2026.
//

#ifndef PROJEKT2_NALEPA_PETELICKI_BOARD_H
#define PROJEKT2_NALEPA_PETELICKI_BOARD_H
#include "utils/Types.h"
#include "pieces/Pieces.h"
#include "move/Move.h"


class  Board {

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

    bool getWhiteKingMoved() const;
    bool getBlackKingMoved() const;
    bool getWhiteKingsideRookMoved() const;
    bool getBlackKingsideRookMoved() const;
    bool getWhiteQueensideRookMoved() const;
    bool getBlackQueensideRookMoved() const;
    Color getColor(Square square) const;

    Square getEnPassantSquare() const;

    static int getRank(Square square);
    static int getFile(Square square);

private:
    Square whiteKingSquare;
    Square blackKingSquare;
    Square enPassantSquare = NO_SQUARE;

    bool whiteKingMoved = false;
    bool blackKingMoved = false;

    bool whiteKingsideRookMoved = false;
    bool whiteQueensideRookMoved = false;

    bool blackKingsideRookMoved = false;
    bool blackQueensideRookMoved = false;

};



#endif //PROJEKT2_NALEPA_PETELICKI_BOARD_H
