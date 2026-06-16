#include "utils/BitboardUtils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include "board/Board.h"
#include "validation/MoveValidator.h"
#include "rules/GameRules.h"
#include "engine/Engine.h"
#include "move/Move.h"
#include "utils/BitboardUtils.h"
#include "board/Square.h"

int main()
{
    constexpr int GAME_MODE = 2; // 1=PVP, 2=PvsAI, 3=AIvsAI
    constexpr Color HUMAN_COLOR = Color::White;
    constexpr int AI_DEPTH = 5;
    constexpr int AI1_DEPTH = 3;
    constexpr int AI2_DEPTH = 3;

    Board board;
    MoveValidator validator;

    board.setupStartingPosition();

    Color aiColor = (HUMAN_COLOR == Color::White) ? Color::Black : Color::White;
    Color sideToMove = Color::White;

    while (true)
    {
        board.printBoard();

        if (GameRules::isCheckmate(board, sideToMove)) {
            if (GAME_MODE == 1) {
                if (sideToMove == HUMAN_COLOR) {
                    std::cout << "Checkmate! ";
                    if (sideToMove == HUMAN_COLOR) std::cout << "Black wins.\n";
                    else std::cout << "White wins.\n";
                } else {
                    std::cout << "Checkmate! ";
                    if (sideToMove == HUMAN_COLOR) std::cout << "Black wins.\n";
                    else std::cout << "White wins.\n";
                }
            } else {
                if (sideToMove == HUMAN_COLOR) {
                    std::cout << "Checkmate! Computer wins.\n";
                } else {
                    std::cout << "Checkmate! You win.\n";
                }
            }
            break;
        }

        if (GameRules::isStalemate(board, sideToMove)) {
            std::cout << "Stalemate!\n";
            break;
        }

        if (GAME_MODE == 1 || (GAME_MODE == 2 && sideToMove == HUMAN_COLOR)) {
            std::string line;

            std::cout << "Your move (example: E2 E4 or E7 E8 Q): ";
            std::getline(std::cin >> std::ws, line);

            std::stringstream ss(line);

            std::string fromStr;
            std::string toStr;
            std::string promotionStr;

            ss >> fromStr >> toStr >> promotionStr;

            Square from;
            Square to;

            try {
                from = stringToSquare(fromStr);
                to = stringToSquare(toStr);
            }
            catch (...) {
                std::cout << "Invalid notation!\n";
                continue;
            }

            Piece promotionPiece = NONE;

            if (!promotionStr.empty()) {
                char p = static_cast<char>(std::toupper(promotionStr[0]));

                if (sideToMove == Color::White) {
                    if (p == 'Q') promotionPiece = WHITE_QUEEN;
                    else if (p == 'R') promotionPiece = WHITE_ROOK;
                    else if (p == 'B') promotionPiece = WHITE_BISHOP;
                    else if (p == 'N') promotionPiece = WHITE_KNIGHT;
                } else {
                    if (p == 'Q') promotionPiece = BLACK_QUEEN;
                    else if (p == 'R') promotionPiece = BLACK_ROOK;
                    else if (p == 'B') promotionPiece = BLACK_BISHOP;
                    else if (p == 'N') promotionPiece = BLACK_KNIGHT;
                }
            }

            Move humanMove{from, to, promotionPiece};

            if (!validator.isMoveLegal(board, humanMove)) {
                std::cout << "Illegal move!\n";
                continue;
            }

            board.makeMove(humanMove);
        }
        else if (GAME_MODE == 2 && sideToMove == aiColor)
        {
            Move aiMove = Engine::getBestMove(board, aiColor, AI_DEPTH);

            std::cout << "Computer move: "
                      << squareToString(aiMove.from)
                      << " -> "
                      << squareToString(aiMove.to)
                      << std::endl;

            board.makeMove(aiMove);
        }
        else if (GAME_MODE == 3)
        {
            int depth = (sideToMove == Color::White) ? AI1_DEPTH : AI2_DEPTH;

            std::this_thread::sleep_for(std::chrono::milliseconds(2500));

            Move aiMove = Engine::getBestMove(board, sideToMove, depth);

            std::cout << "Computer move: "
                      << squareToString(aiMove.from)
                      << " -> "
                      << squareToString(aiMove.to)
                      << std::endl;

            board.makeMove(aiMove);
        }

        sideToMove = (sideToMove == Color::White) ? Color::Black : Color::White;
    }

    return 0;
}