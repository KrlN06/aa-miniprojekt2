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

    bool isOwnPieceOnTarget(const Board &board, const Move &move);
};


#endif //PROJEKT2_NALEPA_PETELICKI_MOVEVALIDATOR_H
