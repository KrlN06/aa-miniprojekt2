#ifndef PROJEKT2_NALEPA_PETELICKI_CHESSAI_H
#define PROJEKT2_NALEPA_PETELICKI_CHESSAI_H
	
#include "board/Board.h"
#include "move/Move.h"

class Engine {
public:
    static Move getBestMove(const Board& board, Color aiColor, int depth);
    static uint64_t nodesEvaluated;

private:
    static int minimax(const Board& board, int depth, int alpha, int beta, bool isMaximizingWhite);
};

#endif // PROJEKT2_NALEPA_PETELICKI_CHESSAI_H
