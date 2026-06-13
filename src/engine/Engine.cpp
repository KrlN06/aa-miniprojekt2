#include "engine/Engine.h"
#include "engine/MoveGenerator.h"
#include "engine/Evaluation.h"
#include "rules/GameRules.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>

uint64_t Engine::nodesEvaluated = 0;

int Engine::minimax(const Board& board, int depth, int alpha, int beta, bool isMaximizingWhite) {
    nodesEvaluated++;
    if (depth == 0) return Evaluation::evaluate(board);

    if (isMaximizingWhite) {
        std::vector<Move> moves = MoveGenerator::generateLegalMoves(board, Color::White);
        if (moves.empty()) {
            if (GameRules::isCheckmate(board, Color::White)) {
                return -100000 - depth;
            }
            return 0;
        }
        int maxEval = -999999;
        for (const auto& move : moves) {
            Board copy = board;
            copy.makeMove(move);
            maxEval = std::max(maxEval, minimax(copy, depth - 1, alpha, beta, false));
            alpha = std::max(alpha, maxEval);
            if (beta <= alpha) break;
        }
        return maxEval;
    }
    else {
        std::vector<Move> moves = MoveGenerator::generateLegalMoves(board, Color::Black);
        if (moves.empty()) {
            if (GameRules::isCheckmate(board, Color::Black)) {
                return 100000 + depth;
            }
            return 0;
        }
        int minEval = 999999;
        for (const auto& move : moves) {
            Board copy = board;
            copy.makeMove(move);
            minEval = std::min(minEval, minimax(copy, depth - 1, alpha, beta, true));
            beta = std::min(beta, minEval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

Move Engine::getBestMove(const Board& board, Color aiColor, int depth) {
    nodesEvaluated = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<Move> moves = MoveGenerator::generateLegalMoves(board, aiColor);
    if (moves.empty()) return Move{A1, A1};

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(moves.begin(), moves.end(), g);

    Move bestMove = moves[0];
    int alpha = -999999;
    int beta = 999999;
    int finalBestScore = (aiColor == Color::White) ? -999999 : 999999;

    if (aiColor == Color::White) {
        for (const auto& move : moves) {
            Board copy = board;
            copy.makeMove(move);
            int score = minimax(copy, depth - 1, alpha, beta, false);

            if (score > finalBestScore) {
                finalBestScore = score;
                bestMove = move;
            }
            alpha = std::max(alpha, finalBestScore);
        }
    }
    else { 
        for (const auto& move : moves) {
            Board copy = board;
            copy.makeMove(move);
            int score = minimax(copy, depth - 1, alpha, beta, true);

            if (score < finalBestScore) {
                finalBestScore = score;
                bestMove = move;
            }
            beta = std::min(beta, finalBestScore);
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    double timeInSec = elapsedSeconds.count();
    uint64_t nps = (timeInSec > 0.0) ? static_cast<uint64_t>(nodesEvaluated / timeInSec) : 0;

    for (int i = 0; i < 100; ++i) {
        std::cout << '\n';
    }
    std::cout << "\n============================================\n";
    std::cout << "Depth: " << depth << "\n";

    int displayScore = (aiColor == Color::White) ? finalBestScore : -finalBestScore;
    if (displayScore > 90000) std::cout << "Ocena pozycji : MAT W " << (100000 - displayScore) << " RUCHACH!\n";
    else if (displayScore < -90000) std::cout << "Ocena pozycji : PRZEGRYWAM (Mat w " << (displayScore + 100000) << ")\n";
    else std::cout << "Ocena pozycji : " << std::fixed << std::setprecision(2) << (displayScore / 100.0);

    std::cout << "Odwiedzone wezly: " << nodesEvaluated << "\n";
    std::cout << "Czas : " << std::fixed << std::setprecision(3) << timeInSec << " s\n";
    std::cout << "Szybkosc : " << nps << " wezlow/sek\n";

    char fFile = 'a' + Board::getFile(bestMove.from); char fRank = '1' + Board::getRank(bestMove.from);
    char tFile = 'a' + Board::getFile(bestMove.to); char tRank = '1' + Board::getRank(bestMove.to);
    std::cout << "Wybrany ruch: [" << fFile << fRank << tFile << tRank << "]\n";
    std::cout << "============================================\n";

    return bestMove;
}
