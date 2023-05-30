#include "FactorizationOfIncreasingAndDecreasingExponentForm.hpp"

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Factorization/BrentMethod.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace algebra {

namespace Factorization {

namespace {
constexpr int NUMBER_OF_ITERATIONS_IN_BRENT_METHOD = 1000;
}

Polynomials factorizeIncreasingAndDecreasingExponentsForm(Polynomial const& polynomial) {
    Polynomials result;
    factorizeIncreasingAndDecreasingExponentsFormIfPossible(result, polynomial);
    simplifyAndEmplaceBackPolynomialIfListIsEmpty(result, polynomial);
    return result;
}

void factorizeIncreasingAndDecreasingExponentsFormIfPossible(Polynomials& result, Polynomial const& polynomial) {
    Monomials monomials(polynomial.getMonomialsConstReference());
    if (monomials.size() > 1) {
        Monomial firstMonomial(monomials.front());
        Monomial lastMonomial(monomials.back());
        int maxExponentDivisor(calculateMaxExponentDivisor(firstMonomial, lastMonomial));
        for (int exponentDivisor = 2; exponentDivisor <= maxExponentDivisor; exponentDivisor++) {
            if (areExponentsDivisible(firstMonomial, exponentDivisor) &&
                areExponentsDivisible(lastMonomial, exponentDivisor)) {
                Monomial unitFirstMonomial(1, firstMonomial.getVariablesToExponentsMapConstReference());
                Monomial unitSecondMonomial(1, lastMonomial.getVariablesToExponentsMapConstReference());
                unitFirstMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, exponentDivisor));
                unitSecondMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, exponentDivisor));
                Monomials monomialsWithExponentsInOrder(
                    getMonomialsWithExponentsInOrder(exponentDivisor, unitFirstMonomial, unitSecondMonomial));
                if (areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials, monomialsWithExponentsInOrder)) {
                    AlbaNumbers coefficients(
                        getCoefficientsInMonomialsWithExponentsInOrder(polynomial, monomialsWithExponentsInOrder));
                    factorizePolynomialForm(
                        result, polynomial, coefficients, unitFirstMonomial.getVariablesToExponentsMapConstReference(),
                        unitSecondMonomial.getVariablesToExponentsMapConstReference());
                }
                if (!result.empty()) {
                    break;
                }
            }
        }
    }
}

void factorizePolynomialForm(
    Polynomials& result, Polynomial const& polynomial, AlbaNumbers const& coefficients,
    Monomial::VariablesToExponentsMap const& firstVariableExponent,
    Monomial::VariablesToExponentsMap const& secondVariableExponent) {
    AlbaNumbers rootValues(calculatePolynomialRoots(coefficients));
    if (areRootsAcceptable(rootValues)) {
        Polynomial remainingPolynomial(polynomial);
        for (AlbaNumber const& rootValue : rootValues) {
            AlbaNumber rootFirstCoefficient(1);
            AlbaNumber rootSecondCoefficient(rootValue * -1);
            AlbaNumber aCoefficient(getFirstMonomial(remainingPolynomial).getConstantConstReference());
            if (aCoefficient.isIntegerOrFractionType() && rootSecondCoefficient.isIntegerOrFractionType()) {
                fixCoefficientsOfFactors(aCoefficient, rootFirstCoefficient, rootSecondCoefficient);
            }
            Monomial rootFirstMonomial(rootFirstCoefficient, firstVariableExponent);
            Monomial rootSecondMonomial(rootSecondCoefficient, secondVariableExponent);
            Polynomial rootPolynomial{rootFirstMonomial, rootSecondMonomial};
            PolynomialOverPolynomial divideProcess(remainingPolynomial, rootPolynomial);
            PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(divideProcess.divide());
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, rootPolynomial);
            remainingPolynomial = quotientAndRemainder.quotient;
        }
        if (!rootValues.empty() && !isTheValue(remainingPolynomial, 1)) {
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, remainingPolynomial);
        }
    }
}

void fixCoefficientsOfFactors(
    AlbaNumber& aCoefficient, AlbaNumber& rootFirstCoefficient, AlbaNumber& rootSecondCoefficient) {
    AlbaNumber::FractionData aCoefficientFractionData(aCoefficient.getFractionData());
    AlbaNumber::FractionData secondFractionData(rootSecondCoefficient.getFractionData());
    int multiplier = getGreatestCommonFactor<int>(
        getAbsoluteValue(aCoefficientFractionData.numerator), secondFractionData.denominator);
    rootFirstCoefficient = rootFirstCoefficient * multiplier;
    rootSecondCoefficient = rootSecondCoefficient * multiplier;
    aCoefficient = aCoefficient / multiplier;
}

bool areAllMonomialsFoundInMonomialsWithExponentsInOrder(
    Monomials const& monomialsToCheck, Monomials const& monomialsWithExponentsInOrder) {
    Polynomial polynomialWithExponentsInOrder(monomialsWithExponentsInOrder);
    bool areAllMonomialsFoundInPolynomialWithExponentsInOrder(true);
    for (Monomial const& monomialToCheck : monomialsToCheck) {
        if (!isVariableExponentInMonomialFound(polynomialWithExponentsInOrder, monomialToCheck)) {
            areAllMonomialsFoundInPolynomialWithExponentsInOrder = false;
            break;
        }
    }
    return areAllMonomialsFoundInPolynomialWithExponentsInOrder;
}

