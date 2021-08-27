#include "RetrieveHelpers.hpp"

using namespace std;

namespace alba{

namespace algebra
{
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
