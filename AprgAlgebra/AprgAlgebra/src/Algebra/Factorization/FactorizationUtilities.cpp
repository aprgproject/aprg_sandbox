#include "FactorizationUtilities.hpp"

#include <Algebra/Factorization/Factorization.hpp>
#include <Algebra/Utilities.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

bool isPerfectSquare(Monomial const& monomial)
{
    return isPerfectNthPower(monomial, 2);
}

bool isPerfectCube(Monomial const& monomial)
{
    return isPerfectNthPower(monomial, 3);
}

bool isPerfectNthPower(Monomial const& monomial, unsigned int const nthPower)
{
    AlbaNumber constant(monomial.getConstantConstReference());
    bool result(false);
    if(constant.isIntegerType() && mathHelper::isPerfectNthPower(constant, nthPower))
    {
        result = areExponentsDivisible(monomial, nthPower);
    }
    return result;
}

bool areExponentsDivisible(Monomial const& monomial, unsigned int const divisor)
{
    bool result(true);
    for(Monomial::VariableExponentPair const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference())
    {
        if(!variableExponentPair.second.isIntegerType()
                || !isDivisible(getAbsoluteValue(variableExponentPair.second.getInteger()), divisor))
        {
            result=false;
            break;
        }
    }
    return result;
}

void simplifyPolynomialThenEmplaceBackIfNotEmpty(Polynomials & polynomials, Polynomial const& polynomial)
{
    Polynomial simplifiedPolynomial(polynomial);
    simplifiedPolynomial.simplify();
    emplaceBackIfNotEmpty(polynomials, simplifiedPolynomial);
}

void emplaceBackIfNotEmpty(Polynomials & polynomials, Polynomial const& polynomial)
{
    if(!polynomial.isEmpty())
    {
        polynomials.emplace_back(polynomial);
    }
}

Polynomials returnPolynomialsOrSinglePolynomialIfEmpty(
        Polynomials const& polynomials,
        Polynomial const& polynomial)
{
    Polynomials result(polynomials);
    if(result.empty())
    {
        simplifyPolynomialThenEmplaceBackIfNotEmpty(result, polynomial);
    }
    return result;
}

}

}

}
