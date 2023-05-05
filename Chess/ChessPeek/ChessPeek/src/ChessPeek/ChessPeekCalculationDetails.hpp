#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>

namespace alba {

namespace chess {

struct ChessPeekCalculationDetails {
    unsigned int depthInPlies;
    int numberOfMovesTillMate;
    std::string bestMove;
    StringAndIntPairs searchingMoveAndScorePairs;
    stringHelper::strings pvMovesInBestLine;

    bool operator==(ChessPeekCalculationDetails const& other) const;
    bool operator!=(ChessPeekCalculationDetails const& other) const;
};

}  // namespace chess

}  // namespace alba
