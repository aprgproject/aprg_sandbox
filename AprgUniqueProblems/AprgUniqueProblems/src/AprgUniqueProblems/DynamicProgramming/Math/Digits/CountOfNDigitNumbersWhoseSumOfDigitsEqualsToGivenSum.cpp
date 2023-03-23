#include "CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum.hpp"

#include <Common/Math/Helpers/PowerHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum(
        Count const numberOfDigits,
        Value const sumOfDigits)
    : m_numberOfDigits(numberOfDigits)
    , m_targetSumOfDigits(sumOfDigits)
{}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingNaiveRecursion() const
{
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(2^n)
    // Auxiliary Space: Constant

    Count result(0);
    if(m_numberOfDigits>0)
    {
        result = getCountUsingNaiveRecursion(m_targetSumOfDigits, m_numberOfDigits-1);
    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingMemoizationDP() const
{
    // Time Complexity: O(numberOfDigits * sumOfDigits * 9) (same as iterative)
    // Auxiliary Space: O(numberOfDigits * sumOfDigits)

    Count result(0);
    if(m_numberOfDigits>0)
    {
        CountMatrix countMatrix(m_targetSumOfDigits+1, m_numberOfDigits, UNUSED_COUNT);
        result = getCountUsingMemoizationDP(countMatrix, m_targetSumOfDigits, m_numberOfDigits-1);    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingIterativeDP() const
{
    // Time Complexity: O(numberOfDigits * sumOfDigits * 9)
    // Auxiliary Space: O(numberOfDigits * sumOfDigits)

    Count result(0);
    if(m_numberOfDigits>0)
    {        CountMatrix countMatrix(m_targetSumOfDigits+1, m_numberOfDigits, 0U);

        for(Value digitValue=0; digitValue<=min(m_targetSumOfDigits, 9U); digitValue++)
        {
            countMatrix.setEntry(digitValue, 0, 1);
        }
        for(Count digitIndex=1; digitIndex<m_numberOfDigits; digitIndex++)
        {
            countMatrix.setEntry(0, digitIndex, 1);
            for(Value partialSum=1; partialSum<=m_targetSumOfDigits; partialSum++)
            {
                for(Value digitValue=0; digitValue<=min(partialSum-1, 9U); digitValue++)
                {
                    countMatrix.getEntryReference(partialSum, digitIndex) += countMatrix.getEntry(partialSum-digitValue, digitIndex-1);
                }
            }
        }
        result = countMatrix.getEntry(countMatrix.getNumberOfColumns()-1, countMatrix.getNumberOfRows()-1);
    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingIterativeDPAndSpaceEfficient() const
{
    // Time Complexity: O(numberOfDigits * sumOfDigits * 9)
    // Auxiliary Space: O(sumOfDigits)

    Count result(0);
    if(m_numberOfDigits>0)
    {        Counts partialSumToCount(m_targetSumOfDigits+1);
        for(Value digitValue=0; digitValue<=min(m_targetSumOfDigits, 9U); digitValue++)
        {
            partialSumToCount[digitValue]=1;
        }
        for(Count digitIndex=1; digitIndex<m_numberOfDigits; digitIndex++)
        {
            for(Value partialSum=m_targetSumOfDigits; partialSum>0; partialSum--)
            {
                for(Value digitValue=1; digitValue<=min(partialSum-1, 9U); digitValue++) // When digitValue==0, the count is 1, so no need to process
                {
                    partialSumToCount[partialSum] += partialSumToCount.at(partialSum-digitValue);
                }
            }
        }
        result = partialSumToCount.back();
    }    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountBySearchingValuesWith1And9Increment() const
{
    // Time Complexity: O(possible values * numberOfDigits)
    // Auxiliary Space: O(1)

    Count result(0);
    if(m_targetSumOfDigits==0)
    {
        result = 1;
    }
    else if(m_numberOfDigits>0)
    {
        Value start = getRaiseToPowerForIntegers(10U, m_numberOfDigits-1);
        Value end = getRaiseToPowerForIntegers(10U, m_numberOfDigits);

        for(Value value=start; value<end; value += (value==m_targetSumOfDigits) ? 9 : 1) // once sum is found just add 9 to find the next one
        {
            Value currentSumOfDigits=0, remainingDigits=value;            while(remainingDigits != 0)
            {
                currentSumOfDigits += remainingDigits % 10;
                remainingDigits /= 10;
            }
            if(currentSumOfDigits == m_targetSumOfDigits)
            {
                result++;
            }

        }
    }
    return result;
}

CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::Count CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum::getCountUsingNaiveRecursion(
        Value const partialSum,
        Count const digitIndex) const
{
    Count result(0);
    if(digitIndex>0)
    {
        if(partialSum>0)
        {
            Value lastDigitValue = min(partialSum-1, 9U);
            for(Value digitValue=0; digitValue<=lastDigitValue; digitValue++)
            {
                result += getCountUsingNaiveRecursion(partialSum-digitValue, digitIndex-1);
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
        Value const partialSum,
        Count const digitIndex) const
{
    Count result(countMatrix.getEntry(partialSum, digitIndex));
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
                    result += getCountUsingMemoizationDP(countMatrix, partialSum-digitValue, digitIndex-1);
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
        countMatrix.setEntry(partialSum, digitIndex, result);
    }
    return result;
}

}
