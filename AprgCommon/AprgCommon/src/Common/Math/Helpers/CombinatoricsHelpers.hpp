#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

namespace alba
{
namespace mathHelper
{
template <typename NumberType> NumberType getNumberOfPossibilities(
        NumberType const numberOfPossibilitiesPerTime,
        NumberType const numberOfTimes)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    static_assert(typeHelper::isUnsignedType<NumberType>(), "Number type must be an unsigned");

    return getRaiseToPowerForIntegers(numberOfPossibilitiesPerTime, numberOfTimes);
}

template <typename NumberType> NumberType getFactorial(NumberType const number)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    static_assert(typeHelper::isUnsignedType<NumberType>(), "Number type must be an unsigned");

    NumberType result(1);
    for(NumberType currentNumber=number; currentNumber>1; currentNumber--)    {
        result *= currentNumber;
    }
    return result;}

template <typename NumberType> NumberType getNumberOfPermutations(
        NumberType const n,
        NumberType const r)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    static_assert(typeHelper::isUnsignedType<NumberType>(), "Number type must be an unsigned");

    NumberType result(0);
    if(n >= r)    {
        result = 1;
        for(NumberType currentNumber=n; currentNumber>n-r; currentNumber--)
        {            result *= currentNumber;
        }
    }
    return result;
}

template <typename NumberType> NumberType getNumberOfCombinations(
        NumberType const n,
        NumberType const r)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    static_assert(typeHelper::isUnsignedType<NumberType>(), "Number type must be an unsigned");

    // Formula 1(recursive formula): (n, k) = (n-1, k-1) + (n-1, k)
    // Base cases: (n, 0) = 1, (n, n) = 1    // Idea: The idea is to fix an element x in the set.
    // If x is included in the subset, we have to choose k-1 elements from n-1 elements,
    // and if x is not included in the subset, we have to choose k elements from n-1 elements.
    // Note: Formula 1 might be useful in dynamic programming
    // Formula 2(factorial formula): (n, k) = n! / (k! * (n-k)!)
    // Idea: There are n! permutations of n elements.
    // We go through all permutations and always include the first k elements of the permutation in the subset.
    // Since the order of the elements in the subset and outside the subset does not matter, the result is divided by k! and (n-k)!

    // Formula 2 is the one implemented below:

    NumberType result(0);
    if(n >= r)
    {
        result = 1;
        NumberType numerator=n;
        NumberType denominator=r;
        NumberType accumulatedNumerator=1;
        NumberType accumulatedDenominator=1;
        bool shouldContinue=true;
        while(shouldContinue)
        {
            shouldContinue = false;
            if(numerator > n-r)
            {
                accumulatedNumerator *= numerator--;
                shouldContinue = true;
            }
            if(denominator > 1)
            {
                accumulatedDenominator *= denominator--;
                shouldContinue = true;
            }
            if(shouldContinue && accumulatedDenominator>1 && isValueBeyondLimits<NumberType>(static_cast<double>(accumulatedNumerator)*numerator))
            {
                NumberType gcf = getGreatestCommonFactor(accumulatedNumerator, accumulatedDenominator);
                accumulatedNumerator /= gcf;
                accumulatedDenominator /= gcf;
            }
        }
        result = accumulatedNumerator/accumulatedDenominator;
    }
    return result;
}

template <typename NumberType> NumberType getValueAtPascalTriangle(
        NumberType const rowIndex,
        NumberType const columnIndex)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    static_assert(typeHelper::isUnsignedType<NumberType>(), "Number type must be an unsigned");

    // This is also called the binomial coefficient.
    // The binomial coefficient equals the number of ways we can choose a subset of k elements from a set of n elements.    // The binomial coefficient = number of combinations

    return getNumberOfCombinations(rowIndex, columnIndex);
}
template <typename NumberType>
typename std::make_signed<NumberType>::type
getStirlingNumberOfTheSecondKind(
        NumberType const n,
        NumberType const k)
{
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    static_assert(typeHelper::isUnsignedType<NumberType>(), "Number type must be an unsigned");

    // In mathematics, particularly in combinatorics, a Stirling number of the second kind (or Stirling partition number)
    // is the number of ways to partition a set of n objects into k non-empty subsets
    // Stirling numbers of the second kind occur in the field of mathematics called combinatorics and the study of partitions.

    using SignedType = typename std::make_signed<NumberType>::type;
    SignedType sum(0);
    bool isDivisibleByTwo(true);
    for(NumberType i=0; i<=k; i++)
    {
        SignedType sign = isDivisibleByTwo ? 1 : -1;
        sum += sign * getNumberOfCombinations(k, i) * getRaiseToPowerForIntegersUsingPow(k-i, n);
        isDivisibleByTwo = !isDivisibleByTwo;
    }
    sum /= getFactorial(k);
    return sum;
}

}//namespace mathHelper

}//namespace alba
