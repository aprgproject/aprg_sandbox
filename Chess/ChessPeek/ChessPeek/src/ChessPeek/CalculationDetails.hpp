#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

struct CalculationDetails {
    unsigned int depthInPlies;
    int mateScore;
    std::string bestMove;
    StringAndIntPairs currentMovesAndScores;
    int scoreInMonitoredVariation;
    stringHelper::strings monitoredVariation;
    StringAndIntPairs commonMovesAndCountsOfEachStep;

    bool operator==(CalculationDetails const& other) const;
    bool operator!=(CalculationDetails const& other) const;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
