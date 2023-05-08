#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

struct CalculationDetails {
    unsigned int depthInPlies;
    int mateScore;
    std::string bestMove;
    StringAndIntPairs searchingMoveAndScorePairs;
    int scoreInPvLine;
    stringHelper::strings pvHalfMovesInMonitoredLine;

    bool operator==(CalculationDetails const& other) const;
    bool operator!=(CalculationDetails const& other) const;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
