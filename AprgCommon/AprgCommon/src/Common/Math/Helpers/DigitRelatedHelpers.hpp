#pragma once

#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <limits>

namespace alba::mathHelper {

template <typename NumberType>
size_t getNumberOfDigitsOnBase(NumberType const base, NumberType const value) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    size_t result(0);
    NumberType absoluteValue(getAbsoluteValue(value));
    if (absoluteValue >= 1) {
        result = static_cast<NumberType>(getLogarithmForIntegers(base, absoluteValue)) + 1;
    }
    return result;
}

template <typename NumberType>
size_t getNumberOfBase10Digits(NumberType const value) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return getNumberOfDigitsOnBase<NumberType>(10, value);
}

template <typename NumberType>
inline bool areNumberOfDigitsOnTheIntegerLimit(size_t const digits) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return digits >= std::numeric_limits<NumberType>::digits10;
}

}  // namespace alba::mathHelper
