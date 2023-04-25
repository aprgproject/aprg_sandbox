#include "FactorizationUtilities.hpp"

#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Retrieval/ExponentsRetriever.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace algebra {

namespace Factorization {

bool areExponentsDivisible(Monomial const& monomial, unsigned int const divisor) {
    bool result(true);
    for (auto const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference()) {
        if (!variableExponentPair.second.isIntegerType() ||
            !isDivisible<long long int>(getAbsoluteValue(variableExponentPair.second.getInteger()), divisor)) {
            result = false;
            break;
        }
    }
    return result;
}

bool isPerfectSquare(Monomial const& monomial) { return isPerfectNthPower(monomial, 2); }

bool isPerfectCube(Monomial const& monomial) { return isPerfectNthPower(monomial, 3); }

bool isPerfectNthPower(Monomial const& monomial, unsigned int const nthPower) {
    AlbaNumber constant(monomial.getConstantConstReference());
    bool result(false);
    if (constant.isIntegerType() && mathHelper::isPerfectNthPower(constant, nthPower)) {
        result = areExponentsDivisible(monomial, nthPower);
    }
    return result;
}

bool doesNotNeedToBeFactorized(Polynomial const& polynomial) {
    Monomials const& monomials(polynomial.getMonomialsConstReference());
    bool result(false);
    if (hasNonRealFiniteNumbers(polynomial)) {
        result = true;
    } else if (monomials.size() <= 1) {
        result = true;
    } else if (monomials.size() == 2) {
        Monomial const& first(monomials.at(0));
        Monomial const& second(monomials.at(1));
        bool areBothConstantIntegers =
            first.getConstantConstReference().isIntegerType() && second.getConstantConstReference().isIntegerType();
        bool areEitherConstantOne = first.getConstantConstReference() == 1 || second.getConstantConstReference() == 1;
        ExponentsRetriever retriever;
        retriever.retrieveFromPolynomial(polynomial);
        AlbaNumbersSet const& exponents(retriever.getSavedData());
        bool areAllExponentsOneOrZero = all_of(exponents.cbegin(), exponents.cend(), [](AlbaNumber const& exponent) {
            return exponent == 0 || exponent == 1;
        });
        bool areBothDegreeLessThanOne = getDegree(first) <= 1 && getDegree(second) <= 1;
        result =
            areBothConstantIntegers && areEitherConstantOne && areAllExponentsOneOrZero && areBothDegreeLessThanOne;
    }
    return result;
}

bool doesContainOnlyConstants(Polynomials const& polynomials) {
    return all_of(polynomials.cbegin(), polynomials.cend(), [](Polynomial const& polynomial) {
        return doesThePolynomialHaveOnlyOneConstant(polynomial);
    });
}

bool IsEmptyOrContainConstantsOrOneNonConstant(Polynomials const& polynomials) {
    bool result(true);
    unsigned int nonConstantsCount = 0;
    for (Polynomial const& polynomial : polynomials) {
        if (!doesThePolynomialHaveOnlyOneConstant(polynomial)) {
            nonConstantsCount++;
            if (nonConstantsCount > 1) {
                result = false;
                break;
            }
        }
    }
    return result;
}

void simplifyThenEmplaceBackIfPolynomialIsNotEmpty(Polynomials& polynomials, Polynomial const& polynomial) {
    Polynomial simplifiedPolynomial(polynomial);
    simplifiedPolynomial.simplify();
    emplaceBackIfPolynomialIsNotEmpty(polynomials, simplifiedPolynomial);
}

void emplaceBackIfPolynomialIsNotEmpty(Polynomials& polynomials, Polynomial const& polynomial) {
    if (!polynomial.isEmpty()) {
        polynomials.emplace_back(polynomial);
    }
}

void simplifyAndEmplaceBackPolynomialIfListIsEmpty(Polynomials& existingPolynomials, Polynomial const& polynomial) {
    if (existingPolynomials.empty()) {
        simplifyThenEmplaceBackIfPolynomialIsNotEmpty(existingPolynomials, polynomial);
    }
}

}  // namespace Factorization

}  // namespace algebra

}  // namespace alba
