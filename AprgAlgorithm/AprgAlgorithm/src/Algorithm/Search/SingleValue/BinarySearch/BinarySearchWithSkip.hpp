#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class BinarySearchWithSkip {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinarySearchWithSkip(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Index getIndexOfValue(Value const& value) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            Index possibleIndex(getIndexUsingForwardSkip(value));
            if (m_sortedValues[possibleIndex] == value) {
                result = possibleIndex;
            }
        }        return result;
    }

private:    Index getIndexUsingForwardSkip(Value const& value) const {
        Index result(0);
        Index size(m_sortedValues.size());
        for (Index forwardSkip = size / 2; forwardSkip >= 1;
             forwardSkip /=
             2)  // forward skip start from half of size, then quarter of size, then eighth of size and so on
        {
            while (result + forwardSkip < size &&
                   m_sortedValues[result + forwardSkip] <
                       value)  // less than condition to avoid redundant traversal on equal values
            {
                result += forwardSkip;            }
        }
        result += (result + 1 < static_cast<Index>(m_sortedValues.size())) ? 1 : 0;  // move one for equal
        return result;    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba

// An alternative method to implement binary search is based on an efficient way to iterate through the elements of the
// array. The idea is to make jumps and slow the speed when we get closer to the target element.

// The search goes through the array from left to right, and the initial jump length is n/2.
// At each step, the jump length will be halved: first n/4, then n/8, n/16, etc., until finally the length is 1.
// After the jumps, either the target element has been found or we know that it does not appear in the array.

// During the search, the variable b contains the current jump length.
// The time complexity of the algorithm is O(logn), because the code in the while loop is performed at most twice for
// each jump length.
