//
// Created by Karol Nalepa on 31/05/2026.
//
#include <cstdlib>
#include "validation/MoveValidator.h"

#include <ranges>


#include "attack/AttackDetector.h"
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
    bool pseudoLegal = false;

    Piece piece = board.getPiece(move.from);

    // Capturing the king is not allowed
    if (board.isOccupied(move.to)) {
        Piece targetPiece = board.getPiece(move.to);
        if (targetPiece == WHITE_KING ||
            targetPiece == BLACK_KING) {
            return false;
        }
    }
    // Promotion validation
    if (piece == WHITE_PAWN && Board::getRank(move.to) == 7) {

        if (move.promotionPiece != WHITE_QUEEN &&
            move.promotionPiece != WHITE_ROOK &&
            move.promotionPiece != WHITE_BISHOP &&
            move.promotionPiece != WHITE_KNIGHT) {
            return false;
        }
    }

    if (piece == BLACK_PAWN && Board::getRank(move.to) == 0) {

        if (move.promotionPiece != BLACK_QUEEN &&
            move.promotionPiece != BLACK_ROOK &&
            move.promotionPiece != BLACK_BISHOP &&
            move.promotionPiece != BLACK_KNIGHT) {
            return false;
        }
    }

    // Promotion piece may only be provided on promotion moves
    if (move.promotionPiece != NONE) {

        if (!(piece == WHITE_PAWN && Board::getRank(move.to) == 7) &&
            !(piece == BLACK_PAWN && Board::getRank(move.to) == 0)) {
            return false;
        }
    }
    switch (piece) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            pseudoLegal = PieceMovement::isPawnMoveLegal(board, move);
            break;

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            pseudoLegal = PieceMovement::isKnightMoveLegal(board, move);
            break;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            pseudoLegal = PieceMovement::isBishopMoveLegal(board, move);
            break;

        case WHITE_ROOK:
        case BLACK_ROOK:
            pseudoLegal = PieceMovement::isRookMoveLegal(board, move);
            break;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            pseudoLegal = PieceMovement::isQueenMoveLegal(board, move);
            break;

        case WHITE_KING:
        case BLACK_KING:
            pseudoLegal = PieceMovement::isKingMoveLegal(board, move);
            break;

        default:
            pseudoLegal = false;
    }

    if (!pseudoLegal) {
        return false;
    }

    Color movingColor;

    if (board.isWhitePiece(move.from))
        movingColor = Color::White;
    else
        movingColor = Color::Black;

    Board copy = board;
    copy.makeMove(move);

    if (AttackDetector::isKingAttacked(copy,movingColor)) {
        return false;
    }
    return true;

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


