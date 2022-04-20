#pragma once

#include <ostream>

namespace alba
{

namespace chess
{

enum class PieceColor
{
    White = 0,
    Black = 1
};

std::ostream & operator<<(std::ostream & out, PieceColor const pieceColor);

}

}
