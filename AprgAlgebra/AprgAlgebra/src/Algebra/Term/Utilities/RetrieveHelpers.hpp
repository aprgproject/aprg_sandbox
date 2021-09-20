#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <map>
#include <string>

namespace alba
{

namespace algebra
{

using VariableToValueMap = std::map<std::string, AlbaNumber>;

bool hasAnyFunctions(Term const& term);

void retrieveTermsOnly(Terms & terms, TermsWithDetails const& termsWithDetails);

AlbaNumber getCoefficientOfMonomialWithNoVariables(
        Polynomial const& polynomial);
AlbaNumber getCoefficientOfMonomialWithVariableOnly(
        Polynomial const& polynomial,
        std::string const& variableName);
VariableToValueMap getCoefficientsForVariablesOnly(
        Polynomial const& polynomial);

}

}
