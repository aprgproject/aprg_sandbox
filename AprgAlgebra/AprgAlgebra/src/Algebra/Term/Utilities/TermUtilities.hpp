#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{

AlbaNumbers getRoots(Polynomial const& polynomial);
AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        std::string const& variableName,
        Term const& term);

}

}
