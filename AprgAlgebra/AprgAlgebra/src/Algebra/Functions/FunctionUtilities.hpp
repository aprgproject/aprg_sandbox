#pragma once

#include <Algebra/Term/TermTypes/Function.hpp>
#include <Math/AlbaNumberTypes.hpp>

#include <string>

namespace alba
{

namespace algebra
{

namespace Functions
{

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        std::string const& variableName,
        Function const& functionObject);

}

}

}