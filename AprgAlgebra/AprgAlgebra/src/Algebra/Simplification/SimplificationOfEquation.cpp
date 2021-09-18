#include "SimplificationOfEquation.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

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
    Term leftHandSide(simplifyAndConvertExpressionToSimplestTerm(getNewCombinedExpression(m_equation)));
    string equationOperatorString(m_equation.getEquationOperator().getOperatorString());

    Term leftHandSideNegated(createExpressionIfPossible({leftHandSide, Term("*"), Term(-1)}));
    leftHandSideNegated.simplify();

    if(isNegatedTermSimpler(leftHandSide, leftHandSideNegated))
    {
        leftHandSide = leftHandSideNegated;
        equationOperatorString = getReverseEquationOperatorString(equationOperatorString);
    }

    m_equation = Equation(leftHandSide, equationOperatorString, Term(Constant(0)));
}

Expression SimplificationOfEquation::getNewCombinedExpression(
        Equation const& equation) const
{
    Expression combinedExpression;
    combinedExpression = createExpressionIfPossible(Terms{equation.getLeftHandTerm(), Term("-"), equation.getRightHandTerm()});

    SimplificationOfExpression::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<SimplificationOfExpression::ConfigurationDetails>());
    configurationDetails.shouldSimplifyToACommonDenominator = true;

    SimplificationOfExpression::ScopeObject scopeObject;    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    combinedExpression.simplify();
    return combinedExpression;
}

}

}

}
