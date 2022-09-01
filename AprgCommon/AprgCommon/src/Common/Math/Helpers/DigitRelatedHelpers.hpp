#pragma once

#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <limits>
#include <type_traits>

namespace alba
{

namespace mathHelper
{

template <typename NumberType> unsigned int getNumberOfDigitsOnBase(NumberType const base, NumberType const value)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    unsigned int result(0);
    NumberType absoluteValue(getAbsoluteValue(value));
    if(absoluteValue >= 1)
    {
        result = static_cast<NumberType>(getLogarithm(base, absoluteValue)) + 1;
    }
    return result;
}

template <typename NumberType> unsigned int getNumberOfBase10Digits(NumberType const value)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return getNumberOfDigitsOnBase<NumberType>(10, value);
}

template <typename NumberType> inline bool areNumberOfDigitsOnTheIntegerLimit(unsigned int const digits)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return digits >= std::numeric_limits<NumberType>::digits10;
}

}//namespace mathHelper

}//namespace alba
