#include "FactorizationUsingPatterns.hpp"

#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba {

namespace algebra {

namespace Factorization {

Polynomials factorizeUsingPatterns(Polynomial const& polynomial) {
    Polynomials result;
    factorizeUsingPatternsIfPossible(result, polynomial);
    simplifyAndEmplaceBackPolynomialIfListIsEmpty(result, polynomial);
    return result;
}

void factorizeUsingPatternsIfPossible(Polynomials& result, Polynomial const& polynomial) {
    factorizeDifferenceOfSquaresIfPossible(result, polynomial);
    if (result.empty()) {
        factorizeDifferenceOfCubesIfPossible(result, polynomial);
        if (result.empty()) {
            factorizeSumOfCubesIfPossible(result, polynomial);
        }
    }
}

void factorizeDifferenceOfSquaresIfPossible(Polynomials& result, Polynomial const& polynomial) {
    if (isDifferenceOfSquares(polynomial)) {
        addFactorsOfDifferenceOfSquares(result, polynomial);
    }
}

void factorizeDifferenceOfCubesIfPossible(Polynomials& result, Polynomial const& polynomial) {
    if (isDifferenceOfCubes(polynomial)) {
        addFactorsOfDifferenceOfCubes(result, polynomial);
    }
}

void factorizeSumOfCubesIfPossible(Polynomials& result, Polynomial const& polynomial) {
    if (isSumOfCubes(polynomial)) {
        addFactorsOfSumOfCubes(result, polynomial);
    }
}

void addFactorsOfDifferenceOfSquares(Polynomials& result, Polynomial const& polynomial) {
    Monomials monomials(polynomial.getMonomials());
    Monomial firstMonomial(monomials[0]);
    Monomial secondMonomial(monomials[1]);
    if (firstMonomial.getCoefficient() > 0 && secondMonomial.getCoefficient() < 0) {
        secondMonomial.multiplyNumber(-1);
    } else if (firstMonomial.getCoefficient() < 0 && secondMonomial.getCoefficient() > 0) {
        firstMonomial.multiplyNumber(-1);
        simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, createPolynomialFromNumber(-1));
    }    firstMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, 2));
    secondMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, 2));
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, Polynomial{firstMonomial, secondMonomial});
    secondMonomial.multiplyNumber(-1);    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, Polynomial{firstMonomial, secondMonomial});
}

void addFactorsOfDifferenceOfCubes(Polynomials& result, Polynomial const& polynomial) {
    Monomials monomials(polynomial.getMonomials());
    Monomial firstMonomial(monomials[0]);
    Monomial secondMonomial(monomials[1]);
    if (firstMonomial.getCoefficient() > 0 && secondMonomial.getCoefficient() < 0) {
        secondMonomial.multiplyNumber(-1);
    } else if (firstMonomial.getCoefficient() < 0 && secondMonomial.getCoefficient() > 0) {
        firstMonomial.multiplyNumber(-1);
        simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, createPolynomialFromNumber(-1));
    }    firstMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, 3));
    secondMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, 3));
    Monomial firstMonomialSquared(firstMonomial);
    Monomial secondMonomialSquared(secondMonomial);    Monomial productOfFirstAndSecond(firstMonomial);
    firstMonomialSquared.raiseToPowerNumber(2);
    secondMonomialSquared.raiseToPowerNumber(2);
    productOfFirstAndSecond.multiplyMonomial(secondMonomial);
    secondMonomial.multiplyNumber(-1);
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, Polynomial{firstMonomial, secondMonomial});
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(
        result, Polynomial{firstMonomialSquared, productOfFirstAndSecond, secondMonomialSquared});
}

void addFactorsOfSumOfCubes(Polynomials& result, Polynomial const& polynomial) {
    Monomials monomials(polynomial.getMonomials());
    Monomial firstMonomial(monomials[0]);
    Monomial secondMonomial(monomials[1]);
    if (firstMonomial.getCoefficient() < 0 && secondMonomial.getCoefficient() < 0) {
        firstMonomial.multiplyNumber(-1);
        secondMonomial.multiplyNumber(-1);
        simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, createPolynomialFromNumber(-1));    }
    firstMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, 3));
    secondMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, 3));
    Monomial firstMonomialSquared(firstMonomial);    Monomial secondMonomialSquared(secondMonomial);
    Monomial productOfFirstAndSecond(firstMonomial);
    firstMonomialSquared.raiseToPowerNumber(2);
    secondMonomialSquared.raiseToPowerNumber(2);
    productOfFirstAndSecond.multiplyMonomial(secondMonomial);
    productOfFirstAndSecond.multiplyNumber(-1);
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, Polynomial{firstMonomial, secondMonomial});
    simplifyThenEmplaceBackIfPolynomialIsNotEmpty(
        result, Polynomial{firstMonomialSquared, productOfFirstAndSecond, secondMonomialSquared});
}

bool isDifferenceOfSquares(Polynomial const& polynomial) {
    bool result(false);
    Monomials monomials(polynomial.getMonomials());
    if (monomials.size() == 2) {
        Monomial firstMonomial(monomials[0]);
        Monomial secondMonomial(monomials[1]);
        if (firstMonomial.getCoefficient() > 0 && secondMonomial.getCoefficient() < 0) {
            secondMonomial.multiplyNumber(-1);
            result = isPerfectSquare(firstMonomial) && isPerfectSquare(secondMonomial);
        } else if (firstMonomial.getCoefficient() < 0 && secondMonomial.getCoefficient() > 0) {
            firstMonomial.multiplyNumber(-1);
            result = isPerfectSquare(firstMonomial) && isPerfectSquare(secondMonomial);
        }    }
    return result;
}

bool isDifferenceOfCubes(Polynomial const& polynomial) {
    bool result(false);
    Monomials monomials(polynomial.getMonomials());
    if (monomials.size() == 2) {
        Monomial firstMonomial(monomials[0]);
        Monomial secondMonomial(monomials[1]);
        if (firstMonomial.getCoefficient() > 0 && secondMonomial.getCoefficient() < 0) {
            secondMonomial.multiplyNumber(-1);
            result = isPerfectCube(firstMonomial) && isPerfectCube(secondMonomial);
        } else if (firstMonomial.getCoefficient() < 0 && secondMonomial.getCoefficient() > 0) {
            firstMonomial.multiplyNumber(-1);
            result = isPerfectCube(firstMonomial) && isPerfectCube(secondMonomial);
        }    }
    return result;
}

bool isSumOfCubes(Polynomial const& polynomial) {
    bool result(false);
    Monomials monomials(polynomial.getMonomials());
    if (monomials.size() == 2) {
        Monomial firstMonomial(monomials[0]);
        Monomial secondMonomial(monomials[1]);
        if (firstMonomial.getCoefficient() > 0 && secondMonomial.getCoefficient() > 0) {
            result = isPerfectCube(firstMonomial) && isPerfectCube(secondMonomial);
        } else if (firstMonomial.getCoefficient() < 0 && secondMonomial.getCoefficient() < 0) {
            firstMonomial.multiplyNumber(-1);
            secondMonomial.multiplyNumber(-1);
            result = isPerfectCube(firstMonomial) && isPerfectCube(secondMonomial);        }
    }
    return result;
}
}  // namespace Factorization

}  // namespace algebra

}  // namespace alba
