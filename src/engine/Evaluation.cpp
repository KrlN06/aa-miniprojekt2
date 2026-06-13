#include "engine/Evaluation.h"
#include <algorithm>

const int Evaluation::mgPieceValues[13] = {
    0,
    100, 320, 330, 500, 900, 20000,
    100, 320, 330, 500, 900, 20000
};

const int Evaluation::egPieceValues[13] = {
    0,
    100, 320, 330, 500, 900, 20000,
    100, 320, 330, 500, 900, 20000
};

const int Evaluation::mgPawnPST[64] = {
      0,   0,   0,   0,   0,   0,   0,   0,
      5,  10,  10, -20, -20,  10,  10,   5,
      5,  -5, -10,   0,   0, -10,  -5,   5,
      0,   0,   0,  35,  35,   0,   0,   0,
      5,   5,  10,  25,  25,  10,   5,   5,
     10,  10,  20,  30,  30,  20,  10,  10,
     50,  50,  50,  50,  50,  50,  50,  50,
      0,   0,   0,   0,   0,   0,   0,   0
};

const int Evaluation::mgKnightPST[64] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
};

const int Evaluation::mgBishopPST[64] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};

const int Evaluation::mgRookPST[64] = {
      0,  0,  0,  5,  5,  0,  0,  0,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
      5, 10, 10, 10, 10, 10, 10,  5,
      0,  0,  0,  0,  0,  0,  0,  0
};

const int Evaluation::mgQueenPST[64] = {
    -20,-10,-10,  0,  0,-10,-10,-20,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -10,  5,  5,  5,  5,  5,  0,-10,
     -5,  0,  5,  5,  5,  5,  0, -5,
      0,  0,  5,  5,  5,  5,  0, -5,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};

const int Evaluation::mgKingPST[64] = {
     20, 30, 10,  0,  0, 10, 30, 20,
     20, 20,-30,-30,-30,-30, 20, 20,
    -10,-20,-30,-40,-40,-30,-20,-10,
    -20,-30,-40,-50,-50,-40,-30,-20,
    -30,-40,-50,-60,-60,-50,-40,-30,
    -30,-40,-50,-60,-60,-50,-40,-30,
    -30,-40,-50,-60,-60,-50,-40,-30,
    -30,-40,-50,-60,-60,-50,-40,-30
};



const int Evaluation::egPawnPST[64] = {
      0,   0,   0,   0,   0,   0,   0,   0,
     10,  10,  10,  10,  10,  10,  10,  10,
     10,  10,  10,  10,  10,  10,  10,  10,
     20,  20,  20,  20,  20,  20,  20,  20,
     30,  30,  30,  30,  30,  30,  30,  30,
     50,  50,  50,  50,  50,  50,  50,  50,
     80,  80,  80,  80,  80,  80,  80,  80,
      0,   0,   0,   0,   0,   0,   0,   0
};

const int Evaluation::egKnightPST[64] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 10, 10, 10,  0,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  0, 10, 10, 10, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
};

const int Evaluation::egBishopPST[64] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};

const int Evaluation::egRookPST[64] = {
      0,  0,  0,  0,  0,  0,  0,  0,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     25, 25, 25, 25, 25, 25, 25, 25,
      0,  0,  0,  0,  0,  0,  0,  0
};

const int Evaluation::egQueenPST[64] = {
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
     -5,  5, 10, 10, 10, 10,  5, -5,
     -5,  5, 10, 10, 10, 10,  5, -5,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};

const int Evaluation::egKingPST[64] = {
    -50,-30,-30,-30,-30,-30,-30,-50,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -50,-40,-30,-20,-20,-30,-40,-50
};

int Evaluation::getGamePhase(const Board& board) {
    int knightPhase = 1, bishopPhase = 1, rookPhase = 2, queenPhase = 4;
    int totalPhase = 24;


    int currentPhase = 0;

    for (int s = 0; s < 64; ++s) {
        Piece p = board.getPiece(static_cast<Square>(s));
        if (p == WHITE_KNIGHT || p == BLACK_KNIGHT) currentPhase += knightPhase;
        else if (p == WHITE_BISHOP || p == BLACK_BISHOP) currentPhase += bishopPhase;
        else if (p == WHITE_ROOK || p == BLACK_ROOK) currentPhase += rookPhase;
        else if (p == WHITE_QUEEN || p == BLACK_QUEEN) currentPhase += queenPhase;
    }

    int calculatedPhase = (currentPhase * 256) / totalPhase;
    return std::max(0, std::min(calculatedPhase, 256));
}

int Evaluation::evaluate(const Board& board) {
    int mgWhite = 0, egWhite = 0;
    int mgBlack = 0, egBlack = 0;

    int currentPhase = 0;
    const int totalPhase = 24;

    for (int square = 0; square < 64; ++square) {
        Piece piece = board.getPiece(static_cast<Square>(square));
        if (piece == NONE) continue;

        if (piece == WHITE_KNIGHT || piece == BLACK_KNIGHT) currentPhase += 1;
        else if (piece == WHITE_BISHOP || piece == BLACK_BISHOP) currentPhase += 1;
        else if (piece == WHITE_ROOK || piece == BLACK_ROOK)     currentPhase += 2;
        else if (piece == WHITE_QUEEN || piece == BLACK_QUEEN)   currentPhase += 4;

        if (board.isWhitePiece(square)) {
            mgWhite += mgPieceValues[piece];
            egWhite += egPieceValues[piece];
            int idx = square;

            if (piece == WHITE_PAWN) { mgWhite += mgPawnPST[idx]; egWhite += egPawnPST[idx]; }
            if (piece == WHITE_KNIGHT) { mgWhite += mgKnightPST[idx]; egWhite += egKnightPST[idx]; }
            if (piece == WHITE_BISHOP) { mgWhite += mgBishopPST[idx]; egWhite += egBishopPST[idx]; }
            if (piece == WHITE_ROOK) { mgWhite += mgRookPST[idx]; egWhite += egRookPST[idx]; }
            if (piece == WHITE_QUEEN) { mgWhite += mgQueenPST[idx]; egWhite += egQueenPST[idx]; }
            if (piece == WHITE_KING) { mgWhite += mgKingPST[idx]; egWhite += egKingPST[idx]; }
        }
        else {
            mgBlack += mgPieceValues[piece];
            egBlack += egPieceValues[piece];
            int idx = square ^ 56;

            if (piece == BLACK_PAWN) { mgBlack += mgPawnPST[idx]; egBlack += egPawnPST[idx]; }
            if (piece == BLACK_KNIGHT) { mgBlack += mgKnightPST[idx]; egBlack += egKnightPST[idx]; }
            if (piece == BLACK_BISHOP) { mgBlack += mgBishopPST[idx]; egBlack += egBishopPST[idx]; }
            if (piece == BLACK_ROOK) { mgBlack += mgRookPST[idx]; egBlack += egRookPST[idx]; }
            if (piece == BLACK_QUEEN) { mgBlack += mgQueenPST[idx]; egBlack += egQueenPST[idx]; }
            if (piece == BLACK_KING) { mgBlack += mgKingPST[idx]; egBlack += egKingPST[idx]; }
        }
    }

    int mgScore = mgWhite - mgBlack;
    int egScore = egWhite - egBlack;

    int phase = (currentPhase * 256) / totalPhase;

    if (phase > 256) phase = 256;

    int finalScore = ((mgScore * phase) + (egScore * (256 - phase))) / 256;

    return finalScore;
}
