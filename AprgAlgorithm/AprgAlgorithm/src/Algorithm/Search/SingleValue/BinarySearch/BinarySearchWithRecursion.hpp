#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class BinarySearchWithRecursion
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinarySearchWithRecursion(Values const& sortedValues)
        : m_sortedValues(sortedValues)
    {}

    Index getIndexOfValue(Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            result = getIndexOfValueWithoutCheck(0U, m_sortedValues.size()-1, value);
        }
        return result;
    }

    Index getIndexOfValue(Index const startIndex, Index const endIndex, Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(startIndex < m_sortedValues.size() && endIndex < m_sortedValues.size() && startIndex <= endIndex)
        {
            result = getIndexOfValueWithoutCheck(startIndex, endIndex, value);
        }
        return result;
    }

private:

    Index getIndexOfValueWithoutCheck(Index const lowerIndex, Index const higherIndex, Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(lowerIndex<=higherIndex)
        {
            Index middleIndex = (lowerIndex+higherIndex)/2;
            Value middleValue(m_sortedValues.at(middleIndex));
            if(value == middleValue)
            {
                result = middleIndex;
            }
            else if(value < middleValue)
            {
                if(middleIndex > 0U)
                {
                    result = getIndexOfValueWithoutCheck(lowerIndex, middleIndex-1, value);
                }
            }
            else // middleValue < value
            {
                result = getIndexOfValueWithoutCheck(middleIndex+1, higherIndex, value);
            }
        }
        return result;
    }

    Values const& m_sortedValues;
};

}

}

// Binary Search: Search a sorted array by repeatedly dividing the search interval in half.
// Begin with an interval covering the whole array.
// If the value of the search key is less than the item in the middle of the interval, narrow the interval to the lower half.
// Otherwise, narrow it to the upper half. Repeatedly check until the value is found or the interval is empty.

// We basically ignore half of the elements just after one comparison.
// Compare x with the middle element.
// If x matches with the middle element, we return the mid index.
// Else If x is greater than the mid element, then x can only lie in the right half subarray after the mid element. So we recur for the right half.
// Else (x is smaller) recur for the left half.

// Time Complexity:
// The time complexity of Binary Search can be written as
// T(n) = T(n/2) + c
// The above recurrence can be solved either using the Recurrence Tree method or Master method.
// It falls in case II of the Master Method and the solution of the recurrence is Theta(Logn) .
// Auxiliary Space: O(1) in case of iterative implementation. In the case of recursive implementation, O(Logn) recursion call stack space.


// Note, its better to have:
// -> int mid = low + (high – low)/2;
// Maybe, you wonder why we are calculating the middle index this way, we can simply add the lower and higher index and divide it by 2.
// -> int mid = (low + high)/2;
// But if we calculate the middle index like this means our code is not 100% correct, it contains bugs.
// That is, it fails for larger values of int variables low and high.
// Specifically, it fails if the sum of low and high is greater than the maximum positive int value(231 – 1).
// The sum overflows to a negative value and the value stays negative when divided by 2. In java, it throws ArrayIndexOutOfBoundException.
// -> int mid = low + (high – low)/2;
// So it’s better to use it like this. This bug applies equally to merge sort and other divide and conquer algorithms.

