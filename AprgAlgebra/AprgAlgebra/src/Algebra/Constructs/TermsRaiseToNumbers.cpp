#include "TermsRaiseToNumbers.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <algorithm>

namespace alba
{

namespace algebra
{

unsigned int TermsRaiseToNumbers::getSize() const
{
    return m_baseToExponentMap.size();
}

TermsRaiseToNumbers::BaseToExponentMap const& TermsRaiseToNumbers::getBaseToExponentMap() const
{
    return m_baseToExponentMap;
}

AlbaNumber TermsRaiseToNumbers::getExponentOfBase(
        Term const& base) const
{
    AlbaNumber result;
    auto const& it = m_baseToExponentMap.find(base);
    if(it != m_baseToExponentMap.cend())
    {
        result = it->second;
    }
    return result;
}

Terms TermsRaiseToNumbers::getTermsInMultiplicationOperation() const
{
    Terms result;
    for(auto const& baseExponentPair : m_baseToExponentMap)
    {
        Term const& base(baseExponentPair.first);
        AlbaNumber const& exponent(baseExponentPair.second);
        result.emplace_back(convertToTerm(base, exponent));
    }
    return result;
}

TermsWithDetails TermsRaiseToNumbers::getTermWithDetailsInMultiplicationAndDivisionOperation() const
{
    TermsWithDetails result;
    for(auto const& baseExponentPair : m_baseToExponentMap)
    {
        Term const& base(baseExponentPair.first);
        AlbaNumber const& exponent(baseExponentPair.second);
        if(exponent >= 0)
        {
            result.emplace_back(convertToTerm(base, exponent), TermAssociationType::Positive);
        }
        else
        {
            result.emplace_back(convertToTerm(base, exponent*-1), TermAssociationType::Negative);
        }
    }
    return result;
}

void TermsRaiseToNumbers::addExponents(
        TermsRaiseToNumbers const& termsRaiseToNumbers)
{
    for(auto const& baseExponentPair : termsRaiseToNumbers.m_baseToExponentMap)
    {
        m_baseToExponentMap[baseExponentPair.first] += baseExponentPair.second;
    }
}

void TermsRaiseToNumbers::addTerm(
        Term const& term,
        TermAssociationType const association)
{
    int sign = (association == TermAssociationType::Positive) ? 1 : -1;
    if(canBeConvertedToMonomial(term))
    {
        Monomial monomial(createMonomialIfPossible(term));
        AlbaNumber constant(monomial.getConstantConstReference());
        if(constant != 1)
        {
            m_baseToExponentMap[Term(constant)] += sign;
        }
        for(auto const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference())
        {
            m_baseToExponentMap[Term(variableExponentPair.first)] += (variableExponentPair.second * sign);
        }
    }
    else
    {
        TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(term));
        Term baseToPut(termRaiseToANumber.getBase());
        AlbaNumber exponentToPut(termRaiseToANumber.getExponent());
        m_baseToExponentMap[baseToPut] += (exponentToPut * sign);
    }
}

void TermsRaiseToNumbers::addTerms(
        Terms const& terms,
        TermAssociationType const association)
{
    for(Term const& term : terms)
    {
        addTerm(term, association);
    }
}

void TermsRaiseToNumbers::subtractExponents(
        TermsRaiseToNumbers const& termsRaiseToNumbers)
{
    for(auto const& baseExponentPair : termsRaiseToNumbers.m_baseToExponentMap)
    {
        m_baseToExponentMap[baseExponentPair.first] -= baseExponentPair.second;
    }
}

void TermsRaiseToNumbers::multiplyNumberToExponents(
        AlbaNumber const& number)
{
    for(auto& baseExponentPair : m_baseToExponentMap)
    {
        baseExponentPair.second *= number;
    }
}

void TermsRaiseToNumbers::setBaseAndExponent(
        Term const& base,
        AlbaNumber const& exponent)
{
    m_baseToExponentMap[base] = exponent;
}

void TermsRaiseToNumbers::removeItemWithBase(
        Term const& base)
{
    m_baseToExponentMap.erase(base);
}

void TermsRaiseToNumbers::simplify()
{
    removeItemsWithExponentsZero();
}

void TermsRaiseToNumbers::removeItemsWithExponentsZero()
{
    for(auto it = m_baseToExponentMap.begin(); it!=m_baseToExponentMap.end(); )
    {
        if(it->second == 0)
        {
            m_baseToExponentMap.erase(it);
            it = m_baseToExponentMap.begin();
        }
        else
        {
            it++;
        }
    }
}

Term TermsRaiseToNumbers::convertToTerm(
        Term const& base,
        AlbaNumber const& exponent) const
{
    Term result;
    if(exponent == 1)
    {
        result = base;
    }
    else
    {
        TermRaiseToANumber termRaiseToANumber(base, exponent);
        result = termRaiseToANumber.getCombinedTerm();
    }
    return result;
}


}

}
