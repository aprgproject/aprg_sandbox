#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/AlbaNumberTypes.hpp>

//#include "EnumHelpers.hpp"
//#include "MonomialHelpers.hpp"
//#include "RetrieveHelpers.hpp"
//#include "StringHelpers.hpp"
//#include "ValueCheckingHelpers.hpp"

namespace alba
{

namespace algebra
{

AlbaNumbers getRoots(Polynomial const& polynomial);
AlbaNumber getMaxDegreeOfPolynomials(Polynomials const& polynomials);
AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        std::string const& variableName,
        Term const& term);

}

}
