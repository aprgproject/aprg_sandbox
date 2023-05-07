#include "ChessPeekCalculationDetails.hpp"

using namespace std;

namespace alba {

namespace chess {

bool ChessPeekCalculationDetails::operator==(ChessPeekCalculationDetails const& other) const {
    return depthInPlies == other.depthInPlies && mateScore == other.mateScore && bestMove == other.bestMove &&
           searchingMoveAndScorePairs == other.searchingMoveAndScorePairs && scoreInPvLine == other.scoreInPvLine &&
           pvHalfMovesInMonitoredLine == other.pvHalfMovesInMonitoredLine;
}

bool ChessPeekCalculationDetails::operator!=(ChessPeekCalculationDetails const& other) const {
    return !operator==(other);
}

}  // namespace chess

}  // namespace alba
