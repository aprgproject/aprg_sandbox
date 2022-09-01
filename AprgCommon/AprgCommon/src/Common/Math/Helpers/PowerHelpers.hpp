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


template <typename NumberType> bool isPowerOfTwo(NumberType const value)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::isPowerOfTwo(value);
}

template <typename NumberType> bool isPerfectSquare(NumberType const value)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return isPerfectNthPower(value, static_cast<NumberType>(2));
}

template <typename NumberType> bool isPerfectCube(NumberType const value)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return isPerfectNthPower(value, static_cast<NumberType>(3));
}

template <typename NumberType> bool isPerfectNthPower(NumberType const value, NumberType const nthPower)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    return isAlmostAnInteger<double, NumberType>(pow(value, static_cast<double>(1)/nthPower));
}

template <typename NumberType> NumberType getRaiseToPowerForIntegers(NumberType const base, NumberType const exponent)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");

    // This is faster and correct than pow
    if(exponent <= 0) // also catches negative exponents (if negative just return 1)
    {
        return 1;
    }
    else if(isEven(exponent))
    {
        return getRaiseToPowerForIntegers(base * base, exponent/2);
    }
    else
    {
        return base * getRaiseToPowerForIntegers(base, exponent-1);
    }
}

template <typename NumberType> NumberType getRaiseToPowerForIntegersUsingPow(NumberType const base, NumberType const exponent)
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
