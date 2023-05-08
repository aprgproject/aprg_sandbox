#pragma once

#include <ChessUtilities/Board/Board.hpp>
#include <ChessUtilities/Board/PieceColor.hpp>
#include <ChessUtilities/Board/PieceColorAndType.hpp>
#include <ChessUtilities/Board/PieceType.hpp>

namespace alba {

namespace chess {

bool isCoordinateWithinTheBoard(Coordinate const& coordinate);
bool isInUpperHalf(Coordinate const& coordinate);
bool isInLowerHalf(Coordinate const& coordinate);
bool isMoveWithinTheBoard(Move const& move);

int getValueOfPieceType(PieceType const pieceType);
PieceColor getOppositeColor(PieceColor const pieceColor);

std::string getEnumString(PieceColor const pieceColor);std::string getEnumString(PieceType const pieceType);
std::string getEnumString(PieceColorAndType const pieceColorAndType);

std::string constructFenString(    Board const& board, PieceColor const colorToMove, std::string const& castlingAvailability,
    std::string const& enPassantTarget, unsigned int const halfMoveClock, unsigned int const fullMoveNumber);

Moves getSequenceOfMoves(Board const& board1, Board const& board2);

}  // namespace chess

}  // namespace alba
