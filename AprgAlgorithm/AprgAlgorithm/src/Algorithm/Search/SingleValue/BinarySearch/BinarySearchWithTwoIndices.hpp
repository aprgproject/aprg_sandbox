#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class BinarySearchWithTwoIndices
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinarySearchWithTwoIndices(Values const& sortedValues)
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
        if(startIndex < m_sortedValues.size() && endIndex < m_sortedValues.size())
        {
            result = getIndexOfValueWithoutCheck(startIndex, endIndex, value);
        }
        return result;
    }

private:

    Index getIndexOfValueWithoutCheck(Index const startIndex, Index const endIndex, Value const& value) const
    {
        Index result(INVALID_INDEX);
        Index lowerIndex(startIndex), higherIndex(endIndex);
        while(lowerIndex<=higherIndex)
        {
            Index middleIndex = (lowerIndex+higherIndex)/2;
            Value middleValue(m_sortedValues.at(middleIndex));
            if(value == middleValue)
            {
                result = middleIndex;
                break;
            }
            else if(value < middleValue)
            {
                higherIndex = middleIndex-1;
            }
            else if(middleValue < value)
            {
                lowerIndex = middleIndex+1;
            }
        }
        return result;
    }

    Values const& m_sortedValues;
};

}

}

// The usual way to implement binary search resembles looking for a word in a dictionary.
// The search maintains an active region in the array, which initially contains all array elements.
// Then, a number of steps is performed, each of which halves the size of the region.

// At each step, the search checks the middle element of the active region.
// If the middle element is the target element, the search terminates.
// Otherwise, the search recursively continues to the left or right half of the region, depending on the value of the middle element.

// In this implementation, the active region is a...b, and initially the region is 0...n-1.
// The algorithm halves the size of the region at each step, so the time complexity is O(logn).
