
#include "utils/BitboardUtils.h"
#include <iostream>
#include "board/Board.h"
#include "validation/MoveValidator.h"

int main()
{

    Board board;

    board.setupStartingPosition();

    board.printBoard();
    std::cout << std::endl;

    MoveValidator validator;

    Move move1{E2, E4};

    std::cout << "E2 -> E4 legal: "
              << validator.isMoveLegal(board, move1)
              << std::endl;

    if (validator.isMoveLegal(board, move1)) {
        board.makeMove(move1);
    }

    board.printBoard();
    std::cout << std::endl;

    Move move2{D7, D5};
    board.makeMove(move2);

    board.printBoard();
    std::cout << std::endl;

    Move move3{E4, D5};
    board.makeMove(move3);

    board.printBoard();
    std::cout << std::endl;

    Move illegalMove1{A1, A2};
    std::cout << "A1 -> A2 legal: "
              << validator.isMoveLegal(board, illegalMove1)
              << std::endl;

    Move illegalMove2{E3, E5};
    std::cout << "E3 -> E5 legal: "
              << validator.isMoveLegal(board, illegalMove2)
              << std::endl;

    Move knightLegal{B1, C3};
    std::cout << "B1 -> C3 legal: "
              << validator.isMoveLegal(board, knightLegal)
              << std::endl;

    Move knightIllegal{B1, B3};
    std::cout << "B1 -> B3 legal: "
              << validator.isMoveLegal(board, knightIllegal)
              << std::endl;

    return 0;
}

