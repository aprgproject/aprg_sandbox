#include "Piece.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <ctype.h>

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

char Piece::convertToCharacter(uint16_t const value)
{
    char result{};
    PieceType pieceType(extractType(value));
    switch(pieceType)
    {
    case PieceType::Pawn:
    {
        result = 'p';
        break;
    }
    case PieceType::Knight:
    {
        result = 'n';
        break;
    }
    case PieceType::Bishop:
    {
        result = 'b';
        break;
    }
    case PieceType::Rook:
    {
        result = 'r';
        break;
    }
    case PieceType::Queen:
    {
        result = 'q';
        break;
    }
    case PieceType::King:
    {
        result = 'k';
        break;
    }
    default :
    {
        break;
    }
    }
    result = (PieceColor::White == extractColor(value)) ? toupper(result) : result;
    return result;
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

char Piece::getCharacter() const
{
    return convertToCharacter(m_underlyingValue);
}

}

}
