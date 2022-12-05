#pragma once

#include <Algorithm/Search/NearestValue/BinarySearch/BinarySearchWithTwoIndices.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class FindKClosestElements
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    using IndexPair = std::pair<Index, Index>;
    static constexpr Index INVALID_INDEX = std::numeric_limits<Index>::max();

    FindKClosestElements(Values const& values) // values can be unsorted
        : m_values(values)
    {}

    IndexPair getIndexPairClosestElements(
            unsigned int const numberOfClosestElements,
            Value const& valueToCheck)
    {
        IndexPair result{INVALID_INDEX, INVALID_INDEX};

        BinarySearchWithTwoIndices<Values> binarySearch(m_values);
        Index nearestIndex(binarySearch.getIndexOfNearestValue(valueToCheck));
        if(nearestIndex != INVALID_INDEX)
        {
            Index count(1U);
            Index low(nearestIndex), high(nearestIndex);
            while(count < numberOfClosestElements && low>0U && high+1U<m_values.size())
            {
                if(valueToCheck-m_values.at(low) <= m_values.at(high)-valueToCheck)
                {
                    low--;
                }
                else
                {
                    high++;
                }
                count++;
            }
            while(count < numberOfClosestElements && low>0U)
            {
                low--;
                count++;
            }
            while(count < numberOfClosestElements && high+1U<m_values.size())
            {
                high++;
                count++;
            }
            result = {low, high};
        }
        return result;
    }

private:

    Values const& m_values;
};

}

}

// Given a sorted array arr[] and a value X, find the k closest elements to X in arr[].
// Examples:
// Input: K = 4, X = 35
// arr[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56}
// Output: 30 39 42 45

// Note that if the element is present in array, then it should not be in output, only the other closest elements are required.
