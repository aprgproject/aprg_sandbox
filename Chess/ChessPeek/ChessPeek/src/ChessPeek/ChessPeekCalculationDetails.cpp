#include "ChessPeekCalculationDetails.hpp"

using namespace std;

namespace alba {

namespace chess {

bool ChessPeekCalculationDetails::operator==(ChessPeekCalculationDetails const& other) const {
    return depthInPlies == other.depthInPlies && numberOfMovesTillMate == other.numberOfMovesTillMate &&
           bestMove == other.bestMove && searchingMoveAndScorePairs == other.searchingMoveAndScorePairs &&
           pvMovesInBestLine == other.pvMovesInBestLine;
}

bool ChessPeekCalculationDetails::operator!=(ChessPeekCalculationDetails const& other) const {
    return !operator==(other);
}

}  // namespace chess

}  // namespace alba
