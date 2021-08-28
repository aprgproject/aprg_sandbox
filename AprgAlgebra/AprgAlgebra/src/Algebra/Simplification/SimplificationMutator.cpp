#include "SimplificationMutator.hpp"

#include <Algebra/Term/Utilities/ConvertHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

SimplificationMutator::SimplificationMutator()
{}

void SimplificationMutator::putSimplification(
        SimplificationOfExpression const& simplification)
{
    m_simplificationOfExpressionOptional.setValue(simplification);
}

void SimplificationMutator::mutateEquation(Equation & equation) const
{
    BaseMutator::mutateEquation(equation);
    equation.simplify();
}

void SimplificationMutator::mutateTerm(Term & term) const
{
    BaseMutator::mutateTerm(term);
    term.simplify();
}

void SimplificationMutator::mutateMonomial(Monomial & monomial) const
{
    monomial.simplify();
}

void SimplificationMutator::mutatePolynomial(Polynomial & polynomial) const
{
    polynomial.simplify();
}

void SimplificationMutator::mutateExpression(Expression & expression) const
{
    if(m_simplificationOfExpressionOptional)
    {
        SimplificationOfExpression simplification(
                    m_simplificationOfExpressionOptional.getConstReference());
        simplification.setExpression(expression);
        simplification.simplify();
        expression = simplification.getExpression();
    }
    else
    {
        expression.simplify();
    }
}

void SimplificationMutator::mutateFunction(Function & functionObject) const
{
    BaseMutator::mutateFunction(functionObject);
    functionObject.simplify();
}

}

}

}
