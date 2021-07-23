#include "SimplificationOfEquation.hpp"

#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Utilities.hpp>

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
    m_equation = Equation(
                convertExpressionToSimplestTerm(getNewCombinedExpression(m_equation)),
                getNewEquationOperatorString(m_equation.getEquationOperator()),
                Term(Constant(0)));
}

Expression SimplificationOfEquation::getNewCombinedExpression(
        Equation const& equation) const
{
    Expression combinedExpression;
    EquationOperator equationOperator(equation.getEquationOperator());
    if(equationOperator.isAnEqualityVariant() || equationOperator.isAGreaterThanVariant())
    {
        combinedExpression = createExpressionIfPossible(Terms{equation.getLeftHandTerm(), Term("-"), equation.getRightHandTerm()});
    }
    else if(equationOperator.isALessThanVariant())
    {
        combinedExpression = createExpressionIfPossible(Terms{equation.getRightHandTerm(), Term("-"), equation.getLeftHandTerm()});
    }
    SimplificationOfExpression simplificationOfExpression(combinedExpression);
    simplificationOfExpression.setAsShouldSimplifyToACommonDenominator(true);
    simplificationOfExpression.simplify();
    return simplificationOfExpression.getExpression();
}

string SimplificationOfEquation::getNewEquationOperatorString(
        EquationOperator const& equationOperator) const
{
    string result(equationOperator.getOperatorString());
    if(equationOperator.isLessThan())
    {
        result=">";
    }
    else if(equationOperator.isLessThanOrEqual())
    {
        result=">=";
    }
    return result;
}

}

}

}
