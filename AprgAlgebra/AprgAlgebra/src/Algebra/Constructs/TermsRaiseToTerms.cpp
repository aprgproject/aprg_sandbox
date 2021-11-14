#include "TermsRaiseToTerms.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

namespace alba
{

namespace algebra
{

TermsRaiseToTerms::TermsRaiseToTerms()
{}

TermsRaiseToTerms::TermsRaiseToTerms(
        BaseToExponentMap const& baseToExponentMap)
    : m_baseToExponentMap(baseToExponentMap)
{}

TermsRaiseToTerms::BaseToExponentMap const& TermsRaiseToTerms::getBaseToExponentMap() const
{
    return m_baseToExponentMap;
}

Term TermsRaiseToTerms::getExponentOfBase(
        Term const& base) const
{
    Term result;
    auto const& it = m_baseToExponentMap.find(base);
    if(it != m_baseToExponentMap.cend())
    {
        result = it->second;
    }
    return result;
}

Terms TermsRaiseToTerms::getTermsInMultiplicationOperation() const
{
    Terms result;
    for(auto const& baseExponentPair : m_baseToExponentMap)
    {
        Term const& base(baseExponentPair.first);
        Term const& exponent(baseExponentPair.second);
        result.emplace_back(convertToTerm(base, exponent));
    }
    return result;
}

TermsWithDetails TermsRaiseToTerms::getTermWithDetailsInMultiplicationAndDivisionOperation() const
{
    TermsWithDetails result;
    for(auto const& baseExponentPair : m_baseToExponentMap)
    {
        Term const& base(baseExponentPair.first);
        Term const& exponent(baseExponentPair.second);
        if(isANegativeTerm(exponent))
        {
            result.emplace_back(convertToTerm(base, exponent*-1), TermAssociationType::Negative);
        }
        else
        {
            result.emplace_back(convertToTerm(base, exponent), TermAssociationType::Positive);
        }
    }
    return result;
}

Term TermsRaiseToTerms::getCombinedTerm() const
{
    TermsWithDetails termsWithDetails(getTermWithDetailsInMultiplicationAndDivisionOperation());
    if(termsWithDetails.empty())
    {
        termsWithDetails.emplace_back(Term(1), TermAssociationType::Positive);
    }
    return convertExpressionToSimplestTerm(Expression(OperatorLevel::MultiplicationAndDivision, termsWithDetails));
}

void TermsRaiseToTerms::addExponents(
        TermsRaiseToTerms const& termsRaiseToNumbers)
{
    for(auto const& baseExponentPair : termsRaiseToNumbers.m_baseToExponentMap)
    {
        m_baseToExponentMap[baseExponentPair.first] += baseExponentPair.second;
    }
}

void TermsRaiseToTerms::subtractExponents(
        TermsRaiseToTerms const& termsRaiseToNumbers)
{
    for(auto const& baseExponentPair : termsRaiseToNumbers.m_baseToExponentMap)
    {
        m_baseToExponentMap[baseExponentPair.first] -= baseExponentPair.second;
    }
}

void TermsRaiseToTerms::multiplyToExponents(
        Term const& term)
{
    for(auto& baseExponentPair : m_baseToExponentMap)
    {
        baseExponentPair.second *= term;
    }
}

void TermsRaiseToTerms::putTerm(
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
            if(constant.isFractionType())
            {
                AlbaNumber::FractionData fractionData(constant.getFractionData());
                if(fractionData.numerator != 1)
                {
                    m_baseToExponentMap[Term(fractionData.numerator)] += Term(sign);
                }
                if(fractionData.denominator != 1)
                {
                    m_baseToExponentMap[Term(fractionData.denominator)] += Term(sign*-1);
                }
            }
            else
            {
                m_baseToExponentMap[Term(constant)] += Term(sign);
            }
        }
        for(auto const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference())
        {            m_baseToExponentMap[Term(variableExponentPair.first)] += Term(variableExponentPair.second * sign);
        }
    }
    else    {
        TermRaiseToTerms termRaiseTerms(createTermRaiseToTermsFromTerm(term));
        m_baseToExponentMap[termRaiseTerms.getBase()] += Term(termRaiseTerms.getCombinedExponents() * sign);
    }
}

void TermsRaiseToTerms::putTerms(
        Terms const& terms,
        TermAssociationType const association)
{
    for(Term const& term : terms)
    {
        putTerm(term, association);
    }
}

void TermsRaiseToTerms::setBaseAndExponent(
        Term const& base,
        Term const& exponent)
{
    m_baseToExponentMap[base] = exponent;
}

void TermsRaiseToTerms::removeItemWithBase(
        Term const& base)
{
    m_baseToExponentMap.erase(base);
}

void TermsRaiseToTerms::simplify()
{
    removeItemsWithExponentsZero();
}

void TermsRaiseToTerms::removeItemsWithExponentsZero()
{
    for(auto it = m_baseToExponentMap.begin(); it!=m_baseToExponentMap.end(); )
    {
        if(isTheValue(it->second, 0))
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

Term TermsRaiseToTerms::convertToTerm(
        Term const& base,
        Term const& exponent) const
{
    Term result;
    if(exponent == Term(1))
    {
        result = base;
    }
    else
    {
        result = TermRaiseToTerms(base, exponent).getCombinedTerm();
    }
    result.simplify();
    return result;
}


}

}
