//
// Created by Karol Nalepa on 31/05/2026.
//
#include <cstdlib>
#include "MoveValidator.h"
#include "board/Board.h"

bool MoveValidator::isMoveLegal(const Board &board, const Move &move) {

    if (move.from < A1 || move.from > H8 ||
        move.to < A1 || move.to > H8) {
        return false;
    }

    if (board.getPiece(move.from) == NONE) {
        return false;
    }

    if (isOwnPieceOnTarget(board, move)) {
        return false;
    }

    Piece piece = board.getPiece(move.from);
    switch (piece) {
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            return isKnightMoveLegal(board, move);


        default:
            return true;
    }
}

int MoveValidator::getRank(Square square) {
    return square / 8;
}
int MoveValidator::getFile(Square square) {
    return square % 8;
}

bool MoveValidator::isOwnPieceOnTarget(const Board &board, const Move &move) {
    //Check if you don't capture own piece
    if (board.isWhitePiece(move.from)) {
        if (board.isWhitePiece(move.to)) {
            return true;
        }
    }
    if (board.isBlackPiece(move.from)) {
        if (board.isBlackPiece(move.to)) {
            return true;
        }
    }
    return false;
}

bool MoveValidator::isPawnMoveLegal(const Board &board, const Move &move) {
    
}

bool MoveValidator::isKnightMoveLegal(const Board &board, const Move &move) {
    int fileDiff = std::abs(getFile(move.to) - getFile(move.from));
    int rankDiff = std::abs(getRank(move.to) - getRank(move.from));

    if (fileDiff == 2 && rankDiff == 1) {
        return true;
    }
    else if (fileDiff == 1 && rankDiff == 2) {
        return true;
    }

    return false;
}

