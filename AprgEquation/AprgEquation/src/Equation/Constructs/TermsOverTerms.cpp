#include "TermsOverTerms.hpp"

#include <Equation/Constructs/Factorization.hpp>
#include <Equation/Constructs/PolynomialOverPolynomial.hpp>
#include <Equation/Utilities.hpp>

#include <sstream>

using namespace alba::equation::Factorization;
using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

TermsOverTerms::TermsOverTerms(Terms const& numerators, Terms const& denominators)
    : m_numerators(numerators)
    , m_denominators(denominators)
{}

TermsOverTerms::TermsOverTerms(
        TermsWithDetails const& numeratorsWithDetails,
        TermsWithDetails const& denominatorsWithDetails)
{
    for(TermWithDetails const& numeratorWithDetails : numeratorsWithDetails)
    {
        Term const& numerator(getTermConstReferenceFromSharedPointer(numeratorWithDetails.baseTermSharedPointer));
        m_numerators.emplace_back(numerator);
    }
    for(TermWithDetails const& denominatorWithDetails : denominatorsWithDetails)
    {
        Term const& denominator(getTermConstReferenceFromSharedPointer(denominatorWithDetails.baseTermSharedPointer));
        m_denominators.emplace_back(denominator);
    }
}

Terms const& TermsOverTerms::getNumerators() const
{
    return m_numerators;
}

Terms const& TermsOverTerms::getDenominators() const
{
    return m_denominators;
}

TermsWithDetails TermsOverTerms::getNumeratorAndDenominatorAsTermWithDetails() const
{
    TermsWithDetails result;
    for(Term const& numerator : m_numerators)
    {
        result.emplace_back(getBaseTermConstReferenceFromTerm(numerator), TermAssociationType::Positive);    }
    for(Term const& denominator : m_denominators)
    {
        result.emplace_back(getBaseTermConstReferenceFromTerm(denominator), TermAssociationType::Negative);    }
    return result;
}

std::string TermsOverTerms::getDisplayableString() const
{
    stringstream result;    result << "Numerators:" << endl;
    for(Term const& numerator : m_numerators)
    {
        result << "[" << numerator.getDisplayableString() << "]" << endl;    }
    result << "Denominators:" << endl;
    for(Term const& denominator : m_denominators)
    {
        result << "[" << denominator.getDisplayableString() << "]" << endl;
    }
    return result.str();
}

void TermsOverTerms::simplify()
{
    factorizeNumeratorsAndDenominators();
    removeSameTermsInNumeratorAndDenominator();
    simplifyPolynomialsAndPutFactorsIfNeeded(false);
    removeSameTermsInNumeratorAndDenominator();
}

void TermsOverTerms::simplifyToFactors()
{
    factorizeNumeratorsAndDenominators();
    removeSameTermsInNumeratorAndDenominator();
    simplifyPolynomialsAndPutFactorsIfNeeded(true);
    removeSameTermsInNumeratorAndDenominator();
}

void TermsOverTerms::factorizeNumeratorsAndDenominators()
{
    Terms numerators(m_numerators);
    m_numerators.clear();
    emplaceAndFactorizeAllTermsIfNeeded(m_numerators, numerators, true);
    Terms denominators(m_denominators);
    m_denominators.clear();
    emplaceAndFactorizeAllTermsIfNeeded(m_denominators, denominators, true);
}

void TermsOverTerms::simplifyPolynomialsAndPutFactorsIfNeeded(bool const shouldFactorize)
{
    Polynomial polynomialNumerator(createPolynomialFromConstant(1));
    Terms remainingNumerators;
    multiplyIfPolynomialElseEmplaceBack(polynomialNumerator, remainingNumerators, m_numerators);
    Polynomial polynomialDenominator(createPolynomialFromConstant(1));
    Terms remainingDenominators;
    multiplyIfPolynomialElseEmplaceBack(polynomialDenominator, remainingDenominators, m_denominators);
    simplifyPolynomialNumeratorAndPolynomialDenominator(polynomialNumerator, polynomialDenominator);
    m_numerators.clear();
    m_denominators.clear();
    emplaceAndFactorizePolynomialIfNeeded(m_numerators, polynomialNumerator, shouldFactorize);
    copy(remainingNumerators.cbegin(), remainingNumerators.cend(), back_inserter(m_numerators));
    emplaceAndFactorizePolynomialIfNeeded(m_denominators, polynomialDenominator, shouldFactorize);
    copy(remainingDenominators.cbegin(), remainingDenominators.cend(), back_inserter(m_denominators));
}

void TermsOverTerms::removeSameTermsInNumeratorAndDenominator(){
    for(Terms::iterator numeratorIt = m_numerators.begin();
        numeratorIt != m_numerators.end();
        numeratorIt++)    {
        for(Terms::iterator denominatorIt = m_denominators.begin();
            denominatorIt != m_denominators.end();
            denominatorIt++)
        {
            Term const& term1(*numeratorIt);
            Term const& term2(*denominatorIt);
            if(term1 == term2)
            {
                m_numerators.erase(numeratorIt);
                m_denominators.erase(denominatorIt);
                numeratorIt--;
                denominatorIt--;
            }
        }
    }
}

void TermsOverTerms::multiplyIfPolynomialElseEmplaceBack(
        Polynomial & polynomialResult,
        Terms & termsResult,
        Terms const& termsToCheck) const
{
    for(Term const& termToCheck : termsToCheck)
    {
        if(canBeConvertedToPolynomial(termToCheck))
        {
            polynomialResult.multiplyPolynomial(createPolynomialIfPossible(termToCheck));
        }
        else
        {
            termsResult.emplace_back(termToCheck);
        }
    }
}

void TermsOverTerms::emplaceAndFactorizeAllTermsIfNeeded(
        Terms & termsResult,
        Terms const& termsToCheck,
        bool const shouldFactorize) const
{
    for(Term const& termToCheck : termsToCheck)
    {
        emplaceAndFactorizeTermIfNeeded(termsResult, termToCheck, shouldFactorize);
    }
}

void TermsOverTerms::emplaceAndFactorizeTermIfNeeded(
        Terms & termsResult,
        Term const& term,
        bool const shouldFactorize) const
{
    if(term.isPolynomial())
    {
        Polynomial simplifiedPolynomial(term.getPolynomialConstReference());
        simplifiedPolynomial.simplify();
        emplaceAndFactorizePolynomialIfNeeded(termsResult, simplifiedPolynomial, shouldFactorize);
    }
    else
    {
        termsResult.emplace_back(term);
    }
}

void TermsOverTerms::emplaceAndFactorizePolynomialIfNeeded(
        Terms & termsResult,
        Polynomial const& polynomial,
        bool const shouldFactorize) const
{
    if(polynomial.isZero())
    {
        termsResult.emplace_back(Term(Constant(0)));
    }
    else if(!polynomial.isOne())
    {
        if(shouldFactorize)
        {
            Polynomials polynomialFactors(factorize(polynomial));
            for(Polynomial const& polynomialFactor : polynomialFactors)
            {
                termsResult.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomialFactor));
            }
        }
        else
        {
            termsResult.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomial));
        }
    }
}

void TermsOverTerms::simplifyPolynomialNumeratorAndPolynomialDenominator(
        Polynomial & polynomialNumerator,
        Polynomial & polynomialDenominator) const
{
    PolynomialOverPolynomial numeratorAndDenominator(polynomialNumerator, polynomialDenominator);
    numeratorAndDenominator.simplify();
    polynomialNumerator = numeratorAndDenominator.getNumerator();
    polynomialDenominator = numeratorAndDenominator.getDenominator();
}

}

}