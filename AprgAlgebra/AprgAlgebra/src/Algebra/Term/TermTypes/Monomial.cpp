#include "Monomial.hpp"

#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

#include <set>
#include <sstream>

using namespace std;

namespace alba
{

namespace algebra
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
        //highest degree is the lower priority for sorting
        AlbaNumber degree1(getDegree());
        AlbaNumber degree2(second.getDegree());
        if(degree1 == degree2)
        {
            result = isLessThanByComparingVariableNameMaps(*this, second);
        }
        else
        {
            result = degree1 < degree2;
        }
    }
    return result;
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

bool Monomial::hasASingleVariable() const
{
    return m_variablesToExponentsMap.size() == 1;
}

bool Monomial::hasNegativeExponents() const
{
    bool result(false);
    for(VariableExponentPair const& variableExponentsPair : m_variablesToExponentsMap)
    {
        if(variableExponentsPair.second < 0)
        {
            result=true;
            break;
        }
    }
    return result;
}

AlbaNumber const& Monomial::getConstantConstReference() const
{
    return m_constant;
}

Monomial::VariablesToExponentsMap const& Monomial::getVariablesToExponentsMapConstReference() const
{
    return m_variablesToExponentsMap;
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

AlbaNumber Monomial::getDegree() const
{
    AlbaNumber degree;
    for(VariableExponentPair const& variableExponentPair : m_variablesToExponentsMap)
    {
        degree = degree + variableExponentPair.second;
    }
    return degree;
}

AlbaNumber Monomial::getMaxExponent() const
{
    AlbaNumber maxExponent;
    bool isFirst(true);
    for(VariableExponentPair const& variableExponentPair : m_variablesToExponentsMap)
    {
        if(isFirst)
        {
            maxExponent = variableExponentPair.second;
            isFirst = false;
        }
        else
        {
            maxExponent = max(maxExponent, variableExponentPair.second);
        }
    }
    return maxExponent;
}

AlbaNumber Monomial::getExponentForVariable(string const& variableName) const
{
    AlbaNumber exponent(0);
    if(m_variablesToExponentsMap.find(variableName) != m_variablesToExponentsMap.cend())
    {
        exponent = m_variablesToExponentsMap.at(variableName);
    }
    return exponent;
}

string Monomial::getDisplayableString() const
{
    stringstream result;
    result << m_constant.getDisplayableString();
    for(VariableExponentPair const& variableExponentsPair : m_variablesToExponentsMap)
    {
        result << "[" << variableExponentsPair.first;
        AlbaNumber const& exponent(variableExponentsPair.second);
        if(!(exponent.isIntegerType() && exponent.getInteger()==1))
        {
            result << "^" << variableExponentsPair.second.getDisplayableString();
        }
        result << "]";
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

void Monomial::divideNumber(AlbaNumber const& number)
{
    m_constant = m_constant / number;
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

void Monomial::putVariablesWithExponents(VariablesToExponentsMap const& variablesWithExponents)
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

bool Monomial::isLessThanByComparingVariableNameMaps(
        Monomial const& monomial1,
        Monomial const& monomial2) const
{
    set<string> variableNames;
    for(VariableExponentPair const& nameExponentPair : monomial1.getVariablesToExponentsMapConstReference())
    {
        variableNames.emplace(nameExponentPair.first);
    }
    for(VariableExponentPair const& nameExponentPair : monomial2.getVariablesToExponentsMapConstReference())
    {
        variableNames.emplace(nameExponentPair.first);
    }
    bool result(false);
    for(string const& variableName : variableNames)
    {
        AlbaNumber exponent1(monomial1.getExponentForVariable(variableName));
        AlbaNumber exponent2(monomial2.getExponentForVariable(variableName));
        if(exponent1 != exponent2)
        {
            result = exponent1 < exponent2;
            break;
        }
    }
    return result;
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

ostream & operator<<(ostream & out, Monomial const& monomial)
{
    out << monomial.getDisplayableString();
    return out;
}

}

}
