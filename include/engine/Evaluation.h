#ifndef PROJEKT2_NALEPA_PETELICKI_EVALUATION_H
#define PROJEKT2_NALEPA_PETELICKI_EVALUATION_H

#include "../board/Board.h"

class Evaluation {
public:
    static const int mgPieceValues[13];
    static const int egPieceValues[13];

    static const int mgPawnPST[64];
    static const int egPawnPST[64];

    static const int mgKnightPST[64];
    static const int egKnightPST[64];

    static const int mgQueenPST[64];
    static const int egQueenPST[64];

    static const int mgKingPST[64];
    static const int egKingPST[64];

    static const int mgRookPST[64];
    static const int egRookPST[64];

    static const int mgBishopPST[64];
    static const int egBishopPST[64];

    static int evaluate(const Board& board);

private:
    static int getGamePhase(const Board& board);
};

#endif // PROJEKT2_NALEPA_PETELICKI_EVALUATION_H