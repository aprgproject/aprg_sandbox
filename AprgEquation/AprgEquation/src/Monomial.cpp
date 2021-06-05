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

bool Monomial::operator==(Monomial const& second) const
{
    return m_constant == second.m_constant && m_variablesToExponentsMap == second.m_variablesToExponentsMap;
}

bool Monomial::isZero() const
{
    return m_constant == 0;
}

bool Monomial::isConstantOnly() const
{
    return m_variablesToExponentsMap.empty();
}

bool Monomial::isVariableOnly() const
{
    return m_constant == 1 &&
            m_variablesToExponentsMap.size() == 1 &&
            (m_variablesToExponentsMap.cbegin())->second == 1;
}

string Monomial::getFirstVariableName() const
{
    string variableName;
    if(!m_variablesToExponentsMap.empty())
    {
        variableName = (m_variablesToExponentsMap.cbegin())->first;
    }
    return variableName;
}

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
