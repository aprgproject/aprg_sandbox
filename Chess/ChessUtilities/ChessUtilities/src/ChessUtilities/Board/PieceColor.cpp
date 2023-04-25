#include "PieceColor.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba {

namespace chess {

ostream& operator<<(ostream& out, PieceColor const pieceColor) {
    out << getEnumString(pieceColor);
    return out;
}

}  // namespace chess

}  // namespace alba
