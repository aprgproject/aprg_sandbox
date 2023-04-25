#pragma once

#include <ChessUtilities/Board/PieceColor.hpp>
#include <ChessUtilities/Board/PieceColorAndType.hpp>
#include <ChessUtilities/Board/PieceType.hpp>

#include <cstdint>
#include <ostream>
#include <vector>

namespace alba {

namespace chess {

struct Piece {
public:
    static PieceColor extractColor(uint8_t const value);
    static PieceType extractType(uint8_t const value);
    static PieceColorAndType extractColorAndType(uint8_t const value);
    static uint8_t getValueFromColorAndType(PieceColorAndType const pieceColorAndType);
    static uint8_t getValueFromColorAndType(PieceColor const color, PieceType const type);
    static char convertToCharacter(uint8_t const value);

    Piece();
    Piece(Piece const&) = default;
    Piece(uint8_t const underlyingValue);
    Piece(PieceColorAndType const colorAndType);
    Piece(PieceColor const color, PieceType const type);

    bool operator==(Piece const& piece) const;
    bool operator!=(Piece const& piece) const;
    bool isEmpty() const;

    PieceColor getColor() const;
    PieceType getType() const;
    PieceColorAndType getColorAndType() const;
    uint8_t getUnderlyingValue() const;
    char getCharacter() const;

private:
    uint8_t m_underlyingValue;
};

using Pieces = std::vector<Piece>;

std::ostream& operator<<(std::ostream& out, Piece const& piece);

}  // namespace chess

}  // namespace alba
