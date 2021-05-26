#include "Monomial.hpp"

using namespace std;

namespace alba
{

namespace equation
{

Monomial::Monomial()
{}

Monomial::Monomial(AlbaNumber const& constant, initializer_list<VariableWithExponents> const& variablesWithExponents)
    : m_constant(constant)
{
    setVariablesWithExponents(variablesWithExponents);
}

AlbaNumber const& Monomial::getConstantConstReference() const
{
    return m_constant;
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

void Monomial::setVariablesWithExponents(initializer_list<VariableWithExponents> const& variablesWithExponents)
{
    for(VariableWithExponents const& variableExponentsPair : variablesWithExponents)
    {
        setVariableWtihExponent(variableExponentsPair.first, variableExponentsPair.second);
    }
}



}

}
