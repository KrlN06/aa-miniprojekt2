//
// Created by Karol Nalepa on 31/05/2026.
//
#include <cstdlib>
#include "../../include/validation/MoveValidator.h"


#include "board/Board.h"
#include "pieces/PieceMovement.h"

bool MoveValidator::isMoveLegal(const Board &board, const Move &move) {
    // Basic board boundaries validation
    if (move.from < A1 || move.from > H8 ||
        move.to < A1 || move.to > H8) {
        return false;
    }

    // Source square must contain a piece
    if (board.getPiece(move.from) == NONE) {
        return false;
    }

    // Capturing own piece is not allowed
    if (isOwnPieceOnTarget(board, move)) {
        return false;
    }

    // Dispatch validation based on piece type
    Piece piece = board.getPiece(move.from);
    switch (piece) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            return PieceMovement::isPawnMoveLegal(board, move);

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            return PieceMovement::isKnightMoveLegal(board, move);

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            return PieceMovement::isBishopMoveLegal(board, move);

        case WHITE_ROOK:
        case BLACK_ROOK:
            return PieceMovement::isRookMoveLegal(board, move);

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            return PieceMovement::isQueenMoveLegal(board, move);

        case WHITE_KING:
        case BLACK_KING:
            return PieceMovement::isKingMoveLegal(board, move);

        default:
            return true;
    }
}



bool MoveValidator::isOwnPieceOnTarget(const Board &board, const Move &move) {
    // Check whether the target square contains a friendly piece
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



