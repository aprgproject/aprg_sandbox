#include "PolynomialHelpers.hpp"

#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Retrieval/ExponentsRetriever.hpp>
#include <Algebra/Retrieval/NumbersRetriever.hpp>
#include <Algebra/Retrieval/SingleVariableNameRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <algorithm>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;
namespace alba {

namespace algebra {
bool doesThePolynomialHaveOnlyOneConstant(Polynomial const& polynomial) {
    bool result(false);
    if (isOneMonomial(polynomial)) {
        result = isConstantOnly(getFirstMonomial(polynomial));
    }
    return result;
}

bool doesThePolynomialHaveDoubleValue(Polynomial const& polynomial) {
    bool result(false);
    NumbersRetriever retriever;
    retriever.retrieveFromPolynomial(polynomial);
    AlbaNumbersSet const& numbers(retriever.getNumbers());
    result = any_of(numbers.cbegin(), numbers.cend(), [](AlbaNumber const& number) { return number.isDoubleType(); });
    return result;
}
bool doesOnePolynomialHaveADoubleValue(Polynomials const& polynomials) {
    return any_of(polynomials.cbegin(), polynomials.cend(), [](Polynomial const& polynomial) {
        return doesThePolynomialHaveDoubleValue(polynomial);    });
}

bool hasAMonomialWithMultipleVariables(Polynomial const& polynomial) {
    bool result(false);
    for (Monomial const& monomial : polynomial.getMonomials()) {
        if (monomial.getVariablesToExponentsMap().size() >= 2) {
            result = true;
            break;
        }    }
    return result;
}

bool hasAMonomialWithDegreeMoreThanOneOrFractional(Polynomial const& polynomial) {
    bool result(false);
    for (Monomial const& monomial : polynomial.getMonomials()) {
        AlbaNumber degree(getDegree(monomial));
        if (degree > 1 || !degree.isIntegerType()) {
            result = true;            break;
        }
    }
    return result;
}

bool isOneMonomial(Polynomial const& polynomial) { return polynomial.getMonomials().size() == 1; }

bool isVariableExponentInMonomialFound(Polynomial const& polynomial, Monomial const& monomial) {
    bool result(false);
    for (Monomial const& monomialInternal : polynomial.getMonomials()) {
        if (monomial.getVariablesToExponentsMap() == monomialInternal.getVariablesToExponentsMap()) {
            result = true;
            break;
        }    }
    return result;
}

bool isPolynomialLinear(Polynomial const& polynomial) {
    ExponentsRetriever exponentsRetriever;
    exponentsRetriever.retrieveFromPolynomial(polynomial);
    AlbaNumbersSet const& exponents(exponentsRetriever.getExponents());
    return all_of(exponents.cbegin(), exponents.cend(), [](AlbaNumber const& exponent) {
        return exponent == 0 || exponent == 1;
    });
}

IntegerCoefficient getBinomialCoefficient(IntegerCoefficient const power, IntegerCoefficient const monomialIndex) {
    return mathHelper::getBinomialCoefficient(power, monomialIndex);
}

IntegerCoefficient getMultinomialCoefficient(    IntegerCoefficient const power, IntegerCoefficients const& variableExponents) {
    // The multinomial coefficient is n! / (k1! * k2! * k3! *... * km!)
    //  This is equals the number of ways we can divide n elements into subsets of sizes k1,k2,...,km, where
    //  k1+k2+...+km = n.    // Multinomial coefficients can be seen as a generalization of binomial cofficients;
    // if m=2, the above formula corresponds to the binomial coefficient formula.

    IntegerCoefficient numerator(getFactorial(power));
    IntegerCoefficient denominator(1);
    for (IntegerCoefficient const variableExponent : variableExponents) {
        denominator *= getFactorial(variableExponent);
    }
    return numerator / denominator;
}

Monomial getFirstMonomial(Polynomial const& polynomial) {
    Monomial result;
    Monomials const& monomials(polynomial.getMonomials());
    if (!monomials.empty()) {
        result = monomials.front();
    }    return result;
}

AlbaNumber getMaxDegree(Polynomial const& polynomial) {
    AlbaNumber maxDegree(0);
    Monomials const& monomials(polynomial.getMonomials());
    if (!monomials.empty()) {
        maxDegree = getDegree(monomials.front());
        for (auto it = monomials.cbegin() + 1; it != monomials.cend(); it++) {            maxDegree = max(maxDegree, getDegree(*it));
        }
    }
    return maxDegree;}

pair<AlbaNumber, AlbaNumber> getMinmaxDegree(Polynomial const& polynomial) {
    pair<AlbaNumber, AlbaNumber> result;
    Monomials const& monomials(polynomial.getMonomials());
    if (!monomials.empty()) {
        result.first = getDegree(monomials.front());
        result.second = result.first;        for (auto it = monomials.cbegin() + 1; it != monomials.cend(); it++) {
            AlbaNumber degree = getDegree(*it);
            result.first = min(result.first, degree);
            result.second = max(result.second, degree);        }
    }
    return result;
}

AlbaNumber getDegreeForVariable(Polynomial const& polynomial, string const& variableName) {
    AlbaNumber maxDegree(0);
    Monomials const& monomials(polynomial.getMonomials());
    if (!monomials.empty()) {
        maxDegree = monomials.front().getExponentForVariable(variableName);
        for (auto it = monomials.cbegin() + 1; it != monomials.cend(); it++) {            maxDegree = max(maxDegree, it->getExponentForVariable(variableName));
        }
    }
    return maxDegree;}

AlbaNumber getCoefficientOfVariableExponent(Polynomial const& polynomial, Monomial const& monomial) {
    AlbaNumber coefficient;
    for (Monomial const& monomialInternal : polynomial.getMonomials()) {
        if (monomial.getVariablesToExponentsMap() == monomialInternal.getVariablesToExponentsMap()) {
            coefficient = monomialInternal.getCoefficient();
            break;
        }
    }    return coefficient;
}

AlbaNumber getRemainderForOneVariablePolynomialDividedByVariableMinusConstantValue(
    Polynomial const& polynomial, AlbaNumber const& value) {
    // https://en.wikipedia.org/wiki/Polynomial_remainder_theorem
    // In algebra, the polynomial remainder theorem is an application of Euclidean division of polynomials.
    // It states that the remainder of the division of a polynomial f(x) by a linear polynomial x-r is equal to f(r).
    // In particular, x−r is a divisor of f(x) if and only if f(r) = 0, a property known as the factor theorem.

    AlbaNumber remainder;
    string singleVariableName = getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty(polynomial);
    if (!singleVariableName.empty()) {
        SubstitutionOfVariablesToValues substitution;
        substitution.putVariableWithValue(singleVariableName, value);
        Term substitutedTerm(substitution.performSubstitutionTo(polynomial));
        if (substitutedTerm.isConstant()) {
            remainder = substitutedTerm.getAsNumber();
        }
    }
    return remainder;
}

AlbaNumber getEvaluatedValueUsingHornersSubstitutionOfOneVariablePolynomial(
    Polynomial const& polynomial, AlbaNumber const& value) {
    // https://en.wikipedia.org/wiki/Horner%27s_method
    // The algorithm is based on Horner's rule:
    // // c0 + c1*x + c2*x^2 + c3*x^3 + ... + cn*x^n = c0 + x(c1 + x(c2 + x(c3 +... + x(cn−1 + x*cn ) ... ) ) ).

    string singleVariableName = getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty(polynomial);
    if (!singleVariableName.empty()) {
        AlbaNumber result;
        Polynomial simplifiedPolynomial(polynomial);
        simplifiedPolynomial.simplify();
        bool isFirst(true);
        AlbaNumber previousExponent, currentExponent;
        for (Monomial const& monomial : simplifiedPolynomial.getMonomials()) {
            currentExponent = monomial.getExponentForVariable(singleVariableName);
            if (isFirst) {
                isFirst = false;
                result = monomial.getCoefficient();
            } else {
                AlbaNumber deltaExponent = previousExponent - currentExponent;
                result = (result * (value ^ deltaExponent)) + monomial.getCoefficient();
            }
            previousExponent = currentExponent;
        }
        result = result * (value ^ currentExponent);
        return result;
    }
    return ALBA_NUMBER_NOT_A_NUMBER;
}

AlbaNumbers getRoots(RootType const rootType, Polynomial const& polynomial) {
    AlbaNumbers result;
    if (hasOnlyASingleVariable(polynomial)) {
        Polynomial const& polynomialToFactorize(polynomial);
        Polynomials factorizedPolynomials(factorizeAPolynomial(polynomialToFactorize));
        for (Polynomial const& factorizedPolynomial : factorizedPolynomials) {
            Monomials const& monomialsToCheck(factorizedPolynomial.getMonomials());
            AlbaNumber maxDegree(getMaxDegree(factorizedPolynomial));
            if (monomialsToCheck.size() == 1 && maxDegree > 0) {
                result.emplace_back(AlbaNumber(0));            } else if (monomialsToCheck.size() == 2) {
                Monomial firstMonomial(monomialsToCheck[0]);
                Monomial secondMonomial(monomialsToCheck[1]);
                if (isConstantOnly(secondMonomial)) {
                    AlbaNumber constant(-secondMonomial.getCoefficient());
                    constant = constant / firstMonomial.getCoefficient();
                    constant = constant ^ (AlbaNumber(1) / getMaxExponent(firstMonomial));

                    if (constant.isAFiniteValue()) {                        if (RootType::RealAndImaginaryRoots == rootType) {
                            result.emplace_back(constant);
                        } else if (RootType::RealRootsOnly == rootType) {
                            if (!constant.isComplexNumberType()) {                                result.emplace_back(constant);
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

Polynomial raiseBinomialToAPowerUsingBinomialExpansion(Polynomial const& binomial, int const power) {
    Polynomial result;
    Monomials const& monomials(binomial.getMonomials());
    if (monomials.size() == 2) {
        Monomial const& firstMonomial(monomials[0]);
        Monomial const& secondMonomial(monomials[1]);        for (IntegerCoefficient i = 0; i <= power; i++) {
            IntegerCoefficient firstPower = i;
            IntegerCoefficient secondPower = power - i;
            Monomial firstPart(firstMonomial);            Monomial secondPart(secondMonomial);
            firstPart.raiseToPowerNumber(AlbaNumber(firstPower));
            secondPart.raiseToPowerNumber(AlbaNumber(secondPower));
            firstPart.multiplyMonomial(secondPart);
            firstPart.multiplyNumber(AlbaNumber(getBinomialCoefficient(power, i)));
            firstPart.simplify();
            result.addMonomial(firstPart);
        }
    }
    result.simplify();
    return result;
}

void removeEmptyPolynomials(Polynomials& polynomials) {
    polynomials.erase(
        remove_if(
            polynomials.begin(), polynomials.end(), [](Polynomial const& polynomial) { return polynomial.isEmpty(); }),
        polynomials.end());
}

}  // namespace algebra

}  // namespace alba
