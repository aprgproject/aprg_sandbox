#include "CreateHelpers.hpp"

#include <Algebra/Constructs/TermsAggregator.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

Monomial createMonomialFromConstant(Constant const& constant)
{
    return Monomial(constant.getNumberConstReference(), {});
}

Monomial createMonomialFromVariable(Variable const& variable)
{
    return Monomial(1, {{variable.getVariableName(), 1}});
}

Monomial createMonomialIfPossible(Term const& term)
{
    Monomial result;
    if(term.isConstant())
    {
        result = createMonomialFromConstant(term.getConstantConstReference());
    }
    else if(term.isVariable())
    {
        result = createMonomialFromVariable(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        result = term.getMonomialConstReference();
    }
    else if(term.isPolynomial())
    {
        Polynomial const polynomial(term.getPolynomialConstReference());
        if(polynomial.isOneMonomial())
        {
            result = polynomial.getFirstMonomial();
        }
    }
    return result;
}

Polynomial createPolynomialFromConstant(Constant const& constant)
{
    return Polynomial{createMonomialFromConstant(constant)};
}

Polynomial createPolynomialFromVariable(Variable const& variable)
{
    return Polynomial{createMonomialFromVariable(variable)};
}

Polynomial createPolynomialFromMonomial(Monomial const& monomial)
{
    return Polynomial{monomial};
}

Polynomial createPolynomialIfPossible(Term const& term)
{
    Polynomial result;
    if(term.isConstant())
    {
        result = createPolynomialFromConstant(term.getConstantConstReference());
    }
    else if(term.isVariable())
    {
        result = createPolynomialFromVariable(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        result = createPolynomialFromMonomial(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = term.getPolynomialConstReference();
    }
    return result;
}

Expression createExpressionInAnExpression(Expression const& expression)
{
    return Expression(Term(expression));
}

Expression createAndWrapExpressionFromATerm(Term const& term)
{
    return Expression(term);
}

Expression createOrCopyExpressionFromATerm(Term const& term)
{
    Expression result;
    if(!term.isEmpty())
    {
        if(term.isExpression())
        {
            result=term.getExpressionConstReference();
        }
        else
        {
            result=Expression(term);
        }
    }
    return result;
}

Expression createExpressionIfPossible(Terms const& terms)
{
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.buildExpressionFromTerms();
    Terms const& builtTerms(aggregator.getTermsConstReference());
    if(builtTerms.size() == 1)
    {
        result = createOrCopyExpressionFromATerm(builtTerms.at(0));
    }
    return result;
}

Expression createSimplifiedExpressionIfPossible(Terms const& terms)
{
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms const& simplifiedTerms(aggregator.getTermsConstReference());
    if(simplifiedTerms.size() == 1)
    {
        result = createOrCopyExpressionFromATerm(simplifiedTerms.at(0));
    }
    return result;
}

Function createFunctionWithEmptyInputExpression(string const& functionName)
{
    Function result;
    if("abs" == functionName)
    {
        result = Functions::abs(Term());
    }
    return result;
}

Function createFunctionInAnFunction(Function const& functionObject)
{
    return Function(
                functionObject.getFunctionName(),
                Term(functionObject),
                functionObject.getFunctionToPerform());
}


}

}
