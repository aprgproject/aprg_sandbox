#include "TermsOverTerms.hpp"

#include <Equation/Constructs/Factorization.hpp>
#include <Equation/Constructs/PolynomialOverPolynomial.hpp>
#include <Equation/Utilities.hpp>

#include <sstream>

using namespace alba::equation::Factorization;
using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

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

void TermsOverTerms::simplify()
{
    //remove common terms first don't make it big
    simplifyPolynomialsAndShouldFactorize(false);
    removeSameTermsInNumeratorAndDenominator();
}

void TermsOverTerms::simplifyToFactors()
{
    simplifyPolynomialsAndShouldFactorize(true);
    removeSameTermsInNumeratorAndDenominator();
}

TermsWithDetails TermsOverTerms::getNumeratorAndDenominatorAsTermWithDetails() const
{
    TermsWithDetails result;
    if(areTermsEmptyOrValueOne(m_numerators))
    {
        result.emplace_back(getBaseTermConstReferenceFromTerm(Term(1)), TermAssociationType::Positive);
    }
    for(Term const& numerator : m_numerators)
    {
        result.emplace_back(getBaseTermConstReferenceFromTerm(numerator), TermAssociationType::Positive);
    }
    for(Term const& denominator : m_denominators)
    {
        result.emplace_back(getBaseTermConstReferenceFromTerm(denominator), TermAssociationType::Negative);
    }
    return result;
}

Terms const& TermsOverTerms::getNumerators() const
{
    return m_numerators;
}

Terms const& TermsOverTerms::getDenominators() const
{
    return m_denominators;
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

void TermsOverTerms::simplifyPolynomialsAndShouldFactorize(bool const shouldFactorize)
{
    Polynomial polynomialNumerator(createPolynomialFromConstant(1));
    Terms remainingNumerators;
    for(Term const& numeratorTerm : m_numerators)
    {
        if(canBeConvertedToPolynomial(numeratorTerm))
        {
            polynomialNumerator.multiplyPolynomial(createPolynomialIfPossible(numeratorTerm));
        }
        else
        {
            remainingNumerators.emplace_back(numeratorTerm);
        }
    }
    Polynomial polynomialDenominator(createPolynomialFromConstant(1));
    Terms remainingDenominators;
    for(Term const& denominatorTerm : m_denominators)
    {
        if(canBeConvertedToPolynomial(denominatorTerm))
        {
            polynomialDenominator.multiplyPolynomial(createPolynomialIfPossible(denominatorTerm));
        }
        else
        {
            remainingDenominators.emplace_back(denominatorTerm);
        }
    }
    PolynomialOverPolynomial numeratorAndDenominator(polynomialNumerator, polynomialDenominator);
    numeratorAndDenominator.simplify();
    polynomialNumerator = numeratorAndDenominator.getNumerator();
    polynomialDenominator = numeratorAndDenominator.getDenominator();
    m_numerators.clear();
    m_denominators.clear();
    if(polynomialNumerator.isZero())
    {
        m_numerators.emplace_back(Term(Constant(0)));
    }
    else if(!polynomialNumerator.isOne())
    {
        if(shouldFactorize)
        {
            Polynomials polynomialNumerators(factorize(polynomialNumerator));
            for(Polynomial const& polynomial : polynomialNumerators)
            {
                m_numerators.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomial));
            }
        }
        else
        {
            m_numerators.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomialNumerator));
        }
    }
    for(Term const& numeratorTerm : remainingNumerators)
    {
        m_numerators.emplace_back(numeratorTerm);
    }
    if(polynomialDenominator.isZero())
    {
        m_denominators.emplace_back(Term(Constant(0)));
    }
    else if(!polynomialDenominator.isOne())
    {
        if(shouldFactorize)
        {
            Polynomials polynomialDenominators(factorize(polynomialDenominator));
            for(Polynomial const& polynomial : polynomialDenominators)
            {
                m_denominators.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomial));
            }
        }
        else
        {
            m_denominators.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomialDenominator));
        }
    }
    for(Term const& denominatorTerm : remainingDenominators)
    {
        m_denominators.emplace_back(denominatorTerm);
    }
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

bool TermsOverTerms::areTermsEmptyOrValueOne(Terms const& terms) const
{
    bool result(false);
    if(terms.empty())
    {
        result = true;
    }
    else
    {
        result = terms.at(0).isTheValueOne();
    }
    return result;
}

}

}
