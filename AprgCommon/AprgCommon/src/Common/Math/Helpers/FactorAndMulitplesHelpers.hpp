#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <numeric>

namespace alba
{
namespace mathHelper
{
template <typename NumberType> bool isPrime(NumberType const number)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

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

template <typename NumberType> NumberType isPowerOfTwo(NumberType const number)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::isPowerOfTwo(number);
}

template <typename NumberType> NumberType getGreatestPowerOf2Factor(NumberType const number)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    return AlbaBitValueUtilities<NumberType>::getGreatestPowerOf2Factor(number);
}

template <typename NumberType> NumberType getGreatestCommonFactor(NumberType const firstNumber, NumberType const secondNumber)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    // Consider using std::common_type as return type
    return std::gcd(firstNumber, secondNumber);
}

template <typename NumberType> NumberType getGreatestCommonFactorUsingEuclidAlgorithm(NumberType const firstNumber, NumberType const secondNumber)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    // Using Euclid’s algorithm

    // Euclid’s algorithm provides an efficient way to find the greatest common divisor of two numbers.    // The algorithm is based on the following formula:
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

template <typename NumberType> NumberType getGreatestCommonFactorWithLastValues(
        NumberType const number1,
        NumberType const number2,
        NumberType & lastValue1,
        NumberType & lastValue2)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    NumberType result{};
    if (number2 == 0) // Base Case
    {
        lastValue1 = 1;
        lastValue2 = 0;
        result = number1;
    }
    else
    {
        NumberType previous1{}, previous2{};
        result = getGreatestCommonFactorWithLastValues(number2, number1 % number2, previous1, previous2); // Recursively find the gcf
        lastValue1 = previous2;
        lastValue2 = previous1 - (number1 / number2) * previous2;
    }
    return result;
}

template <typename NumberType> NumberType getLeastCommonMultiple(NumberType const firstNumber, NumberType const secondNumber)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    // Consider using std::common_type as return type
    return std::lcm(firstNumber, secondNumber);
}

template <typename NumberType> NumberType getLeastCommonMultipleUsingEuclidAlgorithm(NumberType const firstNumber, NumberType const secondNumber)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    // Using Euclid’s algorithm
    // lcm(a,b) = ab/gcd(a,b)
    NumberType result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {        result = firstNumber/getGreatestCommonFactor(firstNumber, secondNumber)*secondNumber;
    }
    return result;
}

template <typename NumberType> double getLeastCommonMultipleInDouble(NumberType const firstNumber, NumberType const secondNumber)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    double result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {
        result = static_cast<double>(firstNumber)/getGreatestCommonFactor(firstNumber, secondNumber)*secondNumber;
    }
    return result;
}

template <typename NumberType> NumberType getNumberOfMultiplesInclusive(NumberType const multiple, NumberType const number)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    NumberType result(0);
    if(multiple>0 && number>=multiple)
    {
        result = number/multiple;
    }
    return result;
}

template <typename NumberType> inline NumberType getMultipleThatIsLesserOrEqual(NumberType const multiple, NumberType const number)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    NumberType result(0);
    if(multiple>0)
    {
        result = number/multiple*multiple;
    }
    return result;
}

template <typename NumberType> inline NumberType getMultipleThatIsGreaterOrEqual(NumberType const multiple, NumberType const number)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    NumberType result(0);
    if(multiple>0 && number>0)
    {
        result = ((number-1)/multiple + 1)*multiple;
    }
    return  result;
}

template <typename NumberType> inline NumberType getDifferenceFromGreaterMultiple(NumberType const multiple, NumberType const number)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");

    NumberType result(0);
    NumberType greaterMultiple(getMultipleThatIsGreaterOrEqual(multiple, number));
    if(number <= greaterMultiple)
    {
        result = greaterMultiple - number;
    }
    return result;
}

AlbaNumber getGreatestCommonFactor(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber); // different implementation
AlbaNumber getLeastCommonMultiple(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber); // different implementation

}//namespace mathHelper

}//namespace alba
