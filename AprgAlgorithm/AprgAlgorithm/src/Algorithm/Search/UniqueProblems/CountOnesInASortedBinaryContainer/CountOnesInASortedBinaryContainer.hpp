#pragma once

#include <Algorithm/Search/UniqueProblems/FindSmallestValueWithTrue/FindSmallestValueWithTrue.hpp>
#include <Algorithm/Utilities/InvalidIndex.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class CountOnesInASortedBinaryContainer
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    CountOnesInASortedBinaryContainer()
    {}

    Index getNumberOfOnesInASortedBinaryContainer(Values const& sortedBinaryValues)
    {
        Index result(0U);
        if(!sortedBinaryValues.empty())
        {
            FindSmallestValueWithTrue<Index> query([&](Index const index) -> bool // this is binary search
            {
                return sortedBinaryValues.at(index);
            });
            Index index = query.getSmallestValueWithTrue(0U, sortedBinaryValues.size()-1U);
            if(sortedBinaryValues.at(index))
            {
                result = sortedBinaryValues.size() - index;
            }
        }
        return result;
    }
};

}

}

// Given a binary array sorted in non-increasing order, count the number of 1’s in it.

// We can use Binary Search to find count in O(Logn) time.
// The idea is to look for last occurrence of 1 using Binary Search.

