#include "Monomial.hpp"

#include <sstream>

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
    putVariablesWithExponents(variablesWithExponents);
}

Monomial::Monomial(AlbaNumber const& constant, VariablesToExponentsMap const& variablesWithExponents)
    : m_constant(constant)
    , m_variablesToExponentsMap(variablesWithExponents)
{}

Monomial::VariablesToExponentsMap Monomial::combineVariableExponentMapByMultiplication(
        VariablesToExponentsMap const& variablesMap1,
        VariablesToExponentsMap const& variablesMap2)
{
    VariablesToExponentsMap newVariableMap;
    for(VariableExponentPair const variableExponentPair : variablesMap1)
    {
        newVariableMap[variableExponentPair.first] = newVariableMap[variableExponentPair.first] + variableExponentPair.second;
    }
    for(VariableExponentPair const variableExponentPair : variablesMap2)
    {
        newVariableMap[variableExponentPair.first] = newVariableMap[variableExponentPair.first] + variableExponentPair.second;
    }
    return newVariableMap;
}

Monomial::VariablesToExponentsMap Monomial::combineVariableExponentMapByDivision(
        VariablesToExponentsMap const& variablesMap1,
        VariablesToExponentsMap const& variablesMap2)
{
    VariablesToExponentsMap newVariableMap;
    for(VariableExponentPair const variableExponentPair : variablesMap1)
    {
        newVariableMap[variableExponentPair.first] = newVariableMap[variableExponentPair.first] + variableExponentPair.second;
    }
    for(VariableExponentPair const variableExponentPair : variablesMap2)
    {
        newVariableMap[variableExponentPair.first] = newVariableMap[variableExponentPair.first] - variableExponentPair.second;
    }
    return newVariableMap;
}

bool Monomial::operator==(Monomial const& second) const
{
    return m_constant == second.m_constant && m_variablesToExponentsMap == second.m_variablesToExponentsMap;
}

bool Monomial::operator!=(Monomial const& second) const
{
    return !(operator==(second));
}

bool Monomial::operator<(Monomial const& second) const
{
    bool result(false);
    if(m_variablesToExponentsMap == second.m_variablesToExponentsMap)
    {
        result = m_constant < second.m_constant;
    }
    else
    {
        AlbaNumber degree1(getDegree());
        AlbaNumber degree2(second.getDegree());
        if(degree1 == degree2)
        {
            result = m_variablesToExponentsMap < second.m_variablesToExponentsMap;
        }
        else
        {
            result = degree1 < degree2;
        }
    }
    return result;
}
bool Monomial::isOne() const
{
    return m_constant == 1 && isConstantOnly();}

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

Monomial::VariablesToExponentsMap const& Monomial::getVariablesToExponentsMapConstReference() const
{
    return m_variablesToExponentsMap;
}

AlbaNumber Monomial::getDegree() const
{
    AlbaNumber degree;
    for(VariableExponentPair const& variableExponentPair : m_variablesToExponentsMap)
    {
        degree = degree+variableExponentPair.second;
    }
    return degree;
}

string Monomial::getDisplayableString() const
{
    stringstream result;    result << m_constant.getDisplayableString();
    for(VariableExponentPair const& variableExponentsPair : m_variablesToExponentsMap)
    {
        result << "|"               << variableExponentsPair.first
               << "^"
               << variableExponentsPair.second.getDisplayableString()
               << "|";
    }
    return result.str();
}

void Monomial::simplify()
{
    removeZeroExponents();
}

void Monomial::multiplyNumber(AlbaNumber const& number)
{
    m_constant = m_constant * number;
}

void Monomial::raiseToPowerNumber(AlbaNumber const& number)
{
    m_constant = m_constant ^ number;
    for(VariablesToExponentsMapIterator it = m_variablesToExponentsMap.begin();
        it != m_variablesToExponentsMap.end();
        it++)
    {
        AlbaNumber & exponent(it->second);
        exponent=exponent*number;
    }
}

void Monomial::multiplyMonomial(Monomial const& monomial)
{
    VariablesToExponentsMap newVariablesMap(
                combineVariableExponentMapByMultiplication(
                    m_variablesToExponentsMap,
                    monomial.m_variablesToExponentsMap));
    m_constant = m_constant * monomial.m_constant;
    m_variablesToExponentsMap = newVariablesMap;
}

void Monomial::divideMonomial(Monomial const& monomial)
{
    VariablesToExponentsMap newVariablesMap(
                combineVariableExponentMapByDivision(
                    m_variablesToExponentsMap,
                    monomial.m_variablesToExponentsMap));
    m_constant = m_constant / monomial.m_constant;
    m_variablesToExponentsMap = newVariablesMap;
}

void Monomial::setConstant(AlbaNumber const& constant)
{
    m_constant = constant;
}

void Monomial::putVariablesWithExponents(initializer_list<VariableExponentPair> const& variablesWithExponents)
{
    for(VariableExponentPair const& variableExponentsPair : variablesWithExponents)
    {
        putVariableWithExponent(variableExponentsPair.first, variableExponentsPair.second);
    }
}

void Monomial::putVariableWithExponent(string const& variable, AlbaNumber const& exponent)
{
    m_variablesToExponentsMap[variable]=exponent;
}

void Monomial::removeZeroExponents()
{
    VariablesToExponentsMap oldVariableMap(m_variablesToExponentsMap);
    m_variablesToExponentsMap.clear();
    for(VariableExponentPair const& variableExponentPair : oldVariableMap)
    {
        if(variableExponentPair.second != 0)
        {
            m_variablesToExponentsMap.emplace(variableExponentPair.first, variableExponentPair.second);
        }
    }
}

}

}
