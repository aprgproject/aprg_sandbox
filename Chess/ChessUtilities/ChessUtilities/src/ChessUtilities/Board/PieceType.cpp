#include "PieceType.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba
{

namespace chess
{

ostream & operator<<(ostream & out, PieceType const pieceType)
{
    out << getEnumString(pieceType);
    return out;
}

}

}
