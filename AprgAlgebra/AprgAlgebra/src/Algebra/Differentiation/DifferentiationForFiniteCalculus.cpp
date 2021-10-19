#include "DifferentiationForFiniteCalculus.hpp"

#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba
{
namespace algebra
{

DifferentiationForFiniteCalculus::DifferentiationForFiniteCalculus(
        string const& nameOfVariableToDifferentiate)
    : m_nameOfVariableToDifferentiate(nameOfVariableToDifferentiate)
{}

Term DifferentiationForFiniteCalculus::differentiate(
        Term const& term) const
{
    return differentiateTerm(term);
}

Term DifferentiationForFiniteCalculus::differentiate(
        Constant const& constant) const
{
    return Term(differentiateConstant(constant));
}

Term DifferentiationForFiniteCalculus::differentiate(
        Variable const& variable) const
{
    Term result(differentiateVariable(variable));
    result.simplify();
    return result;
}

Term DifferentiationForFiniteCalculus::differentiate(
        Monomial const& monomial) const
{
    Term result(differentiateMonomial(monomial));
    result.simplify();
    return result;
}

Term DifferentiationForFiniteCalculus::differentiate(
        Polynomial const& polynomial) const
{
    Term result(differentiatePolynomial(polynomial));
    result.simplify();
    return result;
}

Term DifferentiationForFiniteCalculus::differentiate(
        Expression const& expression) const
{
    return differentiateExpression(expression);
}

Term DifferentiationForFiniteCalculus::differentiate(
        Function const& functionObject) const
{
    return differentiateFunction(functionObject);
}

Equation DifferentiationForFiniteCalculus::differentiate(
        Equation const& equation) const
{
    return differentiateEquation(equation);
}

Term DifferentiationForFiniteCalculus::differentiateMultipleTimes(
        Term const& term,
        unsigned int const numberOfTimes) const
{
    Term currentResult(term);
    for(unsigned int i=0; i<numberOfTimes; i++)
    {
        currentResult = differentiate(currentResult);
    }
    return currentResult;
}

Equation DifferentiationForFiniteCalculus::differentiateMultipleTimes(
        Equation const& equation,
        unsigned int const numberOfTimes) const
{
    Equation currentResult(equation);
    for(unsigned int i=0; i<numberOfTimes; i++)
    {
        currentResult = differentiate(currentResult);
    }
    return currentResult;
}

Term DifferentiationForFiniteCalculus::differentiateTerm(
        Term const& term) const
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

AlbaNumber DifferentiationForFiniteCalculus::differentiateConstant(
        Constant const&) const
{
    return 0;
}

Polynomial DifferentiationForFiniteCalculus::differentiateVariable(
        Variable const& variable) const
{
    Polynomial result(createPolynomialFromConstant(0));
    if(isVariableToDifferentiate(variable.getVariableName()))
    {
        result = Polynomial{Monomial(1, {{m_nameOfVariableToDifferentiate, 1}}), Monomial(1, {})};
    }
    return result;
}

Term DifferentiationForFiniteCalculus::differentiateMonomial(
        Monomial const& monomial) const
{
    return Term(getDerivativeDefinitionForFiniteCalculus(Term(monomial), m_nameOfVariableToDifferentiate));
}

Term DifferentiationForFiniteCalculus::differentiatePolynomial(
        Polynomial const& polynomial) const
{
    return Term(getDerivativeDefinitionForFiniteCalculus(Term(polynomial), m_nameOfVariableToDifferentiate));
}

Term DifferentiationForFiniteCalculus::differentiateExpression(
        Expression const& expression) const
{
    return Term(getDerivativeDefinitionForFiniteCalculus(Term(expression), m_nameOfVariableToDifferentiate));
}

Term DifferentiationForFiniteCalculus::differentiateFunction(
        Function const& functionObject) const
{
    return Term(getDerivativeDefinitionForFiniteCalculus(Term(functionObject), m_nameOfVariableToDifferentiate));
}

Equation DifferentiationForFiniteCalculus::differentiateEquation(
        Equation const& equation) const
{
    Equation result(
                differentiate(equation.getLeftHandTerm()),
                equation.getEquationOperator().getOperatorString(),
                differentiate(equation.getRightHandTerm()));
    result.simplify();
    return result;
}

bool DifferentiationForFiniteCalculus::isVariableToDifferentiate(
        string const& variableName) const
{
    return variableName == m_nameOfVariableToDifferentiate;
}


}

}
