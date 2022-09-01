#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba
{

namespace mathHelper
{

template <typename NumberType> bool isPrime(NumberType const number)
{
    // Non prime would have: a * b = nonPrimeNumber, where a and b are integers
    // To have less iterations:
    // When a = b, then we can test if divisible until nonPrimeNumber^0.5
    // When a > b, then we can test if divisible until b. Since b < nonPrimeNumber^0.5, then we can test until nonPrimeNumber^0.5.
    // When a < b, then we can test if divisible until a. Since a < nonPrimeNumber^0.5, then we can test until nonPrimeNumber^0.5.
    bool result(number>=2);
    NumberType limit(pow(number, 0.5));
    for(NumberType i=2; i<=limit; i++)
    {
        if(isDivisible(number, i))
        {
            result = false;
            break;
        }
    }
    return result;
}

template <typename NumberType> NumberType getGreatestPowerOf2Factor(NumberType const number)
{
    return AlbaBitValueUtilities<NumberType>::getGreatestPowerOf2Factor(number);
}

template <typename NumberType> NumberType getGreatestCommonFactor(NumberType const firstNumber, NumberType const secondNumber)
{
    // Using Euclid’s algorithm

    // Euclid’s algorithm provides an efficient way to find the greatest common divisor of two numbers.
    // The algorithm is based on the following formula:
    // gcd(a, b) =
    // -> if b=0: a
    // -> if b!=0: gcd(b, a%b)

    NumberType result(0);
    NumberType temporaryFirst(getAbsoluteValue(firstNumber)); // only consider positive GCF
    NumberType temporarySecond(getAbsoluteValue(secondNumber)); // only consider positive GCF
    while(true)
    {
        if(temporarySecond==0)
        {
            result = temporaryFirst;
            break;
        }
        else
        {
            NumberType copyOfFirst(temporaryFirst);
            temporaryFirst = temporarySecond;
            temporarySecond = copyOfFirst%temporarySecond;
        }
    }
    return result;
}

template <typename NumberType> NumberType getLeastCommonMultiple(NumberType const firstNumber, NumberType const secondNumber)
{
    // Using Euclid’s algorithm
    // lcm(a,b) = ab/gcd(a,b)
    NumberType result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {
        result = firstNumber/getGreatestCommonFactor(firstNumber, secondNumber)*secondNumber;
    }
    return result;
}

template <typename NumberType> double getLeastCommonMultipleInDouble(NumberType const firstNumber, NumberType const secondNumber)
{
    double result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {
        result = static_cast<double>(firstNumber)/getGreatestCommonFactor(firstNumber, secondNumber)*secondNumber;
    }
    return result;
}

template <typename NumberType> NumberType getNumberOfMultiplesInclusive(NumberType const multiple, NumberType const number)
{
    NumberType result(0);
    if(multiple>0)
    {
        result = ((number+multiple-1)/multiple);
    }
    return result;
}

template <typename NumberType> NumberType getDifferenceFromGreaterMultiple(NumberType const multiple, NumberType const number)
{
    unsigned result(0);
    if(multiple>0)
    {
        NumberType numberOfMultiples(getNumberOfMultiplesInclusive(multiple, number));
        result = (numberOfMultiples*multiple) - number;
    }
    return result;
}

AlbaNumber getGreatestCommonFactor(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber); // different implementation
AlbaNumber getLeastCommonMultiple(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber); // different implementation

}//namespace mathHelper

}//namespace alba
