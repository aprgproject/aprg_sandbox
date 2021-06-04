#include "Monomial.hpp"

using namespace std;

namespace alba
{

namespace equation
{

Monomial::Monomial()
{}

Monomial::Monomial(AlbaNumber const& constant, initializer_list<VariableExponentPair> const& variablesWithExponents)
    : m_constant(constant)
{
    setVariablesWithExponents(variablesWithExponents);
}

Monomial::Monomial(AlbaNumber const& constant, VariablesToExponentsMap const& variablesWithExponents)
    : m_constant(constant)
    , m_variablesToExponentsMap(variablesWithExponents)
{}

AlbaNumber const& Monomial::getConstantConstReference() const
{
    return m_constant;
}

Monomial::VariablesToExponentsMap & Monomial::getVariablesToExponentsMapReference()
{
    return m_variablesToExponentsMap;
}

Monomial::VariablesToExponentsMap const& Monomial::getVariablesToExponentsMapConstReference() const
{
    return m_variablesToExponentsMap;
}

void Monomial::setConstant(AlbaNumber const& constant)
{
    m_constant = constant;
}

void Monomial::setVariableWtihExponent(
        string const& variable,
        AlbaNumber const& exponent)
{
    m_variablesToExponentsMap[variable]=exponent;
}

void Monomial::setVariablesWithExponents(initializer_list<VariableExponentPair> const& variablesWithExponents)
{
    for(VariableExponentPair const& variableExponentsPair : variablesWithExponents)
    {
        setVariableWtihExponent(variableExponentsPair.first, variableExponentsPair.second);
    }
}



}

}
