#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
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

template <typename NumberType> NumberType getRaiseToPowerForIntegers(NumberType const base, NumberType const exponent)
{
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
    return static_cast<int>(ceil(pow(base, exponent)));
}

bool isPerfectSquare(AlbaNumber const& value); // pass as const reference
bool isPerfectCube(AlbaNumber const& value); // pass as const reference
bool isPerfectNthPower(AlbaNumber const& number, unsigned int const nthPower); // different implementation

}//namespace mathHelper
}//namespace alba