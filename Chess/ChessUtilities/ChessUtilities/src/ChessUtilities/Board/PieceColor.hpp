#pragma once

#include <ostream>

namespace alba {

namespace chess {

enum class PieceColor { Unknown = 0, White = 0B10, Black = 0B11 };

std::ostream& operator<<(std::ostream& out, PieceColor const pieceColor);
}  // namespace chess

}  // namespace alba