#pragma once

#include <ostream>

namespace alba
{

namespace chess
{

enum class PieceType
{
    Empty = 0,
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6,
};


std::ostream & operator<<(std::ostream & out, PieceType const pieceType);

}

}
