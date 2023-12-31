#include "OtherUtilities.hpp"

#include <Algorithm/Search/SumSearch/FourSum.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Matrix/Utilities/AlbaMatrixUtilities.hpp>

#include <numeric>

using namespace alba::algorithm;
using namespace alba::mathHelper;
using namespace alba::matrix;
using namespace std;

namespace alba {

namespace math {

namespace {

void findDistinctNonConsecutiveFibonacciNumbersForSum(
    bool& isComplete, UnsignedIntegers& fibonaccisForSum, UnsignedIntegers const& fibonaccis, UnsignedInteger const sum,
    UnsignedInteger const index) {
    // This can be improved by dynamic programming
    for (UnsignedInteger i = index; i < fibonaccis.size(); i++) {
        UnsignedInteger fibonacci(fibonaccis[i]);
        if (sum > fibonacci) {
            fibonaccisForSum.emplace_back(fibonacci);
            findDistinctNonConsecutiveFibonacciNumbersForSum(
                isComplete, fibonaccisForSum, fibonaccis, sum - fibonacci, index + 2);
            if (isComplete) {
                break;
            }
            fibonaccisForSum.pop_back();
        } else if (sum == fibonacci) {
            fibonaccisForSum.emplace_back(fibonacci);
            isComplete = true;
            break;
        }
    }
}

}  // namespace

bool isAFibonacciNumber(UnsignedInteger const number) {
    // https://en.wikipedia.org/wiki/Fibonacci_number#Identification
    // Binet's formula provides a proof that a positive integer x is a Fibonacci number if and only if at least one of
    // 5*x^2 + 4 or 5*x^2 + 4 is a perfect square.
    return isPerfectSquare(5 * number * number + 4) || isPerfectSquare(5 * number * number - 4);
}

bool isALuckyNumber(UnsignedInteger const number) {
    // Lucky numbers are a subset of integers.
    // Rather than going into much theory, let us see the process of arriving at lucky numbers:
    // 1) Take the set of integers:
    // -> 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,......
    // 2) First, delete every second number, we get following reduced set.
    // -> 1,3,5,7,9,11,13,15,17,19,............
    // 3) Now, delete every third number, we get
    // -> 1, 3, 7, 9, 13, 15, 19,........
    // 4) Continue this process indefinitely......
    // Any number that does NOT get deleted due to above process is called “lucky”.
    // Therefore, set of lucky numbers is 1, 3, 7, 13,.........

    UnsignedInteger remainingValue = number;
    UnsignedInteger removedNumber = 2;
    bool result(false);
    while (true) {
        if (removedNumber > 2) {
            result = true;
            break;
        } else if (number % removedNumber == 0) {
            result = false;
            break;
        } else {
            remainingValue = remainingValue - (remainingValue / removedNumber);
            removedNumber++;
        }
    }
    return result;
}

bool isLagrangeTheoremTrue(UnsignedInteger const number) {
    // Lagrange’s theorem states that every positive integer can be represented as a sum of four squares, i.e., a^2 +
    // b^2 + c^2 + d^2. For example, the number 123 can be represented as the sum 8^2 + 5^2 + 5^2 + 3^2.

    UnsignedInteger maxElement = static_cast<UnsignedInteger>(pow(number, 0.5));  // max element is square root
    UnsignedIntegers squaredElements;
    squaredElements.reserve(maxElement - 1);
    for (UnsignedInteger i = 1; i < maxElement; i++) {
        squaredElements.emplace_back(i * i);
    }

    FourSum<UnsignedIntegers> fourSum(squaredElements);
    auto fourValues = fourSum.getPossibleDuplicatedFourValuesWithSum(number);
    UnsignedInteger sumOfSquares = get<0>(fourValues) + get<1>(fourValues) + get<2>(fourValues) + get<3>(fourValues);

    return sumOfSquares == number;
}

bool isZeckendorfTheoremTrue(UnsignedInteger const number) {
    // Zeckendorf’s theorem states that every positive integer has a unique representation as a sum of Fibonacci numbers
    // such that no two numbers are equal or consecutive Fibonacci numbers.
    // For example, the number 74 can be represented as the sum 55 + 13 + 5 + 1.

    bool result(false);
    UnsignedIntegers fibonaccis(getFibonacciNumbersBelowThisNumber(number));

    bool isComplete(false);
    UnsignedIntegers fibonaccisForSum;
    findDistinctNonConsecutiveFibonacciNumbersForSum(isComplete, fibonaccisForSum, fibonaccis, number, 0);

    if (isComplete) {
        UnsignedInteger sumOfFibonaccis =
            accumulate(fibonaccisForSum.cbegin(), fibonaccisForSum.cend(), 0, std::plus<UnsignedInteger>());
        result = sumOfFibonaccis == number;
    }
    return result;
}

UnsignedInteger getNthFibonacciNumber(UnsignedInteger const number) {
    // NOTE: The time complexity is linear but its accurate

    if (number == 0) {
        return 0;
    } else {
        UnsignedInteger previousFibonacci(0);
        UnsignedInteger currentFibonacci(1);
        for (UnsignedInteger n = 2; n <= number; n++) {
            UnsignedInteger nextFibonacci = currentFibonacci + previousFibonacci;
            previousFibonacci = currentFibonacci;
            currentFibonacci = nextFibonacci;
        }
        return currentFibonacci;
    }
}

UnsignedInteger getNthFibonacciNumberUsingBinetsFormula(UnsignedInteger const number) {
    // NOTE: The time complexity is constant but it uses double precision so its not that accurate
    // NOTE: The pow() might be logarithmic but its not clearly written on the standard.

    // Binets formula:
    double sqrtOf5 = sqrt(5);
    double phi = (1 + sqrtOf5) / 2;
    return getIntegerAfterRoundingADoubleValue<UnsignedInteger>(pow(phi, number) / sqrtOf5);
}

UnsignedInteger getNthFibonacciNumberUsingRecursion(UnsignedInteger const number) {
    // NOTE: The time complexity is exponential.
    // The function would be called with fibonacci number of times,
    // so stricter running time would be: O((phi)^n) (from binets formula)
    // O((phi)^n) = O((1 + sqrtOf5)^n) = O(1.618^n)
    if (number <= 1) {
        return number;
    } else {
        return getNthFibonacciNumberUsingRecursion(number - 2) + getNthFibonacciNumberUsingRecursion(number - 1);
    }
}

UnsignedInteger getNthFibonacciUsingMatrixPowerWithLogarithmicTime(UnsignedInteger const number) {
    // NOTE: The time complexity is logarithmic.
    // NOTE: This is discussed in linear recurrence section in Matrix as well

    if (number == 0) {
        return 0;
    } else {
        // Matrix representation:
        // |f(n-1)|f(n)  |
        // |f(n)  |f(n+1)|

        UnsignedIntegerMatrix formulaicTransform(2, 2, {0, 1, 1, 1});

        UnsignedIntegerMatrix fibonacciMatrix(
            getMatrixRaiseToScalarPower(formulaicTransform, number - 1));  // logarithmic
        return fibonacciMatrix.getEntry(1U, 1U);
    }
}

UnsignedInteger getNthFibonacciUsingLogarithmicTabularDP(UnsignedInteger const number) {
    // Derived using matrix power

    UnsignedInteger result(number);
    if (number > 1) {
        UnsignedInteger size = max(number + 1, 2ULL);
        UnsignedIntegers tabularData(size);
        tabularData[0] = 0;
        tabularData[1] = 1;

        SetOfUnsignedIntegers logarithmicSteps{number};
        UnsignedInteger initialValue(number);
        while (initialValue >= 3) {
            initialValue = mathHelper::isOdd(initialValue) ? (initialValue + 1) / 2 : initialValue / 2;
            logarithmicSteps.emplace(initialValue);
            logarithmicSteps.emplace(initialValue - 1);
        }

        for (UnsignedInteger const step : logarithmicSteps) {
            UnsignedInteger& resultForStep(tabularData[step]);
            UnsignedInteger n = (step + 1) / 2;
            UnsignedInteger fibonacciAtK = tabularData[n];
            UnsignedInteger fibonacciAtKMinus1 = tabularData[n - 1];
            if (mathHelper::isOdd(step)) {
                resultForStep = fibonacciAtK * fibonacciAtK + fibonacciAtKMinus1 * fibonacciAtKMinus1;
            } else {
                resultForStep = (2 * fibonacciAtKMinus1 + fibonacciAtK) * fibonacciAtK;
            }
        }
        result = tabularData[number];
    }
    return result;
}

UnsignedIntegers getFibonacciNumbersBelowThisNumber(UnsignedInteger const number) {
    UnsignedIntegers result;
    UnsignedInteger previousFibonacci(0);
    UnsignedInteger currentFibonacci(1);
    if (0 < number) {
        result.emplace_back(0);  // zero is included if number is higher than zero
    }
    while (currentFibonacci < number) {
        result.emplace_back(currentFibonacci);
        UnsignedInteger nextFibonacci = currentFibonacci + previousFibonacci;
        previousFibonacci = currentFibonacci;
        currentFibonacci = nextFibonacci;
    }
    return result;
}

}  // namespace math

}  // namespace alba
