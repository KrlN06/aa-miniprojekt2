//
// Created by Karol Nalepa on 12/06/2026.
//

#ifndef PROJEKT2_NALEPA_PETELICKI_GAMERULES_H
#define PROJEKT2_NALEPA_PETELICKI_GAMERULES_H

#include "board/Board.h"

class GameRules {
public:

    static bool hasAnyLegalMove(const Board& board, Color color);

    static bool isCheckmate(const Board& board, Color color);

    static bool isStalemate(const Board& board, Color color);
};



#endif //PROJEKT2_NALEPA_PETELICKI_GAMERULES_H
