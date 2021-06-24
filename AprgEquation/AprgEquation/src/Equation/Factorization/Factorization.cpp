#include "Factorization.hpp"

#include <Equation/Factorization/FactorizationBySplitting.hpp>
#include <Equation/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>
#include <Equation/Factorization/FactorizationUsingPatterns.hpp>
#include <Equation/Factorization/FactorizationUtilities.hpp>

using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

Expression factorize(Expression const& expression)
{
    Expression factorizedExpression(expression);
    factorizedExpression.factorize();
    return factorizedExpression;
}

Polynomials factorize(Polynomial const& polynomial)
{
    Polynomial polynomialToFactorize(polynomial);
    polynomialToFactorize.simplify();
    Polynomials result{polynomialToFactorize};
    if(!polynomialToFactorize.isOneMonomial())
    {
        result = factorizeCommonMonomial(polynomialToFactorize);
        if(result.size() == 1){result = factorizeDifferenceOfSquares(polynomialToFactorize); }
        if(result.size() == 1){result = factorizeDifferenceOfCubes(polynomialToFactorize); }
        if(result.size() == 1){result = factorizeSumOfCubes(polynomialToFactorize); }
        if(result.size() == 1){result = factorizeIncreasingAndDecreasingExponentsForm(polynomialToFactorize); }
        if(result.size() == 1){result = factorizeBySplittingToSmallerPolynomials(polynomialToFactorize); }
        if(result.size() != 1)
        {
            result = factorizePolynomials(result);
        }
    }
    return result;
}

}

}

}
