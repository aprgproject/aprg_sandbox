#include "SimplificationOfEquation.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::algebra::Factorization;
using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

SimplificationOfEquation::SimplificationOfEquation(
        Equation const& equation)
    : m_equation(equation)
{}

Equation SimplificationOfEquation::getEquation() const
{
    return m_equation;
}

void SimplificationOfEquation::simplify()
{
    Term leftHandSide(m_equation.getLeftHandTerm());
    Term rightHandSide(m_equation.getRightHandTerm());
    simplifyLeftHandSideAndRightHandSide(leftHandSide, rightHandSide);

    Term newLeftHandSide(simplifyAndConvertExpressionToSimplestTerm(getNewCombinedTerm(leftHandSide, rightHandSide)));
    string equationOperatorString(m_equation.getEquationOperator().getOperatorString());

    removeExponentIfNeeded(newLeftHandSide);
    completeExpressionWithFractionalExponentsIfNeeded(newLeftHandSide);
    removeCommonConstant(newLeftHandSide);
    simplifyLeftHandSide(newLeftHandSide);
    negateTermIfNeeded(newLeftHandSide, equationOperatorString);

    m_equation = Equation(newLeftHandSide, equationOperatorString, 0);
}

void SimplificationOfEquation::simplifyLeftHandSideAndRightHandSide(
        Term & leftHandSide,
        Term & rightHandSide)
{
    raiseLeftHandSideAndRightHandSideToPowerIfLogarithmic(leftHandSide, rightHandSide);
}

void SimplificationOfEquation::raiseLeftHandSideAndRightHandSideToPowerIfLogarithmic(
        Term & leftHandSide,
        Term & rightHandSide)
{
    if(rightHandSide.isFunction() && isLogarithmicFunction(rightHandSide.getFunctionConstReference()))
    {
        Function const& functionObject(rightHandSide.getFunctionConstReference());
        if("log" == functionObject.getFunctionName())
        {
            leftHandSide = Term(createExpressionIfPossible({10, "^", leftHandSide}));
        }
        else if("ln" == functionObject.getFunctionName())
        {
            leftHandSide = Term(createExpressionIfPossible({getEAsTerm(), "^", leftHandSide}));
        }
        rightHandSide = getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference());
    }
}

Term SimplificationOfEquation::getNewCombinedTerm(
        Term const& leftHandSide,
        Term const& rightHandSide) const
{
    Term combinedTerm;
    if(isTheValue(leftHandSide, AlbaNumber(0)))
    {
        combinedTerm = rightHandSide;
    }
    else if(isTheValue(rightHandSide, AlbaNumber(0)))
    {
        combinedTerm = leftHandSide;
    }
    else
    {
        combinedTerm = Term(createExpressionIfPossible(Terms{leftHandSide, "-", rightHandSide}));
    }
    return combinedTerm;
}

void SimplificationOfEquation::negateTermIfNeeded(
        Term & leftHandSide,
        string & equationOperatorString)
{
    if(isANegativeTerm(leftHandSide))
    {
        leftHandSide = convertPositiveTermIfNegative(leftHandSide);
        equationOperatorString = getReverseEquationOperatorString(equationOperatorString);
    }
}

void SimplificationOfEquation::removeExponentIfNeeded(
        Term & leftHandSide)
{
    if(leftHandSide.isExpression())
    {
        Expression const& expression(leftHandSide.getExpressionConstReference());
        if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
        {
            TermRaiseToTerms termRaiseToTerms(expression.getTermsWithAssociation().getTermsWithDetails());
            leftHandSide = termRaiseToTerms.getBase();
        }
    }
}

