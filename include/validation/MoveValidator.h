//
// Created by Karol Nalepa on 31/05/2026.
//

#ifndef PROJEKT2_NALEPA_PETELICKI_MOVEVALIDATOR_H
#define PROJEKT2_NALEPA_PETELICKI_MOVEVALIDATOR_H
#include "board/Board.h"


class MoveValidator {

public:
    bool isMoveLegal(const Board& board, const Move& move);

private:
    int getRank(Square square);
    int getFile(Square square);

    bool isOwnPieceOnTarget(const Board& board, const Move& move);
    bool isPawnMoveLegal(const Board& board, const Move& move);
    bool isKnightMoveLegal(const Board& board, const Move& move);
    bool isBishopMoveLegal(const Board& board, const Move& move);
    bool isRookMoveLegal(const Board& board, const Move& move);
    bool isQueenMoveLegal(const Board& board, const Move& move);
    bool isKingMoveLegal(const Board& board, const Move& move);
};


#endif //PROJEKT2_NALEPA_PETELICKI_MOVEVALIDATOR_H
