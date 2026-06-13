//
// Created by Karol Nalepa on 12/06/2026.
//

#include "rules/GameRules.h"
#include "validation/MoveValidator.h"
#include "attack/AttackDetector.h"

bool GameRules::hasAnyLegalMove(const Board& board, Color color)
{
    MoveValidator validator;

    for (int from = A1; from <= H8; from++) {

        Square fromSquare = static_cast<Square>(from);

        if (!board.isOccupied(fromSquare)) {
            continue;
        }

        if (board.getColor(fromSquare) != color) {
            continue;
        }

        for (int to = A1; to <= H8; to++) {

            Square toSquare = static_cast<Square>(to);

            Move move{
                fromSquare,
                toSquare,
                NONE
            };

            if (validator.isMoveLegal(board, move)) {
                return true;
            }
        }
    }

    return false;
}

bool GameRules::isCheckmate(const Board& board, Color color)
{
    Square kingSquare = (color == Color::White)
                        ? board.getWhiteKingSquare()
                        : board.getBlackKingSquare();

    Color enemyColor = (color == Color::White)
                       ? Color::Black
                       : Color::White;

    return AttackDetector::isSquareAttacked(board,
                                             kingSquare,
                                             enemyColor)
           &&
           !hasAnyLegalMove(board, color);
}

bool GameRules::isStalemate(const Board& board, Color color)
{
    Square kingSquare = (color == Color::White)
                        ? board.getWhiteKingSquare()
                        : board.getBlackKingSquare();

    Color enemyColor = (color == Color::White)
                       ? Color::Black
                       : Color::White;

    return !AttackDetector::isSquareAttacked(board,
                                              kingSquare,
                                              enemyColor)
           &&
           !hasAnyLegalMove(board, color);
}
