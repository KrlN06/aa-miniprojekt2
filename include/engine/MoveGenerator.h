#ifndef PROJEKT2_NALEPA_PETELICKI_MOVEGENERATOR_H
#define PROJEKT2_NALEPA_PETELICKI_MOVEGENERATOR_H
	
#include <vector>
#include "board/Board.h"
#include "move/Move.h"

class MoveGenerator {
public:
    static std::vector<Move> generateLegalMoves(const Board& board, Color color);
};

#endif // PROJEKT2_NALEPA_PETELICKI_MOVEGENERATOR_H
