//
// Created by Karol Nalepa on 18/05/2026.
//

#include "board/Board.h"
#include "utils/BitboardUtils.h"
#include "../include/validation/MoveValidator.h"
#include "pieces/PieceMovement.h"
#include <iostream>
#include <stdexcept>

void Board::setupStartingPosition() {

    whitePawns = 0;
    whiteKnights = 0;
    whiteBishops = 0;
    whiteRooks = 0;
    whiteQueens = 0;
    whiteKing = 0;

    blackPawns = 0;
    blackKnights = 0;
    blackBishops = 0;
    blackRooks = 0;
    blackQueens = 0;
    blackKing = 0;

    whitePieces = 0;
    blackPieces = 0;
    occupied = 0;

    setBit(whitePawns, A2);
    setBit(whitePawns, B2);
    setBit(whitePawns, C2);
    setBit(whitePawns, D2);
    setBit(whitePawns, E2);
    setBit(whitePawns, F2);
    setBit(whitePawns, G2);
    setBit(whitePawns, H2);

    setBit(whiteRooks, A1);
    setBit(whiteRooks, H1);

    setBit(whiteKnights, B1);
    setBit(whiteKnights, G1);

    setBit(whiteBishops, C1);
    setBit(whiteBishops, F1);

    setBit(whiteQueens, D1);
    setBit(whiteKing, E1);


    setBit(blackPawns, A7);
    setBit(blackPawns, B7);
    setBit(blackPawns, C7);
    setBit(blackPawns, D7);
    setBit(blackPawns, E7);
    setBit(blackPawns, F7);
    setBit(blackPawns, G7);
    setBit(blackPawns, H7);

    setBit(blackRooks, A8);
    setBit(blackRooks, H8);

    setBit(blackKnights, B8);
    setBit(blackKnights, G8);

    setBit(blackBishops, C8);
    setBit(blackBishops, F8);

    setBit(blackQueens, D8);
    setBit(blackKing, E8);

    whiteKingSquare = E1;
    blackKingSquare = E8;
    enPassantSquare = NO_SQUARE;

    whitePieces =
        whitePawns |
        whiteKnights |
        whiteBishops |
        whiteRooks |
        whiteQueens |
        whiteKing;

    blackPieces =
            blackPawns |
            blackKnights |
            blackBishops |
            blackRooks |
            blackQueens |
            blackKing;

    occupied = whitePieces | blackPieces;

}

bool Board::isOccupied(int square) const {
    return getBit(occupied, square);
}

Piece Board::getPiece(int square) const {

    if (getBit(whitePawns, square)) {
        return WHITE_PAWN;
    }

    if (getBit(whiteKnights, square)) {
        return WHITE_KNIGHT;
    }

    if (getBit(whiteBishops, square)) {
        return WHITE_BISHOP;
    }

    if (getBit(whiteRooks, square)) {
        return WHITE_ROOK;
    }

    if (getBit(whiteQueens, square)) {
        return WHITE_QUEEN;
    }

    if (getBit(whiteKing, square)) {
        return WHITE_KING;
    }

    if (getBit(blackPawns, square)) {
        return BLACK_PAWN;
    }

    if (getBit(blackKnights, square)) {
        return BLACK_KNIGHT;
    }

    if (getBit(blackBishops, square)) {
        return BLACK_BISHOP;
    }

    if (getBit(blackRooks, square)) {
        return BLACK_ROOK;
    }

    if (getBit(blackQueens, square)) {
        return BLACK_QUEEN;
    }

    if (getBit(blackKing, square)) {
        return BLACK_KING;
    }

    return NONE;
}

