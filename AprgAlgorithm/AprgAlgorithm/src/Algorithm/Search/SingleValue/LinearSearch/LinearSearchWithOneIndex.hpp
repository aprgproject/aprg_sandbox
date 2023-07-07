#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>
class LinearSearchWithOneIndex {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    LinearSearchWithOneIndex(Values const& values)  // values can be unsorted
        : m_values(values) {}

    Index getIndexOfValue(Value const& target) const {
        Index result(INVALID_INDEX);
        if (!m_values.empty()) {
            result = getIndexOfValueWithoutCheck(0, m_values.size() - 1, target);
        }
        return result;
    }

    Index getIndexOfValue(Index const startIndex, Index const endIndex, Value const& target) const {
        Index result(INVALID_INDEX);
        if (startIndex < static_cast<Index>(m_values.size()) && endIndex < static_cast<Index>(m_values.size()) &&
            startIndex <= endIndex) {
            result = getIndexOfValueWithoutCheck(startIndex, endIndex, target);
        }
        return result;
    }

private:
    Index getIndexOfValueWithoutCheck(Index const startIndex, Index const endIndex, Value const& target) const {
        Index result(INVALID_INDEX);
        auto it = std::find(m_values.cbegin() + startIndex, m_values.cbegin() + endIndex + 1, target);
        if (it != m_values.cbegin() + endIndex + 1) {
            result = std::distance(m_values.cbegin(), it);
        }
        return result;
    }

    Values const& m_values;
};

}  // namespace algorithm

}  // namespace alba

// A simple approach is to do a linear search, i.e
// -> Start from the leftmost element of arr[] and one by one compare x with each element of arr[]
// -> If x matches with an element, return the index.
// -> If x doesn’t match with any of elements, return -1.

// The time complexity of the above algorithm is O(n).
// Linear search is rarely used practically because other search algorithms such as
// the binary search algorithm and hash tables allow significantly faster-searching comparison to linear search.
