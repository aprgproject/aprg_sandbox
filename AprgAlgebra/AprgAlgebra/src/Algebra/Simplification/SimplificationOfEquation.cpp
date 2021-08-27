#include "SimplificationOfEquation.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Retrieval/FirstCoefficientRetriever.hpp>
#include <Algebra/Retrieval/NumberOfTermsRetriever.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>

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

bool SimplificationOfEquation::isNegatedTermSimpler(
        Term const& term,
        Term const& negatedTerm) const
{
    FirstCoefficientRetriever firstCoefficientRetrieverForTerm;
    NumberOfTermsRetriever numberOfTermsRetrieverForTerm;
    NumberOfTermsRetriever numberOfTermsRetrieverForNegatedTerm;
    firstCoefficientRetrieverForTerm.retrieveFromTerm(term);
    numberOfTermsRetrieverForTerm.retrieveFromTerm(term);
    numberOfTermsRetrieverForNegatedTerm.retrieveFromTerm(negatedTerm);

    return numberOfTermsRetrieverForTerm.getSavedData() > numberOfTermsRetrieverForNegatedTerm.getSavedData()
            || firstCoefficientRetrieverForTerm.getSavedData() < 0;
}

Expression SimplificationOfEquation::getNewCombinedExpression(
        Equation const& equation) const
{
    Expression combinedExpression;
    combinedExpression = createExpressionIfPossible(Terms{equation.getLeftHandTerm(), Term("-"), equation.getRightHandTerm()});
    SimplificationOfExpression simplificationOfExpression(combinedExpression);
    simplificationOfExpression.setAsShouldSimplifyToACommonDenominator(true);
    simplificationOfExpression.simplify();
    return simplificationOfExpression.getExpression();
}

}

}

}
