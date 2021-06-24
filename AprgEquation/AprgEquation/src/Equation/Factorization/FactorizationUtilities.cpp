#include "FactorizationUtilities.hpp"

#include <Equation/Factorization/Factorization.hpp>
#include <Equation/Utilities.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorizePolynomials(Polynomials const& polynomials)
{
    Polynomials result;
    for(Polynomial const& polynomialToFactorize : polynomials)
    {
        Polynomials factorizedPolynomials(factorize(polynomialToFactorize));
        if(factorizedPolynomials.size() == 1)
        {
            simplifyPolynomialThenEmplaceBack(result, polynomialToFactorize);
        }
        else
        {
            copy(factorizedPolynomials.cbegin(), factorizedPolynomials.cend(), back_inserter(result));
        }
    }
    return result;
}

Polynomials returnPolynomialsOrSinglePolynomialIfEmpty(
        Polynomials const& polynomials,
        Polynomial const& polynomial)
{
    Polynomials result(polynomials);
    if(result.empty())
    {
        simplifyPolynomialThenEmplaceBack(result, polynomial);
    }
    return result;
}

Polynomials factorizeCommonMonomial(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeCommonMonomialIfPossible(polynomial),
                polynomial);
}

Polynomials factorizeCommonMonomialIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(!polynomial.isOneMonomial())
    {
        Monomial gcfMonomial(getGcfMonomialInMonomials(polynomial.getMonomialsConstReference()));
        if(!gcfMonomial.isOne())
        {
            Polynomial reducedPolynomial(polynomial);
            reducedPolynomial.divideMonomial(gcfMonomial);
            reducedPolynomial.simplify();
            simplifyPolynomialThenEmplaceBack(result, createPolynomialFromMonomial(gcfMonomial));
            simplifyPolynomialThenEmplaceBack(result, reducedPolynomial);
        }
    }
    return result;
}

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

void simplifyPolynomialThenEmplaceBack(Polynomials & polynomials, Polynomial const& polynomial)
{
    Polynomial simplifiedPolynomial(polynomial);
    simplifiedPolynomial.simplify();
    polynomials.emplace_back(simplifiedPolynomial);
}

}

}

}
