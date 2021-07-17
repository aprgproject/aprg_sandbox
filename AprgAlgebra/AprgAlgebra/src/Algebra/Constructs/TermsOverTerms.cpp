#include "TermsOverTerms.hpp"

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Factorization/Factorization.hpp>
#include <Algebra/Utilities.hpp>

#include <algorithm>
#include <sstream>

using namespace alba::algebra::Factorization;
using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
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
        result.emplace_back(numerator, TermAssociationType::Positive);
    }
    for(Term const& denominator : m_denominators)
    {
        result.emplace_back(denominator, TermAssociationType::Negative);
    }
    return result;
}

std::string TermsOverTerms::getDisplayableString() const
{
    stringstream result;
    result << "Numerators:" << endl;
    for(Term const& numerator : m_numerators)
    {
        result << "[" << numerator.getDisplayableString() << "]" << endl;
    }
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
    removeTermsThatHasNoEffectInNumeratorAndDenominator();
    removeSameTermsInNumeratorAndDenominator();
    simplifyPolynomialsToPolynomialsOverPolynomials();
}

void TermsOverTerms::simplifyToFactors()
{
    factorizeNumeratorsAndDenominators();
    removeTermsThatHasNoEffectInNumeratorAndDenominator();
    removeSameTermsInNumeratorAndDenominator();
    simplifyMonomialsToPolynomialsOverPolynomials();
}

void TermsOverTerms::clearThenEmplacePolynomialAndRemainingTerms(
        Polynomial const& polynomialNumerator,
        Terms const& remainingNumerators,
        Terms & termsToUpdate) const
{
    termsToUpdate.clear();
    emplacePolynomialIfNeeded(termsToUpdate, polynomialNumerator);
    termsToUpdate.reserve(remainingNumerators.size());
    copy(remainingNumerators.cbegin(), remainingNumerators.cend(), back_inserter(termsToUpdate));
}

void TermsOverTerms::factorizeNumeratorsAndDenominators()
{
    Terms numerators(m_numerators);
    m_numerators.clear();
    emplaceAndFactorizeAllTerms(m_numerators, numerators);
    Terms denominators(m_denominators);
    m_denominators.clear();
    emplaceAndFactorizeAllTerms(m_denominators, denominators);
}

void TermsOverTerms::emplaceAndFactorizeAllTerms(Terms & termsResult, Terms const& termsToCheck) const
{
    for(Term const& termToCheck : termsToCheck)
    {
        emplaceAndFactorizeTerm(termsResult, termToCheck);
    }
}

void TermsOverTerms::emplaceAndFactorizeTerm(Terms & termsResult, Term const& term) const
{
    if(term.isPolynomial())
    {
        Polynomial simplifiedPolynomial(term.getPolynomialConstReference());
        simplifiedPolynomial.simplify();
        emplaceAndFactorizePolynomialIfNeeded(termsResult, simplifiedPolynomial);
    }
    else
    {
        termsResult.emplace_back(term);
    }
}

void TermsOverTerms::emplaceAndFactorizePolynomialIfNeeded(Terms & termsResult, Polynomial const& polynomial) const
{
    if(polynomial.isZero())
    {
        termsResult.emplace_back(Term(Constant(0)));
    }
    else if(!polynomial.isOne())
    {
        Polynomials polynomialFactors(factorize(polynomial));
        for(Polynomial const& polynomialFactor : polynomialFactors)
        {
            termsResult.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomialFactor));
        }
    }
}

void TermsOverTerms::emplacePolynomialIfNeeded(Terms & termsResult, Polynomial const& polynomial) const
{
    if(polynomial.isZero())
    {
        termsResult.emplace_back(Term(Constant(0)));
    }
    else if(!polynomial.isOne())
    {
        termsResult.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomial));
    }
}

Polynomial TermsOverTerms::multiplyPolynomialTerms(Terms const& polynomialTerms) const
{
    Polynomial polynomialResult(createPolynomialFromConstant(1));
    for(Term const& polynomialTerm : polynomialTerms)
    {
        if(canBeConvertedToPolynomial(polynomialTerm))
        {
            polynomialResult.multiplyPolynomial(createPolynomialIfPossible(polynomialTerm));
        }
    }
    return polynomialResult;
}

void TermsOverTerms::removeTermsThatHasNoEffectInNumeratorAndDenominator()
{
    removeTermsThatHaveNoEffect(m_numerators);
    removeTermsThatHaveNoEffect(m_denominators);
}

void TermsOverTerms::removeSameTermsInNumeratorAndDenominator()
{
    for(Terms::iterator numeratorIt = m_numerators.begin();
        numeratorIt != m_numerators.end();
        numeratorIt++)
    {
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

void TermsOverTerms::removeTermsThatHaveNoEffect(Terms & terms) const
{
    terms.erase(remove_if(terms.begin(), terms.end(), [](Term const& term){
                    return willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term);
                }), terms.end());
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

void TermsOverTerms::simplifyMonomialsToPolynomialsOverPolynomials()
{
    Terms monomialsNumerators, nonMonomialNumerators, monomialDenominators, nonMonomialDenominators;
    segregateMonomialsAndNonMonomials(m_numerators, monomialsNumerators, nonMonomialNumerators);
    segregateMonomialsAndNonMonomials(m_denominators, monomialDenominators, nonMonomialDenominators);
    Polynomial polynomialNumerator(multiplyPolynomialTerms(monomialsNumerators));
    Polynomial polynomialDenominator(multiplyPolynomialTerms(monomialDenominators));
    simplifyPolynomialNumeratorAndPolynomialDenominator(polynomialNumerator, polynomialDenominator);
    clearThenEmplacePolynomialAndRemainingTerms(polynomialNumerator, nonMonomialNumerators, m_numerators);
    clearThenEmplacePolynomialAndRemainingTerms(polynomialDenominator, nonMonomialDenominators, m_denominators);
}

void TermsOverTerms::simplifyPolynomialsToPolynomialsOverPolynomials()
{
    Terms polynomialNumerators, nonPolynomialNumerators, polynomialDenominators, nonPolynomialDenominators;
    segregatePolynomialAndNonPolynomials(m_numerators, polynomialNumerators, nonPolynomialNumerators);
    segregatePolynomialAndNonPolynomials(m_denominators, polynomialDenominators, nonPolynomialDenominators);
    Polynomial polynomialNumerator(multiplyPolynomialTerms(polynomialNumerators));
    Polynomial polynomialDenominator(multiplyPolynomialTerms(polynomialDenominators));
    simplifyPolynomialNumeratorAndPolynomialDenominator(polynomialNumerator, polynomialDenominator);
    clearThenEmplacePolynomialAndRemainingTerms(polynomialNumerator, nonPolynomialNumerators, m_numerators);
    clearThenEmplacePolynomialAndRemainingTerms(polynomialDenominator, nonPolynomialDenominators, m_denominators);
}

}

}