void Board::printBoard() const {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            Piece piece = getPiece(square);

            if (piece == WHITE_KING) {
                std::cout << "K ";
            } else if (piece == WHITE_QUEEN) {
                std::cout << "Q ";
            } else if (piece == WHITE_BISHOP) {
                std::cout << "B ";
            } else if (piece == WHITE_ROOK) {
                std::cout << "R ";
            } else if (piece == WHITE_KNIGHT) {
                std::cout << "N ";
            } else if (piece == WHITE_PAWN) {
                std::cout << "P ";
            } else if (piece == BLACK_PAWN) {
                std::cout << "p ";
            } else if (piece == BLACK_KNIGHT) {
                std::cout << "n ";
            } else if (piece == BLACK_BISHOP) {
                std::cout << "b ";
            } else if (piece == BLACK_ROOK) {
                std::cout << "r ";
            } else if (piece == BLACK_KING) {
                std::cout << "k ";
            } else if (piece == BLACK_QUEEN) {
                std::cout << "q ";
            } else {
                std::cout << ". ";
            }
        }

        std::cout << std::endl;
    }
}

bool Board::isWhitePiece(int square) const
{
    return getBit(whitePieces, square);
}

bool Board::isBlackPiece(int square) const
{
    return getBit(blackPieces, square);
}

void Board::makeMove(const Move &move) {

    Piece piece;
    piece = getPiece(move.from);
    if (piece == NONE)
        return;
    removePiece(piece, move.from);

    if (isOccupied(move.to)) {
        Piece enemyPiece = getPiece(move.to);
        removePiece(enemyPiece, move.to);
    }

    // En passant capture
    if (piece == WHITE_PAWN &&
        move.to == enPassantSquare &&
        !isOccupied(move.to))
    {
        removePiece(BLACK_PAWN,
                    static_cast<Square>(move.to - 8));
    }

    if (piece == BLACK_PAWN &&
        move.to == enPassantSquare &&
        !isOccupied(move.to))
    {
        removePiece(WHITE_PAWN,
                    static_cast<Square>(move.to + 8));
    }

    addPiece(piece, move.to);

    // Castling rook move
    if (piece == WHITE_KING) {

        if (move.from == E1 && move.to == G1) {
            removePiece(WHITE_ROOK, H1);
            addPiece(WHITE_ROOK, F1);
        }
        else if (move.from == E1 && move.to == C1) {
            removePiece(WHITE_ROOK, A1);
            addPiece(WHITE_ROOK, D1);
        }
    }

    if (piece == BLACK_KING) {

        if (move.from == E8 && move.to == G8) {
            removePiece(BLACK_ROOK, H8);
            addPiece(BLACK_ROOK, F8);
        }
        else if (move.from == E8 && move.to == C8) {
            removePiece(BLACK_ROOK, A8);
            addPiece(BLACK_ROOK, D8);
        }
    }

    updateOccupancy();

    // En passant target square
    enPassantSquare = NO_SQUARE;

    if (piece == WHITE_PAWN &&
        getRank(move.to) - getRank(move.from) == 2)
    {
        enPassantSquare =
            static_cast<Square>((move.from + move.to) / 2);
    }

    if (piece == BLACK_PAWN &&
        getRank(move.from) - getRank(move.to) == 2)
    {
        enPassantSquare =
            static_cast<Square>((move.from + move.to) / 2);
    }

    if (piece == WHITE_KING) {

        whiteKingSquare = move.to;
        whiteKingMoved = true;
    }

    if (piece == BLACK_KING) {

        blackKingSquare = move.to;
        blackKingMoved = true;
    }

    if (piece == WHITE_ROOK) {

        if (move.from == A1) {
            whiteQueensideRookMoved = true;
        } else if (move.from == H1) {
            whiteKingsideRookMoved = true;
        }
    }

    if (piece == BLACK_ROOK) {

        if (move.from == A8) {
            blackQueensideRookMoved = true;
        } else if (move.from == H8) {
            blackKingsideRookMoved = true;
        }
    }

    if (piece == WHITE_PAWN && getRank(move.to) == 7) {
        removePiece(WHITE_PAWN, move.to);
        addPiece(move.promotionPiece, move.to);
        updateOccupancy();
    }
    if (piece == BLACK_PAWN && getRank(move.to) == 0) {
        removePiece(BLACK_PAWN, move.to);
        addPiece(move.promotionPiece, move.to);
        updateOccupancy();
    }

}

