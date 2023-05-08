#include "CalculationDetails.hpp"

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

bool CalculationDetails::operator==(CalculationDetails const& other) const {
    return depthInPlies == other.depthInPlies && mateScore == other.mateScore && bestMove == other.bestMove &&
           searchingMoveAndScorePairs == other.searchingMoveAndScorePairs && scoreInPvLine == other.scoreInPvLine &&
           pvHalfMovesInMonitoredLine == other.pvHalfMovesInMonitoredLine;
}

bool CalculationDetails::operator!=(CalculationDetails const& other) const { return !operator==(other); }

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
