
#include "utils/BitboardUtils.h"
#include <iostream>
#include <string>
#include "board/Board.h"
#include "validation/MoveValidator.h"

int main()
{

    Board board;

    board.setupStartingPosition();

    board.printBoard();
    std::cout << std::endl;

    MoveValidator validator;

    bool whiteToMove = true;

    while (true) {

        board.printBoard();
        std::cout << std::endl;

        std::cout << (whiteToMove ? "White" : "Black")
                  << " move (example: a2a3, q to quit): ";

        std::string input;
        std::cin >> input;

        if (input == "q") {
            break;
        }

        if (input.length() != 4) {
            std::cout << "Invalid format. Use for example: a2a3\n";
            continue;
        }

        int fromFile = input[0] - 'a';
        int fromRank = input[1] - '1';
        int toFile = input[2] - 'a';
        int toRank = input[3] - '1';

        if (fromFile < 0 || fromFile > 7 ||
            toFile < 0 || toFile > 7 ||
            fromRank < 0 || fromRank > 7 ||
            toRank < 0 || toRank > 7) {

            std::cout << "Invalid square.\n";
            continue;
        }

        Square from = static_cast<Square>(fromRank * 8 + fromFile);
        Square to = static_cast<Square>(toRank * 8 + toFile);

        if (!board.isOccupied(from)) {
            std::cout << "No piece on source square.\n";
            continue;
        }

        if (whiteToMove && !board.isWhitePiece(from)) {
            std::cout << "It is White's turn.\n";
            continue;
        }

        if (!whiteToMove && !board.isBlackPiece(from)) {
            std::cout << "It is Black's turn.\n";
            continue;
        }

        Move move{from, to};

        if (!validator.isMoveLegal(board, move)) {
            std::cout << "Illegal move.\n";
            continue;
        }

        board.makeMove(move);
        whiteToMove = !whiteToMove;
    }

    return 0;
}

