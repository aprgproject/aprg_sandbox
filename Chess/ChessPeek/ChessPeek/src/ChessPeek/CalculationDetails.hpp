#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

struct CalculationDetails {
    int depthInPlies;
    Variations variations;
    std::string bestMove;
    std::string responseMoveToPonder;

    bool operator==(CalculationDetails const& other) const;
    bool operator!=(CalculationDetails const& other) const;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