int calculateMaxExponentDivisor(Monomial const& firstMonomial, Monomial const& lastMonomial) {
    AlbaNumber maxExponent = max(getMaxExponent(firstMonomial), getMaxExponent(lastMonomial));
    int maxExponentDivisor = getAbsoluteValue(maxExponent.getInteger());
    return maxExponentDivisor;
}

AlbaNumbers getCoefficientsInMonomialsWithExponentsInOrder(
    Polynomial const& polynomial, Monomials const& monomialsWithExponentsInOrder) {
    AlbaNumbers coefficients;
    for (Monomial const& monomialWithExponentInOrder : monomialsWithExponentsInOrder) {
        coefficients.emplace_back(getCoefficientOfVariableExponent(polynomial, monomialWithExponentInOrder));
    }
    return coefficients;
}

AlbaNumbers calculatePolynomialRoots(AlbaNumbers const& coefficients) {
    AlbaNumbers result;
    if (coefficients.size() == 3) {
        result = getQuadraticRoots(
            mathHelper::RootType::RealRootsOnly, coefficients.at(0), coefficients.at(1), coefficients.at(2));
    } else {
        AlbaNumbers derivativeRoots(calculatePolynomialRoots(getDerivativeCoefficients(coefficients)));
        result = calculatePolynomialRootsUsingBrentMethod(derivativeRoots, coefficients);
    }
    return result;
}

AlbaNumbers calculatePolynomialRootsUsingBrentMethod(
    AlbaNumbers const& previousDerivativeRoots, AlbaNumbers const& coefficients) {
    AlbaNumbers result;
    AlbaNumbers valuesForRootFinding(previousDerivativeRoots);
    AlbaNumber maxAbsoluteValue(getMaxAbsoluteValueForRootFinding(coefficients));
    valuesForRootFinding.emplace_back(maxAbsoluteValue * -1);
    valuesForRootFinding.emplace_back(maxAbsoluteValue);
    sort(valuesForRootFinding.begin(), valuesForRootFinding.end());
    BrentMethod brentMethod(coefficients);
    int size = valuesForRootFinding.size();
    for (int i = 0; i < size - 1; i++) {
        int j = i + 1;
        brentMethod.resetCalculation(valuesForRootFinding.at(i), valuesForRootFinding.at(j));
        brentMethod.runMaxNumberOfIterationsOrUntilFinished(NUMBER_OF_ITERATIONS_IN_BRENT_METHOD);
        AlbaNumberOptional rootOptional(brentMethod.getSolution());
        if (rootOptional) {
            AlbaNumber const& root(rootOptional.value());
            result.emplace_back(root);
        }
    }
    return result;
}

AlbaNumber getMaxAbsoluteValueForRootFinding(AlbaNumbers const& coefficients) {
    AlbaNumber result(0);
    if (!coefficients.empty()) {
        result = max(getAbsoluteValue(coefficients.front()), getAbsoluteValue(coefficients.back()));
    }
    return result;
}

AlbaNumbers getDerivativeCoefficients(AlbaNumbers const& coefficients) {
    AlbaNumbers derivativeCoefficients(coefficients);
    if (!derivativeCoefficients.empty()) {
        derivativeCoefficients.pop_back();
        AlbaNumber derivativeMultiplier(static_cast<long long int>(derivativeCoefficients.size()));
        for (AlbaNumber& derivativeCoefficient : derivativeCoefficients) {
            derivativeCoefficient = derivativeCoefficient * derivativeMultiplier;
            derivativeMultiplier = derivativeMultiplier - 1;
        }
    }
    return derivativeCoefficients;
}

Monomials getMonomialsWithExponentsInOrder(
    int const exponentDivisor, Monomial const& firstInPolynomial, Monomial const& lastInPolynomial) {
    Monomials monomialsWithExponentsInOrder;
    for (int i = 0; i <= exponentDivisor; i++) {
        Monomial firstPart(firstInPolynomial);
        firstPart.raiseToPowerNumber(exponentDivisor - i);
        Monomial secondPart(lastInPolynomial);
        secondPart.raiseToPowerNumber(i);
        Monomial product(firstPart);
        product.multiplyMonomial(secondPart);
        product.simplify();
        monomialsWithExponentsInOrder.emplace_back(product);
    }
    return monomialsWithExponentsInOrder;
}

bool areRootsAcceptable(AlbaNumbers const& rootValues) {
    bool doAnyRootsHaveDoubleValues =
        any_of(rootValues.cbegin(), rootValues.cend(), [](AlbaNumber const& root) { return root.isDoubleType(); });
    return !(shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue() && doAnyRootsHaveDoubleValues);
}

}  // namespace Factorization

}  // namespace algebra

}  // namespace alba
