#include "Differentiation.hpp"

#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba
{
namespace algebra
{

Differentiation::Differentiation(
        string const& variableName)
    : m_variableName(variableName)
{}

Term Differentiation::differentiate(Term const& term) const
{
    Term result;
    if(term.isConstant())
    {
        result = differentiate(term.getConstantConstReference());
    }
    else if(term.isVariable())
    {
        result = differentiate(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        result = differentiate(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = differentiate(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = differentiate(term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        result = differentiate(term.getFunctionConstReference());
    }
    return result;
}

Term Differentiation::differentiate(Constant const& ) const
{
    return Term(Constant(0));
}

Term Differentiation::differentiate(Variable const& variable) const
{
    Term result;
    if(variable.getVariableName() == m_variableName)
    {
        result = Term(1);
    }
    else
    {
        result = Term(variable);
    }
    return result;
}

Term Differentiation::differentiate(Monomial const& monomial) const
{
    Term result(differentiateMonomial(monomial));
    result.simplify();
    return result;
}

Term Differentiation::differentiate(Polynomial const& polynomial) const
{
    Term result(differentiatePolynomial(polynomial));
    result.simplify();
    return result;
}

Term Differentiation::differentiate(Expression const& ) const
{
    return Term();
}

Term Differentiation::differentiate(Function const& ) const
{
    return Term();
}

Monomial Differentiation::differentiateMonomial(Monomial const& monomial) const
{
    Monomial result;
    AlbaNumber exponentOfMonomial(monomial.getExponentForVariable(m_variableName));
    if(exponentOfMonomial == 0)
    {
        result = Monomial(0, {});
    }
    else
    {
        Monomial newMonomial(monomial);
        newMonomial.putVariableWithExponent(m_variableName, exponentOfMonomial-1);
        newMonomial.multiplyNumber(exponentOfMonomial);
        result = newMonomial;
    }
    result.simplify();
    return result;
}

Polynomial Differentiation::differentiatePolynomial(Polynomial const& polynomial) const
{
    Polynomial result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result.addMonomial(differentiateMonomial(monomial));
    }
    result.simplify();
    return result;
}

Term Differentiation::differentiateTwoMultipliedTerms(
        Term const& term1,
        Term const& term2) const
{
    Term term1Derivative(differentiate(term1));
    Term term2Derivative(differentiate(term2));
    Expression firstPart(createExpressionIfPossible({term1, Term("*"), term2Derivative}));
    Expression secondPart(createExpressionIfPossible({term2, Term("*"), term1Derivative}));
    Term result(createExpressionIfPossible({firstPart, Term("+"), secondPart}));
    result.simplify();
    return result;
}

Term Differentiation::differentiateTwoDividedTerms(
        Term const& numerator,
        Term const& denominator) const
{
    Term numeratorDerivative(differentiate(numerator));
    Term denominatorDerivative(differentiate(denominator));
    Expression resultNumeratorPart1(createExpressionIfPossible({denominator, Term("*"), numeratorDerivative}));
    Expression resultNumeratorPart2(createExpressionIfPossible({numerator, Term("*"), denominatorDerivative}));
    Expression resultNumerator(createExpressionIfPossible({resultNumeratorPart1, Term("-"), resultNumeratorPart2}));
    Expression resultDenominator(createExpressionIfPossible({denominator, Term("^"), Term(2)}));
    Term result(createExpressionIfPossible({resultNumerator, Term("/"), resultDenominator}));
    result.simplify();
    return result;
}


}

}
