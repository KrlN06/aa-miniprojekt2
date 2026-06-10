#include "pieces/PieceMovement.h"

#include <cmath>

#include "attack/AttackDetector.h"

namespace PieceMovement {
//
// Created by Karol Nalepa on 02/06/2026.
//
bool isPawnMoveLegal(const Board &board, const Move &move) {

    // Relative move vector
    int fileDiff = Board::getFile(move.to) - Board::getFile(move.from);
    int rankDiff = Board::getRank(move.to) - Board::getRank(move.from);

    // White pawn movement rules
    if (board.isWhitePiece(move.from)) {

        // capture handle
        if (board.isBlackPiece(move.to) && rankDiff == 1 && std::abs(fileDiff) == 1)
        {
            return true;
        }

        // 1st rank special move
        if (rankDiff == 2 && fileDiff == 0) {

            if (Board::getRank(move.from) != 1) {
                return false;
            }

            if (board.isOccupied(move.from + 8)) {
                return false;
            }

            if (board.isOccupied(move.to)) {
                return false;
            }

            return true;
        }

        // normal move
        if (rankDiff == 1 && fileDiff == 0) {

            if (board.isOccupied(move.to)) {
                return false;
            }

            return true;
        }

        return false;
    }

    // Black pawn movement rules

    if (board.isBlackPiece(move.from)) {

        // capture handle
        if (board.isWhitePiece(move.to) && rankDiff == -1 && std::abs(fileDiff) == 1)
        {
            return true;
        }

        // 1st rank special move
        if (rankDiff == -2 && fileDiff == 0) {

            if (Board::getRank(move.from) != 6) {
                return false;
            }

            if (board.isOccupied(move.from - 8)) {
                return false;
            }

            if (board.isOccupied(move.to)) {
                return false;
            }

            return true;
        }

        // normal move
        if (rankDiff == -1 && fileDiff == 0) {

            if (board.isOccupied(move.to)) {
                return false;
            }

            return true;
        }

        return false;
    }

    return false;
}

bool isKnightMoveLegal(const Board &board, const Move &move) {
    int fileDiff = std::abs(Board::getFile(move.to) - Board::getFile(move.from));
    int rankDiff = std::abs(Board::getRank(move.to) - Board::getRank(move.from));

    if (fileDiff == 2 && rankDiff == 1) {
        return true;
    }
    else if (fileDiff == 1 && rankDiff == 2) {
        return true;
    }

    return false;
}

bool isBishopMoveLegal(const Board &board, const Move &move) {

    int fileDiff = std::abs(Board::getFile(move.to) - Board::getFile(move.from));
    int rankDiff = std::abs(Board::getRank(move.to) - Board::getRank(move.from));

    if (fileDiff == 0 && rankDiff == 0) {
        return false;
    }

    if (fileDiff != rankDiff) {
        return false;
    }

    int step;
    int fromFile = Board::getFile(move.from);
    int toFile = Board::getFile(move.to);
    int fromRank = Board::getRank(move.from);
    int toRank = Board::getRank(move.to);

    if (fromFile > toFile && fromRank > toRank) {
        step = -9;
    } else if (fromFile < toFile && fromRank > toRank) {
        step = -7;
    } else if (fromFile < toFile && fromRank < toRank) {
        step = 9;
    } else if (fromFile > toFile && fromRank < toRank) {
        step = 7;
    } else {
        return false;
    }

    int current = move.from + step;

    while (current != move.to) {
        if (board.isOccupied(current))
            return false;

        current += step;
    }

    return true;

}

bool isRookMoveLegal(const Board &board, const Move &move) {

    int fileDiff = std::abs(Board::getFile(move.to) - Board::getFile(move.from));
    int rankDiff = std::abs(Board::getRank(move.to) - Board::getRank(move.from));

    // Rook must move strictly horizontally or vertically
    if (fileDiff != 0 && rankDiff != 0 ||
        fileDiff == 0 && rankDiff == 0) {
        return false;
    }

    // Determine movement direction (+8, -8, +1, -1)
    int step;
    int fromFile = Board::getFile(move.from);
    int toFile = Board::getFile(move.to);

    if (fromFile == toFile)
        step = (move.to > move.from) ? 8 : -8;
    else
        step = (move.to > move.from) ? 1 : -1;

    // Check every intermediate square for blockers
    int current = move.from + step;

    while (current != move.to)
    {
        if (board.isOccupied(current))
            return false;

        current += step;
    }

    return true;

}

bool isQueenMoveLegal(const Board &board, const Move &move) {
    return isRookMoveLegal(board, move) ||
       isBishopMoveLegal(board, move);
}

bool isKingMoveLegal(const Board &board, const Move &move) {

    int fileDiff = std::abs(Board::getFile(move.to) - Board::getFile(move.from));
    int rankDiff = std::abs(Board::getRank(move.to) - Board::getRank(move.from));

    // King must actually move
    if (fileDiff == 0 && rankDiff == 0) {
        return false;
    }

    // King may move one square in any direction
    if (fileDiff <= 1 && rankDiff <= 1) {
        return true;
    }


    // CASTLING

    Color kingColor = board.getColor(move.from);

    if (kingColor == Color::White && move.from == E1) { // white king

        // King side castling
        if (move.to == G1) {

            if (board.getWhiteKingMoved()) {
                return false;
            }

            if (board.getWhiteKingsideRookMoved() || board.getPiece(H1) != WHITE_ROOK) {
                return false;
            }

            if (board.isOccupied(F1) || board.isOccupied(G1)) {
                return false;
            }

            if (AttackDetector::isSquareAttacked(board, E1, Color::Black) ||
                AttackDetector::isSquareAttacked(board, F1, Color::Black) ||
                AttackDetector::isSquareAttacked(board, G1, Color::Black)) {
                return false;
            }

            return true;
        }

        // Queen side castling
        if (move.to == C1) {

            if (board.getWhiteKingMoved()) {
                return false;
            }

            if (board.getWhiteQueensideRookMoved() || board.getPiece(A1) != WHITE_ROOK) {
                return false;
            }

            if (board.isOccupied(B1) ||
                board.isOccupied(C1) ||
                board.isOccupied(D1)) {
                return false;
            }

            if (AttackDetector::isSquareAttacked(board, E1, Color::Black) ||
                AttackDetector::isSquareAttacked(board, D1, Color::Black) ||
                AttackDetector::isSquareAttacked(board, C1, Color::Black)) {
                return false;
            }

            return true;
        }
    }

    if (kingColor == Color::Black && move.from == E8) { // black king

        // King side castling
        if (move.to == G8) {

            if (board.getBlackKingMoved()) {
                return false;
            }

            if (board.getBlackKingsideRookMoved() || board.getPiece(H8) != BLACK_ROOK) {
                return false;
            }

            if (board.isOccupied(F8) || board.isOccupied(G8)) {
                return false;
            }

            if (AttackDetector::isSquareAttacked(board, E8, Color::White) ||
                AttackDetector::isSquareAttacked(board, F8, Color::White) ||
                AttackDetector::isSquareAttacked(board, G8, Color::White)) {
                return false;
            }

            return true;
        }

        // Queen side castling
        if (move.to == C8) {

            if (board.getBlackKingMoved()) {
                return false;
            }

            if (board.getBlackQueensideRookMoved() || board.getPiece(A8) != BLACK_ROOK) {
                return false;
            }

            if (board.isOccupied(B8) ||
                board.isOccupied(C8) ||
                board.isOccupied(D8)) {
                return false;
            }

            if (AttackDetector::isSquareAttacked(board, E8, Color::White) ||
                AttackDetector::isSquareAttacked(board, D8, Color::White) ||
                AttackDetector::isSquareAttacked(board, C8, Color::White)) {
                return false;
            }

            return true;
        }
    }


    return false;
}

}
