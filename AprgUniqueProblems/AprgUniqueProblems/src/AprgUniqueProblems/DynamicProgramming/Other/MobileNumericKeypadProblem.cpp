#include "MobileNumericKeypadProblem.hpp"

#include <Math/NumberTheory/OtherUtilities.hpp>

using namespace alba::math;
using namespace std;

namespace alba
{

MobileNumericKeypadProblem::MobileNumericKeypadProblem(
        Count const length)
    : m_length(length)
{}

MobileNumericKeypadProblem::Count MobileNumericKeypadProblem::getCountUsingNaiveRecursion() const
{
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(5^n) (5 is maximum recursion calls in one function call)
    // Auxiliary Space: Constant

    Count result(0);
    for(NumpadValue numpadValue=0; numpadValue<=9; numpadValue++)
    {
        result += getCountForValueUsingNaiveRecursion(m_length, numpadValue);
    }
    return result;
}

MobileNumericKeypadProblem::Count MobileNumericKeypadProblem::getCountUsingMemoizationDP() const
{
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(5^n) (5 is maximum recursion calls in one function call)
    // Auxiliary Space: Constant

    Count result(0);
    CountMatrix countMatrix(m_length+1, 10, UNUSED_VALUE);
    for(NumpadValue numpadValue=0; numpadValue<=9; numpadValue++)
    {
        result += getCountForValueUsingMemoizationDP(countMatrix, m_length, numpadValue);
    }
    return result;
}

MobileNumericKeypadProblem::Count MobileNumericKeypadProblem::getCountUsingIterativeDP() const
{
    // Time Complexity: O(n*d)
    // Auxiliary Space: O(n*d)
    Count result(0);
    if(m_length>0)
    {
        CountMatrix countMatrix(m_length, 10);
        for(NumpadValue numpadValue=0; numpadValue<=9; numpadValue++)
        {
            countMatrix.setEntry(0, numpadValue, 1);
        }
        for(Count lengthMinus1=1; lengthMinus1<m_length; lengthMinus1++)
        {
            Count previousLengthMinus1 = lengthMinus1-1;
            countMatrix.setEntry(lengthMinus1, 0, countMatrix.getEntry(previousLengthMinus1, 0) + countMatrix.getEntry(previousLengthMinus1, 8));
            countMatrix.setEntry(lengthMinus1, 1, countMatrix.getEntry(previousLengthMinus1, 1) + countMatrix.getEntry(previousLengthMinus1, 2) + countMatrix.getEntry(previousLengthMinus1, 4));
            countMatrix.setEntry(lengthMinus1, 2, countMatrix.getEntry(previousLengthMinus1, 2) + countMatrix.getEntry(previousLengthMinus1, 1) + countMatrix.getEntry(previousLengthMinus1, 3) + countMatrix.getEntry(previousLengthMinus1, 5));
            countMatrix.setEntry(lengthMinus1, 3, countMatrix.getEntry(previousLengthMinus1, 3) + countMatrix.getEntry(previousLengthMinus1, 2) + countMatrix.getEntry(previousLengthMinus1, 6));
            countMatrix.setEntry(lengthMinus1, 4, countMatrix.getEntry(previousLengthMinus1, 4) + countMatrix.getEntry(previousLengthMinus1, 1) + countMatrix.getEntry(previousLengthMinus1, 5) + countMatrix.getEntry(previousLengthMinus1, 7));
            countMatrix.setEntry(lengthMinus1, 5, countMatrix.getEntry(previousLengthMinus1, 5) + countMatrix.getEntry(previousLengthMinus1, 2) + countMatrix.getEntry(previousLengthMinus1, 4) + countMatrix.getEntry(previousLengthMinus1, 6) + countMatrix.getEntry(previousLengthMinus1, 8));
            countMatrix.setEntry(lengthMinus1, 6, countMatrix.getEntry(previousLengthMinus1, 6) + countMatrix.getEntry(previousLengthMinus1, 3) + countMatrix.getEntry(previousLengthMinus1, 5) + countMatrix.getEntry(previousLengthMinus1, 6));
            countMatrix.setEntry(lengthMinus1, 7, countMatrix.getEntry(previousLengthMinus1, 7) + countMatrix.getEntry(previousLengthMinus1, 4)  + countMatrix.getEntry(previousLengthMinus1, 8));
            countMatrix.setEntry(lengthMinus1, 8, countMatrix.getEntry(previousLengthMinus1, 8) + countMatrix.getEntry(previousLengthMinus1, 5) + countMatrix.getEntry(previousLengthMinus1, 7) + countMatrix.getEntry(previousLengthMinus1, 9) + countMatrix.getEntry(previousLengthMinus1, 0));
            countMatrix.setEntry(lengthMinus1, 9, countMatrix.getEntry(previousLengthMinus1, 9) + countMatrix.getEntry(previousLengthMinus1, 6) + countMatrix.getEntry(previousLengthMinus1, 8));
        }
        for(NumpadValue numpadValue=0; numpadValue<=9; numpadValue++)
        {
            result += countMatrix.getEntry(m_length-1, numpadValue);
        }
    }
    return result;
}

MobileNumericKeypadProblem::Count MobileNumericKeypadProblem::getCountUsingIterativeDPAndSpaceEfficient() const
{
    // Time Complexity: O(n*d)
    // Auxiliary Space: O(d)
    Count result(0);
    if(m_length>0)
    {
        vector<Counts> previousAndCurrentCounts(2, NumpadValues(10U, 1U));
        for(Count lengthMinus1=1; lengthMinus1<m_length; lengthMinus1++)
        {
            Counts & previousCounts(previousAndCurrentCounts[(lengthMinus1-1)%2]);
            Counts & currentCounts(previousAndCurrentCounts[lengthMinus1%2]);

            currentCounts[0] = previousCounts.at(0) + previousCounts.at(8);
            currentCounts[1] = previousCounts.at(1) + previousCounts.at(2) + previousCounts.at(4);
            currentCounts[2] = previousCounts.at(2) + previousCounts.at(1) + previousCounts.at(3) + previousCounts.at(5);
            currentCounts[3] = previousCounts.at(3) + previousCounts.at(2) + previousCounts.at(6);
            currentCounts[4] = previousCounts.at(4) + previousCounts.at(1) + previousCounts.at(5) + previousCounts.at(7);
            currentCounts[5] = previousCounts.at(5) + previousCounts.at(2) + previousCounts.at(4) + previousCounts.at(6) + previousCounts.at(8);
            currentCounts[6] = previousCounts.at(6) + previousCounts.at(3) + previousCounts.at(5) + previousCounts.at(6);
            currentCounts[7] = previousCounts.at(7) + previousCounts.at(4)  + previousCounts.at(8);
            currentCounts[8] = previousCounts.at(8) + previousCounts.at(5) + previousCounts.at(7) + previousCounts.at(9) + previousCounts.at(0);
            currentCounts[9] = previousCounts.at(9) + previousCounts.at(6) + previousCounts.at(8);
        }

        Counts const& lastCurrent(previousAndCurrentCounts.at((m_length-1)%2));
        for(NumpadValue numpadValue=0; numpadValue<=9; numpadValue++)
        {
            result += lastCurrent.at(numpadValue);
        }
    }
    return result;
}

MobileNumericKeypadProblem::Count MobileNumericKeypadProblem::getCountForValueUsingNaiveRecursion(
        Count const length,
        NumpadValue const numpadValue) const
{
    Count result(0);
    if(length > 1)
    {
        Count lengthMinus1 = length-1;
        switch(numpadValue)
        {
        case 0:
            result =  getCountForValueUsingNaiveRecursion(lengthMinus1, 0)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 8);
            break;
        case 1:
            result =  getCountForValueUsingNaiveRecursion(lengthMinus1, 1)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 2)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 4);
            break;
        case 2:
            result = getCountForValueUsingNaiveRecursion(lengthMinus1, 2)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 1)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 3)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 5);
            break;
        case 3:
            result = getCountForValueUsingNaiveRecursion(lengthMinus1, 3)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 2)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 6);
            break;
        case 4:
            result = getCountForValueUsingNaiveRecursion(lengthMinus1, 4)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 1)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 5)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 7);
            break;
        case 5:
            result = getCountForValueUsingNaiveRecursion(lengthMinus1, 5)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 2)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 4)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 6)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 8);
            break;
        case 6:
            result = getCountForValueUsingNaiveRecursion(lengthMinus1, 6)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 3)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 5)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 6);
            break;
        case 7:
            result = getCountForValueUsingNaiveRecursion(lengthMinus1, 7)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 4)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 8);
            break;
        case 8:
            result = getCountForValueUsingNaiveRecursion(lengthMinus1, 8)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 5)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 7)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 9)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 0);
            break;
        case 9:
            result = getCountForValueUsingNaiveRecursion(lengthMinus1, 9)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 6)
                    + getCountForValueUsingNaiveRecursion(lengthMinus1, 8);
            break;
        default:
            break;
        }
    }
    else if(length == 1)
    {
        result = 1;
    }
    return result;
}

