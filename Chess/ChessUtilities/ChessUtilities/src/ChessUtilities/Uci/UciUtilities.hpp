#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>

namespace alba
{

namespace chess
{

void retrieveCalculationDetailsOnStringFromEngine(
        CalculationDetails & calculationDetails,
        std::string const& stringFromEngine);

}

}
