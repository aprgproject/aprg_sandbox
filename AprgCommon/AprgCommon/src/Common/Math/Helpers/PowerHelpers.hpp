#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

namespace alba::mathHelper {

// dependent definitions
template <typename NumberType>
bool isPerfectNthPower(NumberType const value, NumberType const nthPower);  // declare this first

template <typename NumberType>
inline bool isPowerOfTwo(NumberType const value) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::isPowerOfTwo(value);
}

template <typename NumberType>
inline bool isPerfectSquare(NumberType const value) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return isPerfectNthPower(value, static_cast<NumberType>(2));
}

template <typename NumberType>
inline bool isPerfectCube(NumberType const value) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return isPerfectNthPower(value, static_cast<NumberType>(3));
}

template <typename NumberType>
inline bool isPerfectNthPower(NumberType const value, NumberType const nthPower) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return isAlmostAnInteger<double, NumberType>(pow(value, static_cast<double>(1) / nthPower));
}

template <typename NumberType>
inline NumberType get2ToThePowerOf(NumberType const exponent) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::get2ToThePowerOf(exponent);
}

template <typename NumberType>
NumberType getRaiseToPowerForIntegers(NumberType const base, NumberType const exponent) {
    // This is always correct and faster than pow (check performance test for comparison)

    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    NumberType result(1), currentBase(base), remainingExponent(exponent);
    while (remainingExponent > 0) {
        if (isEven(remainingExponent)) {
            currentBase *= currentBase;
            remainingExponent /= 2;
        } else {
            result *= currentBase;
            remainingExponent--;
        }
    }
    return result;
}

template <typename NumberType>
inline NumberType getRaiseToPowerForIntegersUsingPow(NumberType const base, NumberType const exponent) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    // this is slower (by not too much, check performance test)

    return static_cast<int>(ceil(pow(base, exponent)));
}

template <typename NumberType>
std::enable_if_t<typeHelper::isIntegralType<NumberType>(), NumberType> getRaiseToPowerBasedOnType(
    NumberType const base, NumberType const exponent) {
    return getRaiseToPowerForIntegers(base, exponent);
}

template <typename NumberType>
std::enable_if_t<typeHelper::isFloatingPointType<NumberType>(), NumberType> getRaiseToPowerBasedOnType(
    NumberType const base, NumberType const exponent) {
    return pow(base, exponent);
}

template <typename NumberType>
NumberType getNthRoot(
    NumberType const radicand, NumberType const rootDegree, NumberType const initialGuess,
    int const numberOfIterations) {
    // https://en.wikipedia.org/wiki/Nth_root#Computing_principal_roots
    // This uses Newton method

    NumberType current(initialGuess);
    // set previous to an arbitiary value that is not equal to result
    NumberType previous = current - 1;
    for (int i = 0; i < numberOfIterations && !isAlmostEqual(previous, current); i++) {
        // xk+1 = (n-1)*xk/n + (A/n) * (1/(xk^(n−1)))
        previous = current;
        current = (rootDegree - 1) * current / rootDegree +
                  radicand / rootDegree / getRaiseToPowerBasedOnType(current, rootDegree - 1);
    }
    return current;
}

template <typename NumberType>
NumberType getNthRoot(NumberType const radicand, NumberType const rootDegree) {
    return getNthRoot(radicand, rootDegree, static_cast<NumberType>(1), std::numeric_limits<int>::max());
}

template <typename NumberType>
NumberType getSquareRootUsingNewtonMethod(
    NumberType const radicand, NumberType const initialGuess, int const numberOfIterations) {
    NumberType current(initialGuess);
    // set previous to an arbitiary value that is not equal to result
    NumberType previous = current - 1;
    for (int i = 0; i < numberOfIterations && !isAlmostEqual(previous, current); i++) {
        // xk+1 = (xk + radicand/xk)/2
        previous = current;
        current = (current + radicand / current) / 2;
    }
    return current;
}

template <typename NumberType>
NumberType getSquareRootUsingBinarySearch(NumberType const radicand) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    NumberType low(0), high(radicand);
    while (low < high) {
        NumberType mid = low + (high - low) / 2;
        if (mid * mid <= radicand) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return (low * low > radicand) ? low - 1 : low;

    // Some end cases analysis:
    // -> If interval is one element[a], loop ends, we get check value
    // -> If interval is two elements[a,b]:
    // ---> middleSquared < target -> low moves to right, only b retains (target might be to the left)
    // ---> middleSquared == target -> low moves to right, only b retains (target might be to the left)
    // ---> target < middleSquared -> high moves to left, only a retains
    // -> If interval is three elements, this reduces to one element
    // -> If interval is four elements, this reduces to one element or two elements
}

bool isPerfectSquare(AlbaNumber const& value);                            // pass as const reference
bool isPerfectCube(AlbaNumber const& value);                              // pass as const reference
bool isPerfectNthPower(AlbaNumber const& number, size_t const nthPower);  // different implementation

}  // namespace alba::mathHelper
