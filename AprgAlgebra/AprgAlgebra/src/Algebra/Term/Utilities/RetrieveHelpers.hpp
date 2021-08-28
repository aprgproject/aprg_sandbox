#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

#include <map>
#include <string>

namespace alba
{

namespace algebra
{

using VariableToValueMap = std::map<std::string, AlbaNumber>;

AlbaNumber getCoefficientOfMonomialWithNoVariables(
        Polynomial const& polynomial);
AlbaNumber getCoefficientOfMonomialWithVariableOnly(
        Polynomial const& polynomial,
        std::string const& variableName);
VariableToValueMap getCoefficientsForVariablesOnly(
        Polynomial const& polynomial);

}

}
