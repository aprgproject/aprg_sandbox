#include "CountNumberOfBinaryStringsWithoutConsecutiveOnes.hpp"

#include <Math/NumberTheory/OtherUtilities.hpp>

using namespace alba::math;
using namespace std;

namespace alba
{

CountNumberOfBinaryStringsWithoutConsecutiveOnes::CountNumberOfBinaryStringsWithoutConsecutiveOnes(
        Count const length)
    : m_length(length)
{}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingNaiveRecursion() const
{
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(2^n)
    // Auxiliary Space: Constant

    return getCountUsingNaiveRecursion(false, m_length);
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingTabularDP() const
{
    // Time Complexity: O(n)
    // Auxiliary Space: O(n)

    Count result(0);
    if(m_length>0)
    {
        CountMatrix valueMatrix(2, m_length, 0);
        valueMatrix.setEntry(0, 0, 1);
        valueMatrix.setEntry(1, 0, 1);
        for(Count index=1; index<m_length; index++)
        {
            Count previousZeroCount = valueMatrix.getEntry(0, index-1);
            Count previousOneCount = valueMatrix.getEntry(1, index-1);
            valueMatrix.setEntry(0, index, previousZeroCount+previousOneCount);
            valueMatrix.setEntry(1, index, previousZeroCount);
        }
        result = valueMatrix.getEntry(0, valueMatrix.getNumberOfRows()-1) + valueMatrix.getEntry(1, valueMatrix.getNumberOfRows()-1); // add last zero and one
    }
    return result;
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingTabularDPAndSpaceEfficient() const
{
    // Time Complexity: O(n)
    // Auxiliary Space: O(1)

    Count result(0);
    if(m_length>0)
    {
        Count zeroCount = 1;
        Count oneCount = 1;
        for(Count subLength=1; subLength<m_length; subLength++)
        {
            Count nextZeroCount = zeroCount+oneCount;
            oneCount = zeroCount;
            zeroCount = nextZeroCount;
        }
        result = zeroCount+oneCount;  // add last zero and one
    }
    return result;
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingFibonacci() const
{
    // Time Complexity: O(1) (depends on how fibonacci number is computed)
    // Auxiliary Space: O(1)

    Count result(0);
    if(m_length>0)
    {
        result = getNthFibonacciNumberUsingBinetsFormula(m_length+2);
    }
    return result;
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingMultipleReturns() const
{
    if(m_length%2 == 0)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingSingleReturn() const
{
    Count result(3);
    if(m_length%2 == 0)
    {
        result = 2;
    }
    return result;
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingTernaryReturn() const
{
    return (m_length%2 == 0) ? 2 : 3;
}

CountNumberOfBinaryStringsWithoutConsecutiveOnes::Count CountNumberOfBinaryStringsWithoutConsecutiveOnes::getCountUsingNaiveRecursion(
        bool const previousValue,
        Count const length) const{
    if(length > 0)
    {
        if(previousValue)        {
            return getCountUsingNaiveRecursion(false, length-1);
        }
        else
        {
            return getCountUsingNaiveRecursion(false, length-1) + getCountUsingNaiveRecursion(true, length-1);
        }
    }
    else
    {
        return 1U;
    }
}

}
