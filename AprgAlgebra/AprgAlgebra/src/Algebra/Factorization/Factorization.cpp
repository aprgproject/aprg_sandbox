#include "Factorization.hpp"

#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>

using namespace std;

namespace alba
{

namespace algebra
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


}

}

}
