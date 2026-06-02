#ifndef PROJEKT2_NALEPA_PETELICKI_PIECEMOVEMENT_H
#define PROJEKT2_NALEPA_PETELICKI_PIECEMOVEMENT_H

#include "board/Board.h"
#include "move/Move.h"

namespace PieceMovement {

    bool isPawnMoveLegal(const Board& board, const Move& move);

    bool isKnightMoveLegal(const Board& board, const Move& move);

    bool isBishopMoveLegal(const Board& board, const Move& move);

    bool isRookMoveLegal(const Board& board, const Move& move);

    bool isQueenMoveLegal(const Board& board, const Move& move);

    bool isKingMoveLegal(const Board& board, const Move& move);

}

#endif // PROJEKT2_NALEPA_PETELICKI_PIECEMOVEMENT_H
