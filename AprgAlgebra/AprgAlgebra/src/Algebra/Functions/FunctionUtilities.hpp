#pragma once

#include <Algebra/Term/TermTypes/Function.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

#include <string>

namespace alba
{

namespace algebra
{

namespace Functions
{

bool isFunctionContinuous(Function const& functionObject);

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        std::string const& variableName,        Function const& functionObject);

}
}

}
