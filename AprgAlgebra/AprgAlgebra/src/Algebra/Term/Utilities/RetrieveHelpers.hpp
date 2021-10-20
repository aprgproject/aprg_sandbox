#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <map>
#include <string>

namespace alba
{

namespace algebra
{

using ConditionFunctionForTermsWithDetails = std::function<bool(TermWithDetails const&)>;
using VariableToValueMap = std::map<std::string, AlbaNumber>;

bool hasAnyFunctions(Term const& term);

AlbaNumber getCoefficientOfMonomialWithNoVariables(Polynomial const& polynomial);
AlbaNumber getCoefficientOfMonomialWithVariableOnly(
        Polynomial const& polynomial,
        std::string const& variableName);

VariableToValueMap getCoefficientsForVariablesOnly(Polynomial const& polynomial);

void retrieveTermsFromTermsWithDetails(Terms & terms, TermsWithDetails const& termsWithDetails);

Terms retrieveSubExpressionsAndSubFunctions(Term const& term);
Terms retrieveSubTerms(Term const& term);

TermsWithDetails retrieveTermsWithDetailsThatSatisfiesCondition(
        TermsWithDetails const& termsWithDetails,
        ConditionFunctionForTermsWithDetails const& conditionFunction);

}

}
