//
// Created by Karol Nalepa on 02/06/2026.
//

#ifndef PROJEKT2_NALEPA_PETELICKI_ATTACKDETECTOR_H
#define PROJEKT2_NALEPA_PETELICKI_ATTACKDETECTOR_H

#include "utils/Types.h"
#include "board/Board.h"

#include "move/Move.h"


class AttackDetector {
public:
    static bool isSquareAttacked(
        const Board& board,
        Square square,
        Color attackerColor
    );

    static bool isKingAttacked(
        const Board& board,
        Color kingColor
    );
};



#endif //PROJEKT2_NALEPA_PETELICKI_ATTACKDETECTOR_H
