#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>

namespace alba {

namespace chess {

struct ChessPeekCalculationDetails {
    unsigned int depthInPlies;
    int mateScore;
    std::string bestMove;
    StringAndIntPairs searchingMoveAndScorePairs;
    int scoreInPvLine;
    stringHelper::strings pvHalfMovesInMonitoredLine;

    bool operator==(ChessPeekCalculationDetails const& other) const;
    bool operator!=(ChessPeekCalculationDetails const& other) const;
};

}  // namespace chess

}  // namespace alba
