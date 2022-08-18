#include "RationalizeTermOverTerm.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

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
    return m_numerator / m_denominator;
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
    Term rationalizedTerm, multiplier;
    retrieveTermsForRationalization(rationalizedTerm, multiplier, termToRationalize);
    while(!multiplier.isEmpty())
    {
        termToRationalize = rationalizedTerm;
        otherTerm = otherTerm * multiplier;
        simplifyForRationalize(termToRationalize);
        simplifyForRationalize(otherTerm);
        rationalizedTerm.clear();
        multiplier.clear();
        retrieveTermsForRationalization(rationalizedTerm, multiplier, termToRationalize);
    }
}

void RationalizeTermOverTerm::simplifyForRationalize(Term & term)
{
    SimplificationOfExpression::ConfigurationDetails rationalizeConfigurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    rationalizeConfigurationDetails.shouldSimplifyToACommonDenominator = true;
    rationalizeConfigurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;
    rationalizeConfigurationDetails.shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(rationalizeConfigurationDetails);
    term.simplify();
}

void RationalizeTermOverTerm::retrieveTermsForRationalization(
        Term & rationalizedTerm,
        Term & multiplier,
        Term const& term) const
{
    if(term.isPolynomial())
    {
        retrieveTermsForRationalizationForPolynomial(rationalizedTerm, multiplier, term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        retrieveTermsForRationalizationForExpression(rationalizedTerm, multiplier, term.getExpressionConstReference());
    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForPolynomial(
        Term & rationalizedTerm,
        Term & multiplier,
        Polynomial const& polynomial) const
{
    Monomials const& monomials(polynomial.getMonomialsConstReference());
    if(monomials.size() == 2)
    {
        Monomial const& firstMonomial(monomials.at(0));
        Monomial const& secondMonomial(monomials.at(1));
        retrieveTermsForRationalizationForPolynomial(rationalizedTerm, multiplier, firstMonomial, secondMonomial);
    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForPolynomial(
        Term & rationalizedTerm,
        Term & multiplier,
        Monomial const& firstMonomial,
        Monomial const& secondMonomial) const
{
    AlbaNumber gcfOfExponents = getGreatestCommonFactor(
                getGcfOfExponentsInMonomial(firstMonomial),
                getGcfOfExponentsInMonomial(secondMonomial));
    if(gcfOfExponents.isFractionType())
    {
        AlbaNumber::FractionData exponentFraction(gcfOfExponents.getFractionData());
        if(isDivisible(exponentFraction.denominator, 2U))
        {
            retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByTwo(rationalizedTerm, multiplier, firstMonomial, secondMonomial);
        }
        else if(isDivisible(exponentFraction.denominator, 3U))
        {
            retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByThree(rationalizedTerm, multiplier, firstMonomial, secondMonomial);
        }    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByTwo(        Term & rationalizedTerm,
        Term & multiplier,
        Monomial const& firstMonomial,
        Monomial const& secondMonomial) const
{
    Monomial newSecondMonomialOfRemainder(secondMonomial);
    newSecondMonomialOfRemainder.multiplyNumber(-1);
    multiplier = Polynomial{firstMonomial, newSecondMonomialOfRemainder};

    Monomial rationalizedFirstMonomial(firstMonomial);
    rationalizedFirstMonomial.raiseToPowerNumber(2);
    Monomial rationalizedSecondMonomial(secondMonomial);
    rationalizedSecondMonomial.raiseToPowerNumber(2);
    rationalizedSecondMonomial.multiplyNumber(-1);
    rationalizedTerm = Polynomial{rationalizedFirstMonomial, rationalizedSecondMonomial};
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForPolynomialWhenExponentIsDivisibleByThree(
        Term & rationalizedTerm,
        Term & multiplier,
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
    multiplier = Polynomial{newFirstMonomial, newSecondMonomial, newThirdMonomial};

    Monomial rationalizedFirstMonomial(firstMonomial);
    rationalizedFirstMonomial.raiseToPowerNumber(3);
    Monomial rationalizedSecondMonomial(secondMonomial);
    rationalizedSecondMonomial.raiseToPowerNumber(3);
    rationalizedTerm = Polynomial{rationalizedFirstMonomial, rationalizedSecondMonomial};
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForExpression(
        Term & rationalizedTerm,
        Term & multiplier,
        Expression const& expression) const
{
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        TermsWithDetails const& termsWithDetails(
                    expression.getTermsWithAssociation().getTermsWithDetails());
        if(termsWithDetails.size() == 2)
        {
            TermWithDetails const& firstTermWithDetails(termsWithDetails.at(0));
            TermWithDetails const& secondTermWithDetails(termsWithDetails.at(1));
            retrieveTermsForRationalizationForExpression(rationalizedTerm, multiplier, firstTermWithDetails, secondTermWithDetails);
        }
    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForExpression(
        Term & rationalizedTerm,
        Term & multiplier,
        TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails) const
{
    Term const& firstTerm(getTermConstReferenceFromSharedPointer(firstTermWithDetails.baseTermSharedPointer));
    Term const& secondTerm(getTermConstReferenceFromSharedPointer(secondTermWithDetails.baseTermSharedPointer));
    TermRaiseToANumber firstTermRaiseToANumber(createTermRaiseToANumberFromTerm(firstTerm));
    TermRaiseToANumber secondTermRaiseToANumber(createTermRaiseToANumberFromTerm(secondTerm));

    AlbaNumber gcfOfExponents = getGreatestCommonFactor(
                firstTermRaiseToANumber.getExponent(),
                secondTermRaiseToANumber.getExponent());
    if(gcfOfExponents.isFractionType())
    {
        AlbaNumber::FractionData exponentFraction(gcfOfExponents.getFractionData());
        if(isDivisible(exponentFraction.denominator, 2U))
        {
            retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByTwo(
                        rationalizedTerm,                        multiplier,
                        firstTermWithDetails,
                        secondTermWithDetails);
        }
        else if(isDivisible(exponentFraction.denominator, 3U))
        {
            retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByThree(
                        rationalizedTerm,                        multiplier,
                        firstTermWithDetails,
                        secondTermWithDetails);
        }    }
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByTwo(
        Term & rationalizedTerm,
        Term & multiplier,
        TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails) const
{
    Term const& firstTerm(getTermConstReferenceFromSharedPointer(firstTermWithDetails.baseTermSharedPointer));
    Term const& secondTerm(getTermConstReferenceFromSharedPointer(secondTermWithDetails.baseTermSharedPointer));

    TermWithDetails secondMultiplierTerm(secondTermWithDetails);
    secondMultiplierTerm.association = secondTermWithDetails.hasPositiveAssociation() ?
                TermAssociationType::Negative : TermAssociationType::Positive;
    TermsWithDetails multiplierTermsWithDetails{firstTermWithDetails, secondMultiplierTerm};
    multiplier = createTermWithAdditionAndSubtractionTermsWithDetails(multiplierTermsWithDetails);

    Term firstRationalizedTerm(firstTerm ^ 2);
    Term secondRationalizedTerm(secondTerm ^ 2);
    TermWithDetails firstRationalizedTermWithDetails(firstRationalizedTerm, TermAssociationType::Positive);
    TermWithDetails secondRationalizedTermTermWithDetails(secondRationalizedTerm, TermAssociationType::Negative);
    TermsWithDetails rationalizedTermsWithDetails{firstRationalizedTermWithDetails, secondRationalizedTermTermWithDetails};
    rationalizedTerm = createTermWithAdditionAndSubtractionTermsWithDetails(rationalizedTermsWithDetails);
}

void RationalizeTermOverTerm::retrieveTermsForRationalizationForExpressionWhenExponentIsDivisibleByThree(
        Term & rationalizedTerm,
        Term & multiplier,
        TermWithDetails const& firstTermWithDetails,
        TermWithDetails const& secondTermWithDetails) const
{
    Term const& firstTerm(getTermConstReferenceFromSharedPointer(firstTermWithDetails.baseTermSharedPointer));
    Term const& secondTerm(getTermConstReferenceFromSharedPointer(secondTermWithDetails.baseTermSharedPointer));

    Term firstMultiplierTerm(firstTerm ^ 2);
    Term secondMultiplierTerm(firstTerm * secondTerm);
    Term thirdMultiplierTerm(secondTerm ^ 2);
    TermAssociationType newSecondAssociationType =
            secondTermWithDetails.hasPositiveAssociation() ?
                TermAssociationType::Negative :
                TermAssociationType::Positive;
    TermWithDetails firstMultiplierTermWithDetails(firstMultiplierTerm, TermAssociationType::Positive);
    TermWithDetails secondMultiplierTermWithDetails(secondMultiplierTerm, newSecondAssociationType);
    TermWithDetails thirdMultiplierTermWithDetails(thirdMultiplierTerm, TermAssociationType::Positive);
    TermsWithDetails multiplierTermsWithDetails{firstMultiplierTermWithDetails, secondMultiplierTermWithDetails, thirdMultiplierTermWithDetails};
    multiplier = createTermWithAdditionAndSubtractionTermsWithDetails(multiplierTermsWithDetails);

    Term firstRationalizedTerm(firstTerm ^ 3);
    Term secondRationalizedTerm(secondTerm ^ 3);
    TermWithDetails firstRationalizedTermWithDetails(firstRationalizedTerm, firstTermWithDetails.association);
    TermWithDetails secondRationalizedTermTermWithDetails(secondRationalizedTerm, secondTermWithDetails.association);
    TermsWithDetails rationalizedTermsWithDetails{firstRationalizedTermWithDetails, secondRationalizedTermTermWithDetails};
    rationalizedTerm = createTermWithAdditionAndSubtractionTermsWithDetails(rationalizedTermsWithDetails);
}

}

}
