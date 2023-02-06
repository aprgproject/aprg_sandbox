#include "CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum.hpp"

#include <Common/Math/Helpers/PowerHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum(
        Count const numberOfDigits,
        Value const sum)
    : m_numberOfDigits(numberOfDigits)
    , m_sumOfDigits(sum)
{}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingNaiveRecursion() const
{
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(2^n)
    // Auxiliary Space: Constant

    Count result(0);
    if(m_numberOfDigits>0)
    {
        result = getCountUsingNaiveRecursion(m_numberOfDigits-1, m_sumOfDigits);
    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingMemoizationDP() const
{
    // Time Complexity: O(numberOfDigits * sumOfDigits * 9) (same as tabular)
    // Auxiliary Space: O(numberOfDigits * sumOfDigits)

    Count result(0);
    if(m_numberOfDigits>0)
    {
        CountMatrix countMatrix(m_numberOfDigits, m_sumOfDigits+1, UNUSED_COUNT);
        result = getCountUsingMemoizationDP(countMatrix, m_numberOfDigits-1, m_sumOfDigits);
    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingTabularDP() const
{
    // Time Complexity: O(numberOfDigits * sumOfDigits * 9)
    // Auxiliary Space: O(numberOfDigits * sumOfDigits)

    Count result(0);
    if(m_numberOfDigits>0)
    {
        CountMatrix countMatrix(m_numberOfDigits, m_sumOfDigits+1, 0U);

        for(Value digitValue=0; digitValue<=min(m_sumOfDigits, 9U); digitValue++)
        {
            countMatrix.setEntry(0U, digitValue, 1);
        }
        for(Count digitIndex=1; digitIndex<m_numberOfDigits; digitIndex++)
        {
            countMatrix.setEntry(digitIndex, 0, 1);
            for(Value partialSum=1; partialSum<=m_sumOfDigits; partialSum++)
            {
                for(Value digitValue=0; digitValue<=min(partialSum-1, 9U); digitValue++)
                {
                    countMatrix.getEntryReference(digitIndex, partialSum) += countMatrix.getEntry(digitIndex-1, partialSum-digitValue);
                }
            }
        }
        result = countMatrix.getEntry(countMatrix.getNumberOfColumns()-1, countMatrix.getNumberOfRows()-1);
    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingTabularDPAndSpaceEfficient() const
{
    // Time Complexity: O(numberOfDigits * sumOfDigits * 9)
    // Auxiliary Space: O(sumOfDigits)

    Count result(0);
    if(m_numberOfDigits>0)
    {
        Counts partialSumToCount(m_sumOfDigits+1);
        for(Value digitValue=0; digitValue<=min(m_sumOfDigits, 9U); digitValue++)
        {
            partialSumToCount[digitValue]=1;
        }
        for(Count digitCount=1; digitCount<m_numberOfDigits; digitCount++)
        {
            for(Value partialSum=m_sumOfDigits; partialSum>=1; partialSum--)
            {
                for(Value digitValue=1; digitValue<=min(partialSum-1, 9U); digitValue++)
                {
                    partialSumToCount[partialSum] += partialSumToCount.at(partialSum-digitValue);
                }
            }
        }
        result = partialSumToCount.back();
    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountBySearchingValuesWith1And9Increment() const
{
    // Time Complexity: O(possible values * numberOfDigits)
    // Auxiliary Space: O(1)

    Count result(0);
    if(m_numberOfDigits>0)
    {
        Value start = getRaiseToPowerForIntegers(10U, m_numberOfDigits-1);
        Value end = getRaiseToPowerForIntegers(10U, m_numberOfDigits);

        for(Value value=start; value<end; value += (value==m_sumOfDigits) ? 9 : 1) // once sum is found just add 9 to find the next one
        {
            Value currentSumOfDigits=0, remainingDigits=value;
            while(remainingDigits != 0)
            {
                currentSumOfDigits += remainingDigits % 10;
                remainingDigits /= 10;
            }
            if(currentSumOfDigits == m_sumOfDigits)
            {
                result++;
            }

        }
    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingNaiveRecursion(
        Count const digitIndex,
        Value const partialSum) const
{
    Count result(0);
    if(digitIndex>0)
    {
        if(partialSum>0)
        {
            Value lastDigitValue = min(partialSum-1, 9U);
            for(Value digitValue=0; digitValue<=lastDigitValue; digitValue++)
            {
                result += getCountUsingNaiveRecursion(digitIndex-1, partialSum-digitValue);
            }
        }
        else
        {
            result = 1;
        }
    }
    else if(partialSum<=9) // 1 to 9
    {
        result = 1;
    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingMemoizationDP(
        CountMatrix & countMatrix,
        Count const digitIndex,
        Value const partialSum) const
{
    Count result(countMatrix.getEntry(digitIndex, partialSum));
    if(UNUSED_COUNT == result)
    {
        result = 0;
        if(digitIndex>0)
        {
            if(partialSum>0)
            {
                Value lastDigitValue = min(partialSum-1, 9U);
                for(Value digitValue=0; digitValue<=lastDigitValue; digitValue++)
                {
                    result += getCountUsingMemoizationDP(countMatrix, digitIndex-1, partialSum-digitValue);
                }
            }
            else
            {
                result = 1;
            }
        }
        else if(partialSum<=9) // 1 to 9
        {
            result = 1;
        }
        countMatrix.setEntry(digitIndex, partialSum, result);
    }
    return result;
}

}
