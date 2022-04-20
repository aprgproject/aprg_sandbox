#pragma once

#include <ChessUtilities/Board/PieceColor.hpp>
#include <ChessUtilities/Board/PieceType.hpp>

#include <cstdint>
#include <ostream>
#include <vector>

namespace alba
{

namespace chess
{

struct Piece
{
public:
    static PieceColor extractColor(uint16_t const value);
    static PieceType extractType(uint16_t const value);
    static uint16_t getValueFromColorAndType(PieceColor const color, PieceType const type);
    static char convertToCharacter(uint16_t const value);

    Piece();
    Piece(uint16_t const underlyingValue);
    Piece(PieceColor const color, PieceType const type);

    bool operator==(Piece const& piece) const;
    bool operator!=(Piece const& piece) const;

    PieceColor getColor() const;
    PieceType getType() const;
    uint16_t getUnderlyingValue() const;
    char getCharacter() const;

private:
    uint16_t m_underlyingValue;
};

using Pieces = std::vector<Piece>;


std::ostream & operator<<(std::ostream & out, Piece const& piece);

}

}
