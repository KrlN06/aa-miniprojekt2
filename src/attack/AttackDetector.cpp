//
// Created by Karol Nalepa on 02/06/2026.
//

#include "attack/AttackDetector.h"
#include "board/Board.h"
#include "move/Move.h"
#include "pieces/PieceMovement.h"
#include "utils/Types.h"


bool AttackDetector::isSquareAttacked(
    const Board& board,
    Square square,
    Color attackerColor)
{

    for (int from = A1; from <= H8; from++) {
        Piece piece = board.getPiece(from);

        if (piece == NONE)
            continue;

        if (attackerColor == Color::White && !board.isWhitePiece(from))
            continue;

        if (attackerColor == Color::Black && !board.isBlackPiece(from))
            continue;


        Move move{
            static_cast<Square>(from),
            square
        };

        switch(piece)
        {
            case WHITE_KNIGHT:
            case BLACK_KNIGHT:
                if (PieceMovement::isKnightMoveLegal(board, move))
                    return true;
                break;

            case WHITE_BISHOP:
            case BLACK_BISHOP:
                if (PieceMovement::isBishopMoveLegal(board, move))
                    return true;
                break;

            case WHITE_ROOK:
            case BLACK_ROOK:
                if (PieceMovement::isRookMoveLegal(board, move))
                    return true;
                break;

            case WHITE_QUEEN:
            case BLACK_QUEEN:
                if (PieceMovement::isQueenMoveLegal(board, move))
                    return true;
                break;

            case WHITE_KING:
            case BLACK_KING:
                if (PieceMovement::isKingMoveLegal(board, move))
                    return true;
                break;

            default:
                break;
        }
    }

    return false;
}

bool AttackDetector::isKingAttacked(
    const Board& board,
    Color kingColor)
{
    Square kingSquare;

    if (kingColor == Color::White)
        kingSquare = board.getWhiteKingSquare();
    else
        kingSquare = board.getBlackKingSquare();

    Color attackerColor =
        (kingColor == Color::White)
            ? Color::Black
            : Color::White;

    return isSquareAttacked(
        board,
        kingSquare,
        attackerColor
    );
}

