//
// Created by Karol Nalepa on 31/05/2026.
//
#include <cstdlib>
#include "../../include/validation/MoveValidator.h"


#include "board/Board.h"

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
            return isPawnMoveLegal(board, move);

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            return isKnightMoveLegal(board, move);

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            return isBishopMoveLegal(board, move);

        case WHITE_ROOK:
        case BLACK_ROOK:
            return isRookMoveLegal(board, move);

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            return isQueenMoveLegal(board, move);

        case WHITE_KING:
        case BLACK_KING:
            return isKingMoveLegal(board, move);

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

bool MoveValidator::isPawnMoveLegal(const Board &board, const Move &move) {

    // Relative move vector
    int fileDiff = getFile(move.to) - getFile(move.from);
    int rankDiff = getRank(move.to) - getRank(move.from);

    // White pawn movement rules
    if (board.isWhitePiece(move.from)) {

        // capture handle
        if (board.isBlackPiece(move.to) && rankDiff == 1 && std::abs(fileDiff) == 1)
        {
            return true;
        }

        // 1st rank special move
        if (rankDiff == 2 && fileDiff == 0) {

            if (getRank(move.from) != 1) {
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

            if (getRank(move.from) != 6) {
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

bool MoveValidator::isBishopMoveLegal(const Board &board, const Move &move) {

    int fileDiff = std::abs(getFile(move.to) - getFile(move.from));
    int rankDiff = std::abs(getRank(move.to) - getRank(move.from));

    if (fileDiff == 0 && rankDiff == 0) {
        return false;
    }

    if (fileDiff != rankDiff) {
        return false;
    }

    int step;
    int fromFile = getFile(move.from);
    int toFile = getFile(move.to);
    int fromRank = getRank(move.from);
    int toRank = getRank(move.to);

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

bool MoveValidator::isRookMoveLegal(const Board &board, const Move &move) {

    int fileDiff = std::abs(getFile(move.to) - getFile(move.from));
    int rankDiff = std::abs(getRank(move.to) - getRank(move.from));

    // Rook must move strictly horizontally or vertically
    if (fileDiff != 0 && rankDiff != 0 ||
        fileDiff == 0 && rankDiff == 0) {
        return false;
    }

    // Determine movement direction (+8, -8, +1, -1)
    int step;
    int fromFile = getFile(move.from);
    int toFile = getFile(move.to);

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

bool MoveValidator::isQueenMoveLegal(const Board &board, const Move &move) {
    return isRookMoveLegal(board, move) ||
       isBishopMoveLegal(board, move);
}

bool MoveValidator::isKingMoveLegal(const Board &board, const Move &move) {

    int fileDiff = std::abs(getFile(move.to) - getFile(move.from));
    int rankDiff = std::abs(getRank(move.to) - getRank(move.from));

    // King must actually move
    if (fileDiff == 0 && rankDiff == 0) {
        return false;
    }

    // King may move one square in any direction
    if (fileDiff <= 1 && rankDiff <= 1) {
        return true;
    }

    return false;
}



