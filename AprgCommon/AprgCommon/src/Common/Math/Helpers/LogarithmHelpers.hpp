#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <cmath>

namespace alba::mathHelper {

inline double getLogarithm(double const base, double const inputForLogarithm) {
    // change of base formula
    // log a(b) = C
    // -> b = a^C
    // -> ln(b) = ln(a^C)
    // -> ln(b) = C*ln(a)
    // -> C = ln(b)/ln(a)

    // log a(b) = ln(b) / ln(a)
    return log(inputForLogarithm) / log(base);
}

template <typename NumberType>inline NumberType getLogarithmWithBase2Of(NumberType const value) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::getLogarithmWithBase2Of(value);}

template <typename NumberType>
NumberType getLogarithmForIntegers(NumberType const base, NumberType const inputForLogarithm) {
    // This is always correct and faster than pow (check performance test for comparison)

    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    NumberType result(0);
    if (base > 1 && inputForLogarithm > 0) {  // base must be at least 2 and input should be positive
        NumberType currentCount(1), currentBase(base), remainingValue(inputForLogarithm);
        while (remainingValue > 0) {
            NumberType nextRemainingValue = remainingValue / currentBase;
            if (nextRemainingValue > 0) {
                result += currentCount;
                currentBase *= base;
                currentCount++;
            } else {
                nextRemainingValue = remainingValue / base;
                if (nextRemainingValue > 0) {
                    result++;
                    currentBase = base * base;
                    currentCount = 2;
                }
            }
            remainingValue = nextRemainingValue;
        }
    }
    return result;
}

template <typename NumberType>
NumberType getCeilOfLogarithmForIntegers(NumberType const base, NumberType const inputForLogarithm) {
    return getLogarithmForIntegers(base, (inputForLogarithm * base) - 1);
}

template <typename IntegerType>
IntegerType getIterativeLogarithm(double const base, double const inputForLogarithm) {
    static_assert(typeHelper::isIntegralType<IntegerType>(), "IntegerType must be an integer");

    // The iterated logarithm of n, written log* n (usually read "log star"),
    // is the number of times the logarithm function must be iteratively applied
    // before the result is less than or equal to 1.

    IntegerType count(0);
    double currentLogarithm = getLogarithm(base, inputForLogarithm);
    while (currentLogarithm >= 0 && !isAlmostEqual(currentLogarithm, 1.0)) {
        count++;
        currentLogarithm = getLogarithm(base, currentLogarithm);
    }
    return count;
}

template <typename IntegerType>
IntegerType getSuperLogarithm(double const base, double const inputForLogarithm) {
    static_assert(typeHelper::isIntegralType<IntegerType>(), "IntegerType must be an integer");
    static_assert(typeHelper::isSignedType<IntegerType>(), "IntegerType must be a signed type");

    // In mathematics, the super-logarithm is one of the two inverse functions of tetration.
    // On the positive real numbers, the continuous super-logarithm (inverse tetration) is essentially equivalent
    // However, on the negative real numbers, log-star is 0, whereas the superlogarithm = -1

    int result(0);
    if (inputForLogarithm >= 0) {
        result = getIterativeLogarithm<IntegerType>(base, inputForLogarithm);
    } else {
        result = -1;
    }
    return result;
}

}  // namespace alba::mathHelper
