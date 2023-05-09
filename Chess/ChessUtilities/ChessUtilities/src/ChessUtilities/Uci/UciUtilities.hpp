#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>

namespace alba {

namespace chess {

constexpr int ARTIFICIAL_MATE_SCORE = 999999;

void retrieveCalculationDetailsOnStringFromEngine(
    CalculationDetails& calculationDetails, std::string const& stringFromEngine);

}  // namespace chess

}  // namespace alba
