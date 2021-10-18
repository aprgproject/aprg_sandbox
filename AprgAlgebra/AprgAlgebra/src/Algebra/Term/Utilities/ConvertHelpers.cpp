#include "ConvertHelpers.hpp"

#include <Algebra/Functions/SimplifyingFunctionToExpression.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

namespace alba
{

namespace algebra
{

bool canBeConvertedToConstant(Polynomial const& polynomial)
{
    return polynomial.isEmpty() || (polynomial.isOneMonomial() && polynomial.getFirstMonomial().isConstantOnly());
}

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
    return convertMonomialToSimplestTerm(newMonomial);
}

Term simplifyAndConvertPolynomialToSimplestTerm(Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.simplify();
    return convertPolynomialToSimplestTerm(newPolynomial);
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

Term convertMonomialToSimplestTerm(Monomial const& monomial)
{
    Term newTerm(monomial);
    if(isTheValue(monomial, 0))
    {
        newTerm = Term(Constant(0));
    }
    else if(monomial.isConstantOnly())
    {
        newTerm = Term(monomial.getConstantConstReference());
    }
    else if(monomial.isVariableOnly())
    {
        newTerm = Term(monomial.getFirstVariableName());
    }
    return newTerm;
}

Term convertPolynomialToSimplestTerm(Polynomial const& polynomial)
{
    Term newTerm(polynomial);
    if(isTheValue(polynomial, 0))
    {
        newTerm = Term(Constant(0));
    }
    else if(polynomial.isOneMonomial())
    {
        newTerm = simplifyAndConvertMonomialToSimplestTerm(polynomial.getFirstMonomial());
    }
    return newTerm;
}

Term convertExpressionToSimplestTerm(Expression const& expression)
{
    Term newTerm(expression);
    if(expression.isEmpty())
    {
        newTerm = Term();
    }
    else if(expression.containsOnlyOnePositivelyAssociatedTerm())
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
    if(functionAsParameter.isInputAConstant())
    {
        newTerm = Term(functionAsParameter.performFunctionAndReturnResultIfPossible());
    }
    return newTerm;
}

}

}
