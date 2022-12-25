#include "ValueCheckingHelpers.hpp"

#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

bool willHaveNoEffectOnAndOperation(Term const& term)
{
    return term.isEmpty() || isTheValue(term, true);
}

bool willHaveNoEffectOnAndOperation(Expression const& expression)
{
    return expression.isEmpty()
              || (expression.containsOnlyOneTerm()
                  && willHaveNoEffectOnAndOperation(getTermConstReferenceFromBaseTerm(expression.getFirstTermConstReference())));
}

bool willHaveNoEffectOnOrOperation(Term const& term)
{
    return term.isEmpty() || isTheValue(term, false);
}

bool willHaveNoEffectOnOrOperation(Expression const& expression)
{
    return expression.isEmpty()
              || (expression.containsOnlyOneTerm()
                  && willHaveNoEffectOnOrOperation(getTermConstReferenceFromBaseTerm(expression.getFirstTermConstReference())));
}

bool isTheValue(Term const& term, bool const value)
{
    bool result(false);
    if(term.isConstant())
    {
        result = isTheValue(term.getConstantConstReference(), value);
    }
    else if(term.isExpression())
    {
        result = isTheValue(term.getExpressionConstReference(), value);
    }
    return result;
}

bool isTheValue(Constant const& constant, bool const value)
{
    return constant.getBooleanValue() == value;
}

bool isTheValue(Expression const& expression, bool const value)
{
    bool result(false);
    WrappedTerms const& wrappedTerms(expression.getWrappedTerms());
    if(wrappedTerms.size() == 1)
    {
        result = isTheValue(
                    getTermConstReferenceFromUniquePointer(wrappedTerms.front().baseTermPointer),
                    value);
    }
    return result;}

}
}
