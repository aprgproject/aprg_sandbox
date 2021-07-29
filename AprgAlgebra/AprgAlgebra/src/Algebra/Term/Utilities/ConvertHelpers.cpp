#include "ConvertHelpers.hpp"

namespace alba
{

namespace algebra
{

bool canBeConvertedToMonomial(Term const& term)
{
    TermType termType(term.getTermType());
    bool isPolynomialWithOneMonomial(false);
    if(term.isPolynomial())
    {
        isPolynomialWithOneMonomial = term.getPolynomialConstReference().isOneMonomial();
    }
    return TermType::Constant==termType
            || TermType::Variable==termType
            || TermType::Monomial==termType
            || isPolynomialWithOneMonomial;
}

bool canBeConvertedToPolynomial(Term const& term)
{
    TermType termType(term.getTermType());
    return TermType::Constant==termType
            || TermType::Variable==termType
            || TermType::Monomial==termType
            || TermType::Polynomial==termType;
}

Term simplifyAndConvertMonomialToSimplestTerm(Monomial const& monomial)
{
    Monomial newMonomial(monomial);
    newMonomial.simplify();
    Term newTerm(newMonomial);
    if(newMonomial.isZero())
    {
        newTerm = Term(Constant(0));
    }
    else if(newMonomial.isConstantOnly())
    {
        newTerm = Term(newMonomial.getConstantConstReference());
    }
    else if(newMonomial.isVariableOnly())
    {
        newTerm = Term(newMonomial.getFirstVariableName());
    }
    else
    {
        newTerm = Term(newMonomial);
    }
    return newTerm;
}

Term simplifyAndConvertPolynomialToSimplestTerm(Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.simplify();
    Term newTerm;
    if(newPolynomial.isZero())
    {
        newTerm = Term(Constant(0));
    }
    else if(newPolynomial.isOneMonomial())
    {
        newTerm = simplifyAndConvertMonomialToSimplestTerm(newPolynomial.getFirstMonomial());
    }
    else
    {
        newTerm = Term(newPolynomial);
    }
    return newTerm;
}

Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression)
{
    Expression newExpression(expression);
    newExpression.simplify();
    return convertExpressionToSimplestTerm(newExpression);
}

Term simplifyAndConvertFunctionToSimplestTerm(Function const& functionAsParameter)
{
    Function newFunction(functionAsParameter);
    newFunction.simplify();
    return convertFunctionToSimplestTerm(newFunction);
}

Term convertExpressionToSimplestTerm(Expression const& expression)
{
    Term newTerm(expression);
    if(expression.isEmpty())
    {
        newTerm = Term();
    }
    else if(expression.containsOnlyOneTerm())
    {
        Term const& term = dynamic_cast<Term const&>(expression.getFirstTermConstReference());
        newTerm = term;
        newTerm.simplify();
    }
    return newTerm;
}

Term convertFunctionToSimplestTerm(Function const& functionAsParameter)
{
    Term newTerm(functionAsParameter);
    if(functionAsParameter.isInputExpressionAConstant())
    {
        newTerm = Term(functionAsParameter.performFunctionAndReturnResultIfPossible());
    }
    return newTerm;
}

}

}
