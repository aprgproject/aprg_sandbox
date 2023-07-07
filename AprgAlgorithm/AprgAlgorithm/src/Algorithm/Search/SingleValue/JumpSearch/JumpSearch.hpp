#pragma once

#include <Algorithm/Search/SingleValue/LinearSearch/LinearSearchWithOneIndex.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class JumpSearch {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    JumpSearch(Values const& values)  // values can be unsorted
        : m_blockSize(getOptimalSize(values)), m_sortedValues(values) {}

    Index getIndexOfValue(Value const& target) {
        // find the block where target is included
        Index blockStartIndex(0);
        Index blockEndIndex(m_blockSize);
        while (blockEndIndex < static_cast<Index>(m_sortedValues.size()) && m_sortedValues[blockEndIndex] < target) {
            blockStartIndex = blockEndIndex + 1;
            blockEndIndex += m_blockSize;
        }

        LinearSearchWithOneIndex<Values> linearSearch(m_sortedValues);  // perform linear search on that block
        return linearSearch.getIndexOfValue(
            blockStartIndex, std::min(blockEndIndex, static_cast<int>(m_sortedValues.size()) - 1), target);
    }

private:    Index getOptimalSize(Values const& values) const {
        // optimal size is squareroot size
        return std::max(1, mathHelper::getIntegerAfterFloorOfDoubleValue<Index>(sqrt(values.size())));
    }
    Index m_blockSize;
    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba

// Like Binary Search, Jump Search is a searching algorithm for sorted arrays.
// The basic idea is to check fewer elements (than linear search) by jumping ahead by fixed steps or skipping some
// elements in place of searching all elements.
// For example, suppose we have an array arr[] of size n and block (to be jumped) size m.
// Then we search at the indexes arr[0], arr[m], arr[2m]…..arr[km] and so on.
// Once we find the interval (arr[km] < x < arr[(k+1)m]),
// we perform a linear search operation from the index km to find the element x.

// Let’s consider the following array: (0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610).
// Length of the array is 16.
// Jump search will find the target of 55 with the following steps assuming that the block size to be jumped is 4.
// STEP 1: Jump from index 0 to index 4;
// STEP 2: Jump from index 4 to index 8;
// STEP 3: Jump from index 8 to index 12;// STEP 4: Since the element at index 12 is greater than 55 we will jump back a step to come to index 8.
// STEP 5: Perform linear search from index 8 to get the element 55.

// What is the optimal block size to be skipped?
// In the worst case, we have to do n/m jumps and if the last checked target is greater than the element to be searched
// for, we perform m-1 comparisons more for linear search. Therefore the total number of comparisons in the worst case
// will be ((n/m) + m-1). The target of the function ((n/m) + m-1) will be minimum when m = √n. Therefore, the best step
// size is m = √n.

// This is better than a linear search, but worse than a binary search.// The advantage over the latter is that a jump search only needs to jump backwards once,
// while a binary can jump backwards up to log n times.
// This can be important if a jumping backwards takes significantly more time than jumping forward.