MobileNumericKeypadProblem::Count MobileNumericKeypadProblem::getCountForValueUsingMemoizationDP(
        CountMatrix & countMatrix,
        Count const length,
        NumpadValue const numpadValue) const
{
    Count result(countMatrix.getEntry(length, numpadValue));
    if(UNUSED_VALUE == result)
    {
        result = 0;
        if(length > 1)
        {
            Count lengthMinus1 = length-1;
            switch(numpadValue)
            {
            case 0:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 0)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 8);
                break;
            case 1:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 1)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 2)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 4);
                break;
            case 2:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 2)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 1)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 3)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 5);
                break;
            case 3:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 3)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 2)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 6);
                break;
            case 4:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 4)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 1)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 5)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 7);
                break;
            case 5:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 5)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 2)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 4)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 6)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 8);
                break;
            case 6:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 6)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 3)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 5)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 6);
                break;
            case 7:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 7)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 4)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 8);
                break;
            case 8:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 8)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 5)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 7)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 9)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 0);
                break;
            case 9:
                result = getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 9)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 6)
                        + getCountForValueUsingMemoizationDP(countMatrix, lengthMinus1, 8);
                break;
            default:
                break;
            }
        }
        else if(length == 1)
        {
            result = 1;
        }
        countMatrix.setEntry(length, numpadValue, result);
    }
    return result;
}

}
