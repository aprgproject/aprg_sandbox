#pragma once

#include <ChessUtilities/Board/Board.hpp>
#include <ChessUtilities/Board/PieceColor.hpp>
#include <ChessUtilities/Board/PieceType.hpp>
#include <ChessUtilities/Board/PieceColorAndType.hpp>

namespace alba
{

namespace chess
{

bool isCoordinateOnBoard(Coordinate const& coordinate);
bool isValidMove(Move const& move);

PieceColor getOppositeColor(PieceColor const pieceColor);

std::string getEnumString(PieceColor const pieceColor);
std::string getEnumString(PieceType const pieceType);
std::string getEnumString(PieceColorAndType const pieceColorAndType);

std::string constructFenString(
        Board const& board,
        PieceColor const colorToMove,
        std::string const& castlingAvailability,
        std::string const& enPassantTarget,
        unsigned int const halfMoveClock,
        unsigned int const fullMoveNumber);

Moves getSequenceOfMoves(Board const& board1, Board const& board2);


}

}
