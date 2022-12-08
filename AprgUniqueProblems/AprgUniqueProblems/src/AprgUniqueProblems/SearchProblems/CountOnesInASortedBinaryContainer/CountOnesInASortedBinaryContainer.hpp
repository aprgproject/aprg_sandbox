#pragma once

namespace alba
{

namespace algorithm
{

template <typename Values>
class CountOnesInASortedBinaryContainer
{
public:
    using Count = unsigned int;
    using Index = unsigned int;
    using Value = typename Values::value_type;

    CountOnesInASortedBinaryContainer() = default;

    Count getNumberOfOnesInASortedBinaryContainer(Values const& sortedBinaryValues)
    {
        Count result(0U);
        if(!sortedBinaryValues.empty())
        {
            Index lowerIndex(0U), higherIndex(sortedBinaryValues.size()-1);
            while(lowerIndex<higherIndex)
            {
                Index middleIndex = (lowerIndex+higherIndex)/2;
                if(sortedBinaryValues.at(middleIndex))
                {
                    result = sortedBinaryValues.size() - middleIndex;
                    higherIndex = middleIndex-1;
                }
                else
                {
                    lowerIndex = middleIndex+1;
                }
            }
            if(sortedBinaryValues.at(lowerIndex))
            {
                result = sortedBinaryValues.size() - lowerIndex;
            }
        }
        return result;
    }


//    Implementation using FindSmallestValueWithTrue
//    Index getNumberOfOnesInASortedBinaryContainer(Values const& sortedBinaryValues)
//    {
//        Index result(0U);
//        if(!sortedBinaryValues.empty())
//        {
//            FindSmallestValueWithTrue<Index> query([&](Index const index) -> bool // this is binary search
//            {
//                return sortedBinaryValues.at(index);
//            });
//            Index smallestOneIndex = query.getSmallestValueWithTrue(0U, sortedBinaryValues.size()-1U);
//            if(sortedBinaryValues.at(smallestOneIndex))
//            {
//                result = sortedBinaryValues.size() - smallestOneIndex;
//            }
//        }
//        return result;
//    }
};

}

}

// Given a binary array sorted in non-increasing order, count the number of 1’s in it.

// We can use Binary Search to find count in O(Logn) time.
// The idea is to look for last occurrence of 1 using Binary Search.

