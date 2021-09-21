#include "FactorizationUtilities.hpp"

#include <Algebra/Factorization/Factorization.hpp>
#include <Algebra/Retrieval/ExponentsRetriever.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

bool areExponentsDivisible(Monomial const& monomial, unsigned int const divisor)
{
    bool result(true);
    for(auto const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference())
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
    if(constant.isIntegerType() && mathHelper::isPerfectNthPowerForAlbaNumber(constant, nthPower))
    {
        result = areExponentsDivisible(monomial, nthPower);
    }
    return result;
}

bool doesNotNeedToBeFactorized(Polynomial const& polynomial)
{
    Monomials const& monomials(polynomial.getMonomialsConstReference());
    bool result(false);
    if(monomials.size() <= 1)
    {
        result = true;
    }
    else if(monomials.size() == 2)
    {
        Monomial const& first(monomials.at(0));
        Monomial const& second(monomials.at(1));
        bool areBothConstantIntegers = first.getConstantConstReference().isIntegerType() && second.getConstantConstReference().isIntegerType();
        bool areEitherConstantOne = first.getConstantConstReference() == 1 || second.getConstantConstReference() == 1;
        ExponentsRetriever retriever;
        retriever.retrieveFromPolynomial(polynomial);
        AlbaNumbersSet const& exponents(retriever.getSavedData());
        bool areAllExponentsOneOrZero = all_of(exponents.cbegin(), exponents.cend(), [](AlbaNumber const& exponent)
        {
            return exponent == 0 || exponent == 1;
        });
        bool areBothDegreeLessThanOne = first.getDegree() <= 1 && second.getDegree() <= 1;
        result = areBothConstantIntegers && areEitherConstantOne && areAllExponentsOneOrZero && areBothDegreeLessThanOne;
    }
    return result;
}

bool doesContainOnlyConstants(Polynomials const& polynomials)
{
    return all_of(polynomials.cbegin(), polynomials.cend(), [](Polynomial const& polynomial)
    {
        return doesThePolynomialHaveOnlyOneConstant(polynomial);
    });
}

bool doesContainConstantsOrOnlyOneNonConstant(Polynomials const& polynomials)
{
    bool result(true);
    unsigned int nonConstantsCount=0;
    for(Polynomial const& polynomial : polynomials)
    {
        if(!doesThePolynomialHaveOnlyOneConstant(polynomial))
        {
            nonConstantsCount++;
            if(nonConstantsCount > 1)
            {
                result = false;
                break;
            }
        }
    }
    return result;
}

void simplifyPolynomialThenEmplaceBackIfNotEmpty(Polynomials & polynomials, Polynomial const& polynomial)
{
    Polynomial simplifiedPolynomial(polynomial);    simplifiedPolynomial.simplify();
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
