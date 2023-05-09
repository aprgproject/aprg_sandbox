#include "CalculationDetails.hpp"

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

bool CalculationDetails::operator==(CalculationDetails const& other) const {
    return depthInPlies == other.depthInPlies && mateScore == other.mateScore && bestMove == other.bestMove &&
           currentMovesAndScores == other.currentMovesAndScores &&
           scoreInMonitoredVariation == other.scoreInMonitoredVariation &&
           monitoredVariation == other.monitoredVariation;
}

bool CalculationDetails::operator!=(CalculationDetails const& other) const { return !operator==(other); }

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
