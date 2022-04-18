#pragma once

#include <ChessUtilities/Board/Board.hpp>
#include <ChessUtilities/Board/PieceColor.hpp>

namespace alba
{
namespace chess
{

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