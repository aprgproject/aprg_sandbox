#include "TermsRaiseToNumbers.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

namespace alba
{

namespace algebra
{

TermsRaiseToNumbers::TermsRaiseToNumbers()
{}

TermsRaiseToNumbers::TermsRaiseToNumbers(
        BaseToExponentMap const& baseToExponentMap)
    : m_baseToExponentMap(baseToExponentMap)
{}

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

Term TermsRaiseToNumbers::getCombinedTerm() const
{
    TermsWithDetails termsWithDetails(getTermWithDetailsInMultiplicationAndDivisionOperation());
    if(termsWithDetails.empty())
    {
        termsWithDetails.emplace_back(Term(1), TermAssociationType::Positive);
    }
    return convertExpressionToSimplestTerm(Expression(OperatorLevel::MultiplicationAndDivision, termsWithDetails));
}

void TermsRaiseToNumbers::addExponents(
        TermsRaiseToNumbers const& termsRaiseToNumbers)
{
    for(auto const& baseExponentPair : termsRaiseToNumbers.m_baseToExponentMap)
    {
        m_baseToExponentMap[baseExponentPair.first] += baseExponentPair.second;
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

void TermsRaiseToNumbers::multiplyToExponents(
        AlbaNumber const& number)
{
    for(auto& baseExponentPair : m_baseToExponentMap)
    {
        baseExponentPair.second *= number;
    }
}

void TermsRaiseToNumbers::putTerm(
        Term const& term,
        TermAssociationType const association)
{
    int sign = (association == TermAssociationType::Positive) ? 1 : -1;
    if(canBeConvertedToMonomial(term))
    {
        Monomial monomial(createMonomialIfPossible(term));
        AlbaNumber const& constant(monomial.getConstantConstReference());
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
        m_baseToExponentMap[termRaiseToANumber.getBase()] += (termRaiseToANumber.getExponent() * sign);
    }
}

void TermsRaiseToNumbers::putTerms(
        Terms const& terms,
        TermAssociationType const association)
{
    for(Term const& term : terms)
    {
        putTerm(term, association);
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

void TermsRaiseToNumbers::clear()
{
    m_baseToExponentMap.clear();
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
        result = TermRaiseToANumber(base, exponent).getCombinedTerm();
    }
    return result;
}


}

}
