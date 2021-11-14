#include "SimplificationOfEquation.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

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
    simplifyLeftHandSide(newLeftHandSide);
    negateTermIfNeeded(newLeftHandSide, equationOperatorString);

    m_equation = Equation(newLeftHandSide, equationOperatorString, Term(0));
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
            leftHandSide = Term(createExpressionIfPossible({Term(10), Term("^"), leftHandSide}));
        }
        else if("ln" == functionObject.getFunctionName())
        {
            leftHandSide = Term(createExpressionIfPossible({getEAsTerm(), Term("^"), leftHandSide}));
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
        combinedTerm = Term(createExpressionIfPossible(Terms{leftHandSide, Term("-"), rightHandSide}));
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
                AlbaNumber gcfOfExponents = getGreatestCommonFactorForAlbaNumber(termRaiseToANumber1.getExponent(), termRaiseToANumber2.getExponent());
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
