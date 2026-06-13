#include "utils/BitboardUtils.h"
#include <iostream>
#include <string>
#include "board/Board.h"
#include "validation/MoveValidator.h"
#include "rules/GameRules.h"
#include "engine/Engine.h"
#include "move/Move.h"
#include "utils/BitboardUtils.h"
#include "board/Square.h"

int main()
{
    Board board;
    MoveValidator validator;

    board.setupStartingPosition();

    Color humanColor = Color::White;
    Color aiColor = Color::Black;

    while (true)
    {
        board.printBoard();

        if (GameRules::isCheckmate(board, humanColor)) {
            std::cout << "Checkmate! Computer wins.\n";
            break;
        }

        if (GameRules::isCheckmate(board, aiColor)) {
            std::cout << "Checkmate! You win.\n";
            break;
        }

        if (GameRules::isStalemate(board, humanColor) ||
            GameRules::isStalemate(board, aiColor)) {
            std::cout << "Stalemate!\n";
            break;
        }

        std::string fromStr;
        std::string toStr;

        std::cout << "Your move (example: E2 E4): ";
        std::cin >> fromStr >> toStr;

        Square from = stringToSquare(fromStr);
        Square to = stringToSquare(toStr);

        Move humanMove{from, to};

        if (!validator.isMoveLegal(board, humanMove)) {
            std::cout << "Illegal move!\n";
            continue;
        }

        board.makeMove(humanMove);

        if (GameRules::isCheckmate(board, aiColor)) {
            board.printBoard();
            std::cout << "Checkmate! You win.\n";
            break;
        }

        Move aiMove = Engine::getBestMove(board, aiColor, 3);

        std::cout << "Computer move: "
                  << squareToString(aiMove.from)
                  << " -> "
                  << squareToString(aiMove.to)
                  << std::endl;

        board.makeMove(aiMove);
    }

    return 0;
}