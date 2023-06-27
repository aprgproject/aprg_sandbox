#pragma once

namespace alba {

namespace algorithm {

template <typename Values>
class CountOnesInASortedBinaryContainer {
public:
    using Count = int;
    using Index = int;
    using Value = typename Values::value_type;

    CountOnesInASortedBinaryContainer() = default;

    Count getNumberOfOnesInASortedBinaryContainer(Values const& sortedBinaryValues) {
        Count result(0);
        if (!sortedBinaryValues.empty()) {
            Index lowerIndex(0), higherIndex(sortedBinaryValues.size() - 1);
            while (lowerIndex < higherIndex) {
                Index middleIndex = (lowerIndex + higherIndex) / 2;
                if (sortedBinaryValues[middleIndex]) {
                    result = sortedBinaryValues.size() - middleIndex;
                    higherIndex = middleIndex - 1;
                } else {
                    lowerIndex = middleIndex + 1;
                }
            }
            if (sortedBinaryValues[lowerIndex]) {
                result = sortedBinaryValues.size() - lowerIndex;
            }
        }        return result;
    }

    //    Implementation using FindSmallestValueWithTrue    //    Index getNumberOfOnesInASortedBinaryContainer(Values const& sortedBinaryValues)
    //    {
    //        Index result(0);
    //        if(!sortedBinaryValues.empty())
    //        {
    //            FindSmallestValueWithTrue<Index> query([&](Index const index) -> bool // this is binary search
    //            {
    //                return sortedBinaryValues[index];
    //            });
    //            Index smallestOneIndex = query.getSmallestValueWithTrue(0, sortedBinaryValues.size()-1);
    //            if(sortedBinaryValues[smallestOneIndex])
    //            {
    //                result = sortedBinaryValues.size() - smallestOneIndex;
    //            }    //        }
    //        return result;
    //    }
};
}  // namespace algorithm

}  // namespace alba

// Given a binary array sorted in non-increasing order, count the number of 1’s in it.

// We can use Binary Search to find count in O(Logn) time.
// The idea is to look for last occurrence of 1 using Binary Search.
