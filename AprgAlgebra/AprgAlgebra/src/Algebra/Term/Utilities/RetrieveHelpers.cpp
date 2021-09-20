#include "RetrieveHelpers.hpp"

#include <Algebra/Retrieval/FunctionsRetriever.hpp>

#include <algorithm>


using namespace std;

namespace alba
{

namespace algebra
{

bool hasAnyFunctions(Term const& term)
{
    FunctionsRetriever functionsRetriever([](Function const&)
    {
        return true;
    });
    functionsRetriever.retrieveFromTerm(term);
    return !functionsRetriever.getSavedData().empty();
}

void retrieveTermsOnly(Terms & terms, TermsWithDetails const& termsWithDetails)
{
    terms.reserve(terms.size() + termsWithDetails.size());
    transform(termsWithDetails.cbegin(), termsWithDetails.cend(), back_inserter(terms), []
              (TermWithDetails const& termWithDetails)
    {
        return getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer);
    });
}

AlbaNumber getCoefficientOfMonomialWithNoVariables(
        Polynomial const& polynomial)
{
    AlbaNumber coefficientValue;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        Monomial::VariablesToExponentsMap const& variableToExponentMap(
                    monomial.getVariablesToExponentsMapConstReference());
        if(variableToExponentMap.empty())
        {
            coefficientValue = monomial.getConstantConstReference();
            break;
        }
    }
    return coefficientValue;
}

AlbaNumber getCoefficientOfMonomialWithVariableOnly(
        Polynomial const& polynomial,
        string const& variableName)
{
    AlbaNumber coefficientValue;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        Monomial::VariablesToExponentsMap const& variableToExponentMap(
                    monomial.getVariablesToExponentsMapConstReference());
        if(variableToExponentMap.size() == 1)
        {
            auto const& variableExponentPair = *(variableToExponentMap.cbegin());
            if(variableExponentPair.first == variableName)
            {
                coefficientValue = monomial.getConstantConstReference();
                break;
            }
        }
    }
    return coefficientValue;
}

VariableToValueMap getCoefficientsForVariablesOnly(
        Polynomial const& polynomial)
{
    VariableToValueMap result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        Monomial::VariablesToExponentsMap const& variableToExponentMap(
                    monomial.getVariablesToExponentsMapConstReference());
        if(variableToExponentMap.size() == 1)
        {
            auto const& variableExponentPair = *(variableToExponentMap.cbegin());
            result.emplace(variableExponentPair.first, monomial.getConstantConstReference());
        }
    }
    return result;
}

}

}
