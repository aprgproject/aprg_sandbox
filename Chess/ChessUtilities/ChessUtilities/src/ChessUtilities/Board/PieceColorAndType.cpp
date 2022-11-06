#include "PieceColorAndType.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba
{

namespace chess
{

ostream & operator<<(ostream & out, PieceColorAndType const pieceType)
{
    out << getEnumString(pieceType);
    return out;
}

}

}
