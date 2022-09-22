#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <type_traits>

namespace alba
{

namespace mathHelper
{

// dependent definitions
template <typename NumberType> bool isPerfectNthPower(NumberType const value, NumberType const nthPower); // declare this first


template <typename NumberType> inline bool isPowerOfTwo(NumberType const value)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::isPowerOfTwo(value);
}

template <typename NumberType> inline bool isPerfectSquare(NumberType const value)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return isPerfectNthPower(value, static_cast<NumberType>(2));
}

template <typename NumberType> inline bool isPerfectCube(NumberType const value)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return isPerfectNthPower(value, static_cast<NumberType>(3));
}

template <typename NumberType> inline bool isPerfectNthPower(NumberType const value, NumberType const nthPower)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return isAlmostAnInteger<double, NumberType>(pow(value, static_cast<double>(1)/nthPower));
}

template <typename NumberType> inline NumberType get2ToThePowerOf(NumberType const exponent)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::get2ToThePowerOf(exponent);
}

template <typename NumberType> NumberType getRaiseToPowerForIntegers(NumberType const base, NumberType const exponent)
{
    // This is always correct and faster than pow (check performance test for comparison)

    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    NumberType result(1), newBase(base), newExponent(exponent);
    while(newExponent > 0)
    {        if(isEven(newExponent))
        {
            newBase *= newBase;
            newExponent /= 2;
        }
        else
        {
            result *= newBase;
            newExponent--;
        }
    }
    return result;
}

template <typename NumberType> inline NumberType getRaiseToPowerForIntegersUsingPow(NumberType const base, NumberType const exponent)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    // this is slower (by not too much, check performance test)

    return static_cast<int>(ceil(pow(base, exponent)));
}

bool isPerfectSquare(AlbaNumber const& value); // pass as const reference
bool isPerfectCube(AlbaNumber const& value); // pass as const reference
bool isPerfectNthPower(AlbaNumber const& number, unsigned int const nthPower); // different implementation

}//namespace mathHelper

}//namespace alba
