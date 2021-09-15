#include "RationalizeTermOverTerm.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;

namespace alba
{

namespace algebra
{

RationalizeTermOverTerm::RationalizeTermOverTerm()
{}

RationalizeTermOverTerm::RationalizeTermOverTerm(
        Term const& numerator,
        Term const& denominator)
    : m_numerator(numerator)
    , m_denominator(denominator)
{}

Term const& RationalizeTermOverTerm::getNumerator() const
{
    return m_numerator;
}

Term const& RationalizeTermOverTerm::getDenominator() const
{
    return m_denominator;
}

Term RationalizeTermOverTerm::getCombinedTerm() const
{
    return Term(createExpressionIfPossible({m_numerator, Term("/"), m_denominator}));
}

void RationalizeTermOverTerm::rationalizeNumerator()
{
    rationalize(m_numerator, m_denominator);
}

void RationalizeTermOverTerm::rationalizeDenominator()
{
    rationalize(m_denominator, m_numerator);
}

void RationalizeTermOverTerm::rationalize(
        Term & termToRationalize,
        Term & otherTerm)
{
    Term multiplier(getMultiplierToRationalize(termToRationalize));
    while(!multiplier.isEmpty())
    {
        termToRationalize = Term(createExpressionIfPossible({termToRationalize, Term("*"), multiplier}));
        otherTerm = Term(createExpressionIfPossible({otherTerm, Term("*"), multiplier}));
        simplifyForRationalize(termToRationalize);
        simplifyForRationalize(otherTerm);
        multiplier = getMultiplierToRationalize(termToRationalize);
    }
}

void RationalizeTermOverTerm::simplifyForRationalize(Term & term)
{
    SimplificationOfExpression::ConfigurationDetails rationalizeConfigurationDetails(
                SimplificationOfExpression::getDefaultConfigurationDetails());
    rationalizeConfigurationDetails.shouldSimplifyToACommonDenominator = true;
    rationalizeConfigurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    rationalizeConfigurationDetails.shouldSimplifyByCombiningMonomialAndRadicalExpressionsInMultiplicationAndDivision = true;
    rationalizeConfigurationDetails.shouldSimplifyByCheckingPolynomialRaiseToANumber = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(rationalizeConfigurationDetails);
    term.simplify();
}

Term RationalizeTermOverTerm::getMultiplierToRationalize(
        Term const& term) const
{
    Term result;
    if(term.isPolynomial())
    {
        Polynomial multiplier(getMultiplierToRationalizeForPolynomial(term.getPolynomialConstReference()));
        if(!multiplier.isEmpty())
        {
            result = Term(multiplier);
        }
    }
    else if(term.isExpression())
    {
        Expression multiplier(getMultiplierToRationalizeForExpression(term.getExpressionConstReference()));
        if(!multiplier.isEmpty())
        {
            result = Term(multiplier);
        }
    }
    return result;
}

Polynomial RationalizeTermOverTerm::getMultiplierToRationalizeForPolynomial(
        Polynomial const& polynomial) const
{
    Polynomial result;
    Monomials const& monomials(polynomial.getMonomialsConstReference());
    if(monomials.size() == 2)
    {
        Monomial const& firstMonomial(monomials.at(0));
        Monomial const& secondMonomial(monomials.at(1));
        result = getMultiplierToRationalizeForPolynomial(firstMonomial, secondMonomial);
    }
    return result;
}

Polynomial RationalizeTermOverTerm::getMultiplierToRationalizeForPolynomial(
        Monomial const& firstMonomial,
        Monomial const& secondMonomial) const
{
    Polynomial result;
    AlbaNumber gcfOfExponents = getGreatestCommonFactorForAlbaNumber(
                getGcfOfExponentsInMonomial(firstMonomial),
                getGcfOfExponentsInMonomial(secondMonomial));
    if(gcfOfExponents.isFractionType())
    {
        AlbaNumber::FractionData exponentFraction(gcfOfExponents.getFractionData());
        if(isDivisible(exponentFraction.denominator, 2))
        {
            result = getMultiplierToRationalizeForPolynomialWhenExponentIsDivisibleByTwo(firstMonomial, secondMonomial);
        }
        else if(isDivisible(exponentFraction.denominator, 3))
        {
            result = getMultiplierToRationalizeForPolynomialWhenExponentIsDivisibleByThree(firstMonomial, secondMonomial);
        }
    }
    return result;
}

Polynomial RationalizeTermOverTerm::getMultiplierToRationalizeForPolynomialWhenExponentIsDivisibleByTwo(
        Monomial const& firstMonomial,
        Monomial const& secondMonomial) const
{
    Monomial newSecondMonomial(secondMonomial);
    newSecondMonomial.multiplyNumber(-1);
    return Polynomial{firstMonomial, newSecondMonomial};
}

Polynomial RationalizeTermOverTerm::getMultiplierToRationalizeForPolynomialWhenExponentIsDivisibleByThree(
        Monomial const& firstMonomial,
        Monomial const& secondMonomial) const
{
    Monomial newFirstMonomial(firstMonomial);
    Monomial newThirdMonomial(secondMonomial);
    newFirstMonomial.raiseToPowerNumber(2);
    newThirdMonomial.raiseToPowerNumber(2);
    Monomial newSecondMonomial(firstMonomial);
    newSecondMonomial.multiplyMonomial(secondMonomial);
    newSecondMonomial.multiplyNumber(-1);
    return Polynomial{newFirstMonomial, newSecondMonomial, newThirdMonomial};
}

Expression RationalizeTermOverTerm::getMultiplierToRationalizeForExpression(
        Expression const& expression) const
{
    Expression result;
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        TermsWithDetails const& termsWithDetails(
                    expression.getTermsWithAssociation().getTermsWithDetails());
        if(termsWithDetails.size() == 2)
        {
            TermWithDetails const& firstTermWithDetails(termsWithDetails.at(0));
            TermWithDetails const& secondTermWithDetails(termsWithDetails.at(1));
            result = getMultiplierToRationalizeForExpression(firstTermWithDetails, secondTermWithDetails);
        }
    }
    return result;
}

Expression RationalizeTermOverTerm::getMultiplierToRationalizeForExpression(
        TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails) const
{
    Expression result;
    Term const& firstTerm(getTermConstReferenceFromSharedPointer(firstTermWithDetails.baseTermSharedPointer));
    Term const& secondTerm(getTermConstReferenceFromSharedPointer(secondTermWithDetails.baseTermSharedPointer));
    TermRaiseToANumber firstTermRaiseToANumber(createTermRaiseToANumberFromTerm(firstTerm));
    TermRaiseToANumber secondTermRaiseToANumber(createTermRaiseToANumberFromTerm(secondTerm));

    AlbaNumber gcfOfExponents = getGreatestCommonFactorForAlbaNumber(
                firstTermRaiseToANumber.getExponent(),
                secondTermRaiseToANumber.getExponent());
    if(gcfOfExponents.isFractionType())
    {
        AlbaNumber::FractionData exponentFraction(gcfOfExponents.getFractionData());
        if(isDivisible(exponentFraction.denominator, 2))
        {
            result = getMultiplierToRationalizeForExpressionWhenExponentIsDivisibleByTwo(
                        firstTermWithDetails,
                        secondTermWithDetails);
        }
        else if(isDivisible(exponentFraction.denominator, 3))
        {
            result = getMultiplierToRationalizeForExpressionWhenExponentIsDivisibleByThree(
                        firstTermWithDetails,
                        secondTermWithDetails);
        }
    }
    return result;
}

Expression RationalizeTermOverTerm::getMultiplierToRationalizeForExpressionWhenExponentIsDivisibleByTwo(
        TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails) const
{
    TermWithDetails newSecond(secondTermWithDetails);
    newSecond.association = secondTermWithDetails.hasPositiveAssociation() ?
                TermAssociationType::Negative : TermAssociationType::Positive;
    TermsWithDetails newTermsWithDetails{firstTermWithDetails, newSecond};
    Expression result;
    result.putTermsWithDetails(newTermsWithDetails);
    result.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    return result;
}

Expression RationalizeTermOverTerm::getMultiplierToRationalizeForExpressionWhenExponentIsDivisibleByThree(
        TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails) const
{
    Term const& firstTerm(getTermConstReferenceFromSharedPointer(firstTermWithDetails.baseTermSharedPointer));
    Term const& secondTerm(getTermConstReferenceFromSharedPointer(secondTermWithDetails.baseTermSharedPointer));
    Term newFirstTerm(createExpressionIfPossible({firstTerm, Term("^"), Term(2)}));
    Term newSecondTerm(createExpressionIfPossible({firstTerm, Term("*"), secondTerm}));
    Term newThirdTerm(createExpressionIfPossible({secondTerm, Term("^"), Term(2)}));

    TermAssociationType newSecondAssociationType =
            secondTermWithDetails.hasPositiveAssociation() ?
                TermAssociationType::Negative :
                TermAssociationType::Positive;

    TermWithDetails newFirst(newFirstTerm, TermAssociationType::Positive);
    TermWithDetails newSecond(newSecondTerm, newSecondAssociationType);
    TermWithDetails newThird(newThirdTerm, TermAssociationType::Positive);

    TermsWithDetails newTermsWithDetails{newFirst, newSecond, newThird};
    Expression result;
    result.putTermsWithDetails(newTermsWithDetails);
    result.setCommonOperatorLevel(OperatorLevel::AdditionAndSubtraction);
    return result;
}

}

}
