#pragma once

#include <Algorithm/Search/SingleValue/BinarySearch/BinarySearchWithTwoIndices.hpp>

#include <limits>

namespace alba
{

namespace algorithm
{

template <typename Values>
class ExponentialSearch
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = std::numeric_limits<Index>::max();

    ExponentialSearch(Values const& values) // values can be unsorted
        : m_values(values)
    {}

    Value getNearestValue(Value const& valueToCheck)
    {
        Value result{};
        Index selectedIndex(getIndexOfNearestValue(valueToCheck));
        if(selectedIndex != INVALID_INDEX)
        {
            result = m_values.at(selectedIndex);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& valueToCheck)
    {
        Index result(INVALID_INDEX);

        if(!m_values.empty())
        {
            if(m_values.front() == valueToCheck)
            {
                result = 0U;
            }
            else
            {
                Index endIndex = 1U;
                while(endIndex < m_values.size() && m_values.at(endIndex) <= valueToCheck)
                {
                    endIndex *= 2U;
                }
                BinarySearchWithTwoIndices<Values> binarySearch(1U, endIndex, m_values); // perform linear search on that block
                result = binarySearch.getIndexOfNearestValue(valueToCheck);
            }
        }

        return result;
    }

private:

    Values const& m_values;
};

}

}

// The name of this searching algorithm may be misleading as it works in O(Log n) time.
// The name comes from the way it searches an element.
// Exponential search involves two steps:
// -> Step 1: Find range where element is present
// -> Step 2: Do Binary Search in above found range.

// How to find the range where element may be present?
// The idea is to start with subarray size 1, compare its last element with x, then try size 2, then 4 and so on until last element of a subarray is not greater.
// Once we find an index i (after repeated doubling of i),
// we know that the element must be present between i/2 and i (Why i/2? because we could not find a greater value in previous iteration)

// Time Complexity : O(Log n)
// Auxiliary Space : The above implementation of Binary Search is recursive and requires O(Log n) space.
// With iterative Binary Search, we need only O(1) space.
// Applications of Exponential Search:
// -> Exponential Binary Search is particularly useful for unbounded searches, where size of array is infinite.
// Please refer Unbounded Binary Search for an example.
// -> It works better than Binary Search for bounded arrays, and also when the element to be searched is closer to the first element.

