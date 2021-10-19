#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

bool isTheIntegralDefinitionForFiniteCalculusIsTrue(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b);

Term solveADefiniteIntegral(
        Term const& integratedTerm,
        std::string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue);

}

}