void SimplificationOfEquation::completeExpressionWithFractionalExponentsIfNeeded(
        Term & leftHandSide)
{
    leftHandSide.simplify();
    if(leftHandSide.isExpression())
    {
        Expression const& expression(leftHandSide.getExpressionConstReference());
        if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
        {
            TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
            if(termsWithDetails.size() == 2
                    && areTheSignsOfTwoTermsDifferent(termsWithDetails.at(0), termsWithDetails.at(1)))
            {
                Term const& firstTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(0).baseTermSharedPointer));
                Term const& secondTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.at(1).baseTermSharedPointer));
                TermRaiseToANumber termRaiseToANumber1(createTermRaiseToANumberFromTerm(firstTerm));
                TermRaiseToANumber termRaiseToANumber2(createTermRaiseToANumberFromTerm(secondTerm));
                AlbaNumber gcfOfExponents = getGreatestCommonFactor(termRaiseToANumber1.getExponent(), termRaiseToANumber2.getExponent());
                if(gcfOfExponents.isFractionType())
                {
                    AlbaNumber::FractionData exponentFraction(gcfOfExponents.getFractionData());
                    termRaiseToANumber1.setExponent(termRaiseToANumber1.getExponent() * exponentFraction.denominator);
                    termRaiseToANumber2.setExponent(termRaiseToANumber2.getExponent() * exponentFraction.denominator);
                    leftHandSide = termRaiseToANumber1.getCombinedTerm() - termRaiseToANumber2.getCombinedTerm();
                    leftHandSide.simplify();
                }
            }
        }
    }
}

void SimplificationOfEquation::removeCommonConstant(
        Term & leftHandSide)
{
    if(!isTheValue(leftHandSide, 0) && !isPositiveOrNegativeInfinity(leftHandSide))
    {
        if(canBeConvertedToMonomial(leftHandSide))
        {
            Monomial monomial(createMonomialIfPossible(leftHandSide));
            monomial.setConstant(getSign(monomial.getConstantConstReference()));
            leftHandSide = simplifyAndConvertMonomialToSimplestTerm(monomial);
        }
        else if(leftHandSide.isPolynomial())
        {
            bool isLeftHandSideChanged(false);
            Polynomials factors(factorizeCommonMonomial(leftHandSide.getPolynomialConstReference()));
            for(Polynomial & factor : factors)
            {
                Monomials & monomials(factor.getMonomialsReference());
                if(monomials.size() == 1)
                {
                    Monomial & onlyMonomial(monomials.at(0));
                    onlyMonomial.setConstant(getSign(onlyMonomial.getConstantConstReference()));
                    isLeftHandSideChanged=true;
                }
            }
            if(isLeftHandSideChanged)
            {
                Polynomial combinedPolynomial(createPolynomialFromNumber(1));
                for(Polynomial const& factor : factors)
                {
                    combinedPolynomial.multiplyPolynomial(factor);
                }
                leftHandSide = Term(combinedPolynomial);
            }
        }
        else if(leftHandSide.isExpression())
        {
            bool isLeftHandSideChanged(false);
            Terms factors(factorizeAnExpressionWithConfigurationChanged(leftHandSide.getExpressionConstReference()));
            for(Term & factor : factors)
            {
                if(canBeConvertedToMonomial(factor))
                {
                    Monomial monomialFactor(createMonomialIfPossible(factor));
                    monomialFactor.setConstant(getSign(monomialFactor.getConstantConstReference()));
                    factor = simplifyAndConvertMonomialToSimplestTerm(monomialFactor);
                    isLeftHandSideChanged=true;
                }
            }
            if(isLeftHandSideChanged)
            {
                Term combinedTerm(1);
                for(Term & factor : factors)
                {
                    combinedTerm *= factor;
                }
                leftHandSide = combinedTerm;
            }
        }
    }
}

void SimplificationOfEquation::simplifyLeftHandSide(
        Term & term)
{
    simplifyTermToACommonDenominator(term);
}

bool SimplificationOfEquation::areTheSignsOfTwoTermsDifferent(
        TermWithDetails const& firstTerm,
        TermWithDetails const& secondTerm)
{
    return firstTerm.hasNegativeAssociation() ^ secondTerm.hasNegativeAssociation();
}

}

}

}
