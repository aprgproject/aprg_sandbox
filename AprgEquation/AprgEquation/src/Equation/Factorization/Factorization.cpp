#include "Factorization.hpp"

#include <Equation/Factorization/FactorizationOfExpressions.hpp>
#include <Equation/Factorization/FactorizationOfPolynomials.hpp>

using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorize(Polynomial const& polynomial)
{
    return factorizeAPolynomial(polynomial);
}

Expression factorize(Expression const& expression)
{
    Expression newExpression(expression);
    factorizeAnExpression(newExpression);
    return newExpression;
}

Function factorize(Function const& functionAsParameter)
{
    Function newFunction(functionAsParameter);
    factorizeAnExpression(newFunction.getInputExpressionReference());
    return newFunction;
}


}

}

}
