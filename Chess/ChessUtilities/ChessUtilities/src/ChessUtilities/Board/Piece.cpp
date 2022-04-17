#include "Piece.hpp"

namespace alba
{

namespace chess
{

PieceColor Piece::extractColor(uint16_t const value)
{
    return static_cast<PieceColor>(value>>3 & 0B1);
}

PieceType Piece::extractType(uint16_t const value)
{
    return static_cast<PieceType>(value & 0B111);
}

Piece::Piece(uint16_t const underlyingValue)
    : m_underlyingValue(underlyingValue)
{}

PieceColor Piece::getColor() const
{
    return extractColor(m_underlyingValue);
}

PieceType Piece::getType() const
{
    return extractType(m_underlyingValue);
}

}

}
