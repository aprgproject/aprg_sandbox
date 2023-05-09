#include "CalculationDetails.hpp"

#include <ChessUtilities/Engine/CalculationDetailsEqualityOperators.hpp>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

bool CalculationDetails::operator==(CalculationDetails const& other) const {
    return depthInPlies == other.depthInPlies && variations == other.variations && bestMove == other.bestMove &&
           responseMoveToPonder == other.responseMoveToPonder;
}

bool CalculationDetails::operator!=(CalculationDetails const& other) const { return !operator==(other); }

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
