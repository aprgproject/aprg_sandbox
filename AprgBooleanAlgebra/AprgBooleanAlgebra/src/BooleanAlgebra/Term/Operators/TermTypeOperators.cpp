#include "TermTypeOperators.hpp"

#include <BooleanAlgebra/Operations/PerformOperations.hpp>
#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace booleanAlgebra
{

namespace
{

Term createTermWithAnExpressionWithTwoTermsUsingAndOperation(Term const& term1, Term const& term2)
{
    Expression newExpression(term1);
    newExpression.putTermWithAndOperationIfNeeded(term2);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionAndATermUsingAndOperation(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithAndOperationIfNeeded(term);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithATermAndAnExpressionUsingAndOperation(Term const& term, Expression const& expression)
{
    Expression newExpression(createOrCopyExpressionFromATerm(term));
    newExpression.putTermWithAndOperationIfNeeded(Term(expression));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionWithTwoTermsUsingOrOperation(Term const& term1, Term const& term2)
{
    Expression newExpression(term1);
    newExpression.putTermWithOrOperationIfNeeded(term2);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionAndATermUsingOrOperation(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithOrOperationIfNeeded(term);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithATermAndAnExpressionUsingOrOperation(Term const& term, Expression const& expression)
{
    Expression newExpression(createOrCopyExpressionFromATerm(term));
    newExpression.putTermWithOrOperationIfNeeded(Term(expression));
    return convertExpressionToSimplestTerm(newExpression);
}

}


//And: a & b

Term operator&(Constant const& constant1, Constant const& constant2)
{
    return constant1.getBooleanValue() && constant2.getBooleanValue();
}

Term operator&(Constant const& constant, VariableTerm const& variableTerm)
{
    return createTermWithAnExpressionWithTwoTermsUsingAndOperation(constant, variableTerm);
}

Term operator&(Constant const& constant, Expression const& expression)
{
    return createTermWithATermAndAnExpressionUsingAndOperation(constant, expression);
}

Term operator&(Constant const& constant, Term const& term)
{
    return performAnd(constant, term);
}

Term operator&(VariableTerm const& variableTerm, Constant const& constant)
{
    return createTermWithAnExpressionWithTwoTermsUsingAndOperation(variableTerm, constant);
}

Term operator&(VariableTerm const& variableTerm1, VariableTerm const& variableTerm2)
{
    return createTermWithAnExpressionWithTwoTermsUsingAndOperation(variableTerm1, variableTerm2);
}

Term operator&(VariableTerm const& variableTerm, Expression const& expression)
{
    return createTermWithATermAndAnExpressionUsingAndOperation(variableTerm, expression);
}

Term operator&(VariableTerm const& variableTerm, Term const& term)
{
    return performAnd(variableTerm, term);
}

Term operator&(Expression const& expression, Constant const& constant)
{
    return createTermWithAnExpressionAndATermUsingAndOperation(expression, constant);
}

Term operator&(Expression const& expression, VariableTerm const& variableTerm)
{
    return createTermWithAnExpressionAndATermUsingAndOperation(expression, variableTerm);
}

Term operator&(Expression const& expression1, Expression const& expression2)
{
    return createTermWithAnExpressionAndATermUsingAndOperation(expression1, expression2);
}

Term operator&(Expression const& expression, Term const& term)
{
    return performAnd(expression, term);
}

Term operator&(Term const& term, Constant const& constant)
{
    return performAnd(term, constant);
}

Term operator&(Term const& term, VariableTerm const& variableTerm)
{
    return performAnd(term, variableTerm);
}

Term operator&(Term const& term, Expression const& expression)
{
    return performAnd(term, expression);
}


//Or: a | b

Term operator|(Constant const& constant1, Constant const& constant2)
{
    return constant1.getBooleanValue() || constant2.getBooleanValue();
}

Term operator|(Constant const& constant, VariableTerm const& variableTerm)
{
    return createTermWithAnExpressionWithTwoTermsUsingOrOperation(constant, variableTerm);
}

Term operator|(Constant const& constant, Expression const& expression)
{
    return createTermWithATermAndAnExpressionUsingOrOperation(constant, expression);
}

Term operator|(Constant const& constant, Term const& term)
{
    return performOr(constant, term);
}

Term operator|(VariableTerm const& variableTerm, Constant const& constant)
{
    return createTermWithAnExpressionWithTwoTermsUsingOrOperation(variableTerm, constant);
}

Term operator|(VariableTerm const& variableTerm1, VariableTerm const& variableTerm2)
{
    return createTermWithAnExpressionWithTwoTermsUsingOrOperation(variableTerm1, variableTerm2);
}

Term operator|(VariableTerm const& variableTerm, Expression const& expression)
{
    return createTermWithATermAndAnExpressionUsingOrOperation(variableTerm, expression);
}

Term operator|(VariableTerm const& variableTerm, Term const& term)
{
    return performOr(variableTerm, term);
}

Term operator|(Expression const& expression, Constant const& constant)
{
    return createTermWithAnExpressionAndATermUsingOrOperation(expression, constant);
}

Term operator|(Expression const& expression, VariableTerm const& variableTerm)
{
    return createTermWithAnExpressionAndATermUsingOrOperation(expression, variableTerm);
}

Term operator|(Expression const& expression1, Expression const& expression2)
{
    return createTermWithAnExpressionAndATermUsingOrOperation(expression1, expression2);
}

Term operator|(Expression const& expression, Term const& term)
{
    return performOr(expression, term);
}

Term operator|(Term const& term, Constant const& constant)
{
    return performOr(term, constant);
}

Term operator|(Term const& term, VariableTerm const& variableTerm)
{
    return performOr(term, variableTerm);
}

Term operator|(Term const& term, Expression const& expression)
{
    return performOr(term, expression);
}

}

}
