#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>

#include <iterator>

namespace alba {

namespace algorithm {

template <typename Values>
class LinearSearchWithTwoIndices {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    LinearSearchWithTwoIndices(Values const& values)  // values can be unsorted
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
        for (auto itLower = m_values.cbegin() + startIndex, itHigher = m_values.cbegin() + endIndex;
             itLower <= itHigher; itLower++, itHigher--) {
            Value valueAtLower = *itLower;
            Value valueAtHigher = *itHigher;
            if (valueAtLower == target) {
                result = std::distance(m_values.cbegin(), itLower);
                break;
            } else if (valueAtHigher == target) {
                result = std::distance(m_values.cbegin(), itHigher);
                break;
            }
            if (itLower == itHigher) {
                break;
            }
        }
        return result;
    }
    Values const& m_values;
};

}  // namespace algorithm

}  // namespace alba

// Improve Linear Search Worst-Case Complexity
// if element Found at last  O(n) to O(1)
// if element Not found O(n) to O(n/2) so still O(n)
