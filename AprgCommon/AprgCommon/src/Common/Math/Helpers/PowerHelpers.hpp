#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba
{

namespace mathHelper
{

template <typename NumberType> bool isPerfectNthPower(NumberType const value, NumberType const nthPower); // declare this first

template <typename NumberType> bool isPowerOfTwo(NumberType const value)
{
    return AlbaBitValueUtilities<NumberType>::isPowerOfTwo(value);
}

template <typename NumberType> bool isPerfectSquare(NumberType const value)
{
    return isPerfectNthPower(value, static_cast<NumberType>(2));
}

template <typename NumberType> bool isPerfectCube(NumberType const value)
{
    return isPerfectNthPower(value, static_cast<NumberType>(3));
}

template <typename NumberType> bool isPerfectNthPower(NumberType const value, NumberType const nthPower)
{
    return isAlmostAnInteger<double, NumberType>(pow(value, static_cast<double>(1)/nthPower));
}

bool isPerfectSquare(AlbaNumber const& value); // pass as const reference
bool isPerfectCube(AlbaNumber const& value); // pass as const reference
bool isPerfectNthPower(AlbaNumber const& number, unsigned int const nthPower); // different implementation
int getRaiseToPowerForIntegers(int const base, unsigned int exponent);

}//namespace mathHelper

}//namespace alba