void Board::removePiece(Piece piece, Square square) {
    if (piece==WHITE_KING) {
        clearBit(whiteKing, square);
    } else if (piece==WHITE_QUEEN) {
        clearBit(whiteQueens, square);
    } else if (piece==WHITE_BISHOP) {
        clearBit(whiteBishops, square);
    } else if (piece==WHITE_ROOK) {
        clearBit(whiteRooks, square);
    } else if (piece==WHITE_KNIGHT) {
        clearBit(whiteKnights, square);
    } else if (piece==WHITE_PAWN) {
        clearBit(whitePawns, square);
    } else if (piece==BLACK_PAWN) {
        clearBit(blackPawns, square);
    } else if (piece==BLACK_KNIGHT) {
        clearBit(blackKnights, square);
    } else if (piece==BLACK_BISHOP) {
        clearBit(blackBishops, square);
    } else if (piece==BLACK_ROOK) {
        clearBit(blackRooks, square);
    } else if (piece==BLACK_KING) {
        clearBit(blackKing, square);
    } else if (piece==BLACK_QUEEN) {
        clearBit(blackQueens, square);
    }
}

void Board::addPiece(Piece piece, Square square) {

    if (piece == WHITE_KING) {
        setBit(whiteKing, square);
    } else if (piece == WHITE_QUEEN) {
        setBit(whiteQueens, square);
    } else if (piece == WHITE_BISHOP) {
        setBit(whiteBishops, square);
    } else if (piece == WHITE_ROOK) {
        setBit(whiteRooks, square);
    } else if (piece == WHITE_KNIGHT) {
        setBit(whiteKnights, square);
    } else if (piece == WHITE_PAWN) {
        setBit(whitePawns, square);
    } else if (piece == BLACK_PAWN) {
        setBit(blackPawns, square);
    } else if (piece == BLACK_KNIGHT) {
        setBit(blackKnights, square);
    } else if (piece == BLACK_BISHOP) {
        setBit(blackBishops, square);
    } else if (piece == BLACK_ROOK) {
        setBit(blackRooks, square);
    } else if (piece == BLACK_KING) {
        setBit(blackKing, square);
    } else if (piece == BLACK_QUEEN) {
        setBit(blackQueens, square);
    }
}

void Board::updateOccupancy() {

    whitePieces =
            whitePawns |
            whiteKnights |
            whiteBishops |
            whiteRooks |
            whiteQueens |
            whiteKing;

    blackPieces =
            blackPawns |
            blackKnights |
            blackBishops |
            blackRooks |
            blackQueens |
            blackKing;

    occupied = whitePieces | blackPieces;
}


Square Board::getWhiteKingSquare() const {
    return whiteKingSquare;
}

Square Board::getBlackKingSquare() const {
    return blackKingSquare;
}


int Board::getRank(Square square) {
    return square / 8;
}

int Board::getFile(Square square) {
    return square % 8;
}

bool Board::getWhiteKingMoved() const {
    return whiteKingMoved;
}
bool Board::getBlackKingMoved() const{
    return blackKingMoved;
}

bool Board::getWhiteKingsideRookMoved() const {
    return whiteKingsideRookMoved;
}

bool Board::getBlackKingsideRookMoved() const {
    return blackKingsideRookMoved;
}

bool Board::getWhiteQueensideRookMoved() const {
    return whiteQueensideRookMoved;
}

bool Board::getBlackQueensideRookMoved() const
{
    return blackQueensideRookMoved;
}

Color Board::getColor(Square square) const {

    if (isWhitePiece(square)) {
        return Color::White;
    }

    if (isBlackPiece(square)) {
        return Color::Black;
    }

    throw std::runtime_error("Square is empty");
}

Square Board::getEnPassantSquare() const
{
    return enPassantSquare;
}
