#pragma once

#include <ChessUtilities/Board/PieceColor.hpp>
#include <ChessUtilities/Board/PieceType.hpp>

#include <cstdint>

namespace alba
{

namespace chess
{

struct Piece
{
public:
    static PieceColor extractColor(uint16_t const value);
    static PieceType extractType(uint16_t const value);

    Piece(uint16_t const underlyingValue);
    PieceColor getColor() const;
    PieceType getType() const;

private:
    uint16_t m_underlyingValue;
};

}

}
