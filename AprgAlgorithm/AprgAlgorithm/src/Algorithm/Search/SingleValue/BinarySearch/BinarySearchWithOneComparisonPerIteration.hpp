#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class BinarySearchWithOneComparisonPerIteration {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinarySearchWithOneComparisonPerIteration(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Index getIndexOfValue(Value const& value) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfValueWithoutCheck(0, m_sortedValues.size() - 1, value);
        }
        return result;
    }

    Index getIndexOfValue(Index const startIndex, Index const endIndex, Value const& value) const {
        Index result(INVALID_INDEX);
        if (startIndex < static_cast<Index>(m_sortedValues.size()) &&
            endIndex < static_cast<Index>(m_sortedValues.size()) && startIndex <= endIndex) {
            result = getIndexOfValueWithoutCheck(startIndex, endIndex, value);
        }
        return result;
    }

private:
    Index getIndexOfValueWithoutCheck(Index const startIndex, Index const endIndex, Value const& value) const {
        Index result(INVALID_INDEX);
        Index lowIndex(startIndex), highIndex(endIndex);
        while (lowIndex + 1 < highIndex) {
            Index middleIndex = getMidpointOfIndexes(lowIndex, highIndex);
            Value middleValue(m_sortedValues[middleIndex]);
            if (value <= middleValue) {
                highIndex = middleIndex;
            } else {
                lowIndex = middleIndex;
            }
        }
        if (value == m_sortedValues[lowIndex]) {
            result = lowIndex;
        } else if (value == m_sortedValues[highIndex]) {
            result = highIndex;
        }
        return result;
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba

// Theoretically we need log N + 1 comparisons in worst case.
// If we observe, we are using two comparisons per iteration except during final successful match, if any.
// In practice, comparison would be costly operation, it won’t be just primitive type comparison.
// It is more economical to minimize comparisons as that of theoretical limit.

// In the while loop we are depending only on one comparison.
// The search space converges to place l and r point two different consecutive elements.
// We need one more comparison to trace search status.
