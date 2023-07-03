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

    NumberType result(1), newBase(base), newExponent(exponent);
    while (newExponent > 0) {
        if (isEven(newExponent)) {
            newBase *= newBase;
            newExponent /= 2;
        } else {
            result *= newBase;
            newExponent--;
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

    NumberType result(initialGuess);
    for (int i = 0; i < numberOfIterations; i++) {
        // xk+1 = (n-1)*xk/n + (A/n) * (1/(xk^(n−1)))
        result = (rootDegree - 1) * result / rootDegree +
                 radicand / rootDegree / getRaiseToPowerBasedOnType(result, rootDegree - 1);
    }
    return result;
}

bool isPerfectSquare(AlbaNumber const& value);                            // pass as const reference
bool isPerfectCube(AlbaNumber const& value);                              // pass as const reference
bool isPerfectNthPower(AlbaNumber const& number, size_t const nthPower);  // different implementation
}  // namespace alba::mathHelper