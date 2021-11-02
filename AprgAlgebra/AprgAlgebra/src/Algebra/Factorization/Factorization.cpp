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

}

}

}
