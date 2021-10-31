#include "SimplificationOfEquation.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>
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
    Term leftHandSide(simplifyAndConvertExpressionToSimplestTerm(getNewCombinedTerm(m_equation)));
    string equationOperatorString(m_equation.getEquationOperator().getOperatorString());

    removeExponentIfNeeded(leftHandSide);
    completeExpressionWithFractionalExponentsIfNeeded(leftHandSide);
    simplifyLeftHandTerm(leftHandSide);
    negateTermIfNeeded(leftHandSide, equationOperatorString);

    m_equation = Equation(leftHandSide, equationOperatorString, Term(Constant(0)));
}

Term SimplificationOfEquation::getNewCombinedTerm(
        Equation const& equation) const
{
    Term const& leftHandTerm(equation.getLeftHandTerm());
    Term const& rightHandTerm(equation.getRightHandTerm());

    Term combinedTerm;
    if(isTheValue(leftHandTerm, AlbaNumber(0)))
    {
        combinedTerm = rightHandTerm;
    }
    else if(isTheValue(rightHandTerm, AlbaNumber(0)))
    {
        combinedTerm = leftHandTerm;
    }
    else
    {
        combinedTerm = Term(createExpressionIfPossible(Terms{leftHandTerm, Term("-"), rightHandTerm}));
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

void SimplificationOfEquation::simplifyLeftHandTerm(
        Term & term)
{
    simplifyTermToACommonDenominator(term);
}

bool SimplificationOfEquation::areTheSignsOfTwoTermsDifferent(        TermWithDetails const& firstTerm,
        TermWithDetails const& secondTerm)
{
    return firstTerm.hasNegativeAssociation() ^ secondTerm.hasNegativeAssociation();}

}

}

}
