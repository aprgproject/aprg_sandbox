#pragma once

#include <ChessUtilities/Board/PieceColor.hpp>
#include <ChessUtilities/Board/PieceColorAndType.hpp>
#include <ChessUtilities/Board/PieceType.hpp>

#include <cstdint>
#include <vector>

namespace alba {

namespace chess {

class Piece {
public:
    static PieceColor extractColor(uint8_t const data);
    static PieceType extractType(uint8_t const data);
    static PieceColorAndType extractColorAndType(uint8_t const data);
    static uint8_t getDataFromColorAndType(PieceColorAndType const pieceColorAndType);
    static uint8_t getDataFromColorAndType(PieceColor const color, PieceType const type);

    Piece();
    Piece(uint8_t const data);
    Piece(PieceColorAndType const colorAndType);
    Piece(PieceColor const color, PieceType const type);

    bool operator==(Piece const& piece) const;
    bool operator!=(Piece const& piece) const;
    bool isEmpty() const;

    PieceColor getColor() const;
    PieceType getType() const;
    PieceColorAndType getColorAndType() const;
    uint8_t getData() const;
    char getFenCharacter() const;

private:
    uint8_t m_data;
};

using Pieces = std::vector<Piece>;

}  // namespace chess

}  // namespace alba
