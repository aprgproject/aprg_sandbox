#pragma once

#include <ChessUtilities/Board/BoardValue.hpp>
#include <ChessUtilities/Board/Piece.hpp>

namespace alba {

namespace chess {

std::ostream& operator<<(std::ostream& out, PieceColor const pieceColor);
std::ostream& operator<<(std::ostream& out, PieceType const pieceType);
std::ostream& operator<<(std::ostream& out, PieceColorAndType const pieceType);
std::ostream& operator<<(std::ostream& out, Piece const& piece);

std::ostream& operator<<(std::ostream& out, Move const& move);
std::istream& operator>>(std::istream& in, Move& move);

std::ostream& operator<<(std::ostream& out, Board const& board);

std::ostream& operator<<(std::ostream& out, BoardValue const& boardValue);
std::istream& operator>>(std::istream& in, BoardValue& boardValue);

void printHexValuesInBoard(std::ostream& out, Board const& board);

}  // namespace chess

}  // namespace alba
