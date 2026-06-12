#include "utils/BitboardUtils.h"
#include <iostream>
#include <string>
#include "board/Board.h"
#include "validation/MoveValidator.h"
#include "rules/GameRules.h"

int main()
{
    Board board;
    MoveValidator validator;

    // Stalemate test position
    // Jeśli Board domyślnie tworzy pustą planszę,
    // nie potrzebujemy setupStartingPosition() ani clear().
    board = Board();

    board.addPiece(WHITE_KING, C6);
    board.addPiece(WHITE_QUEEN, C7);
    board.addPiece(BLACK_KING, A8);

    board.updateOccupancy();

    std::cout << "Stalemate position:\n";
    board.printBoard();

    std::cout << std::boolalpha;

    std::cout << "\nBlack has legal move: "
              << GameRules::hasAnyLegalMove(board, Color::Black)
              << std::endl;

    std::cout << "Black checkmate: "
              << GameRules::isCheckmate(board, Color::Black)
              << std::endl;

    std::cout << "Black stalemate: "
              << GameRules::isStalemate(board, Color::Black)
              << std::endl;

    return 0;
}