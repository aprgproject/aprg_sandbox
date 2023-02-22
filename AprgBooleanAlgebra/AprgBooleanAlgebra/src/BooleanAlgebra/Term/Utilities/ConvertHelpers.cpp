#include "ConvertHelpers.hpp"

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression)
{
    Expression newExpression(expression);
    newExpression.simplify();
    return convertExpressionToSimplestTerm(newExpression);
}

Term convertExpressionToSimplestTerm(Expression const& expression)
{
    Term newTerm(expression);
    if(expression.isEmpty())
    {
        newTerm.clear();
    }
    else if(expression.containsOnlyOneTerm())
    {
        Term const& term = static_cast<Term const&>(expression.getFirstTermConstReference());
        newTerm = term;
        newTerm.simplify();
    }
    return newTerm;
}

}

}
