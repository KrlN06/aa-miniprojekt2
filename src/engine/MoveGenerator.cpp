#include "engine/MoveGenerator.h"
#include "validation/MoveValidator.h"

std::vector<Move> MoveGenerator::generateLegalMoves(const Board& board, Color color) {
    std::vector<Move> legalMoves;
    MoveValidator validator;

    for (int fromSrc = 0; fromSrc < 64; ++fromSrc) {
        Square from = static_cast<Square>(fromSrc);

        if (color == Color::White && !board.isWhitePiece(fromSrc)) continue;
        if (color == Color::Black && !board.isBlackPiece(fromSrc)) continue;

        for (int toDest = 0; toDest < 64; ++toDest) {
            Square to = static_cast<Square>(toDest);

            Move move{from, to};

            if (validator.isMoveLegal(board, move)) {
                legalMoves.push_back(move);
            }
        }
    }

    return legalMoves;
}
