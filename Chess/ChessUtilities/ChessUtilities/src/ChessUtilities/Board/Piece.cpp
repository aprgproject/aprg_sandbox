#include "Piece.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace std;

namespace alba {

namespace chess {

PieceColor Piece::extractColor(uint8_t const data) {
    if (PieceType::Empty == extractType(data)) {
        return PieceColor::Unknown;
    } else {
        return static_cast<PieceColor>((data >> 3 & 0B1) | 0B10);  // put 0B10 to avoid unknown
    }
}

PieceType Piece::extractType(uint8_t const data) { return static_cast<PieceType>(data & 0B111); }

PieceColorAndType Piece::extractColorAndType(uint8_t const data) {
    return static_cast<PieceColorAndType>(data & 0B1111);
}

uint8_t Piece::getDataFromColorAndType(PieceColorAndType const pieceColorAndType) {
    return static_cast<uint8_t>(pieceColorAndType) & 0B1111;
}

uint8_t Piece::getDataFromColorAndType(PieceColor const color, PieceType const type) {
    return ((static_cast<uint8_t>(color) & 0B1) << 3) | (static_cast<uint8_t>(type) & 0B111);
}

Piece::Piece() : m_data(0U) {}

Piece::Piece(uint8_t const data) : m_data(data) {}

Piece::Piece(PieceColorAndType const colorAndType) : m_data(getDataFromColorAndType(colorAndType)) {}

Piece::Piece(PieceColor const color, PieceType const type) : m_data(getDataFromColorAndType(color, type)) {}

bool Piece::operator==(Piece const& piece) const { return m_data == piece.m_data; }

bool Piece::operator!=(Piece const& piece) const { return !operator==(piece); }

bool Piece::isEmpty() const { return PieceType::Empty == getType(); }

PieceColor Piece::getColor() const { return extractColor(m_data); }

PieceType Piece::getType() const { return extractType(m_data); }

PieceColorAndType Piece::getColorAndType() const { return extractColorAndType(m_data); }

uint8_t Piece::getData() const { return m_data; }

char Piece::getFenCharacter() const { return convertToFenCharacter(extractType(m_data), extractColor(m_data)); }

}  // namespace chess

}  // namespace alba
