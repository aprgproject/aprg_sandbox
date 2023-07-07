#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class BinarySearchWithOneComparisonPerIteration {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinarySearchWithOneComparisonPerIteration(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Index getIndexOfValue(Value const& target) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexUsingIntervalsCanBeOutsideTarget(0, m_sortedValues.size() - 1, target);
            // result = getIndexUsingIntervalsInsideTarget(0, m_sortedValues.size() - 1, target);
        }
        return result;
    }

    Index getIndexOfValue(Index const startIndex, Index const endIndex, Value const& target) const {
        Index result(INVALID_INDEX);
        if (startIndex < static_cast<Index>(m_sortedValues.size()) &&
            endIndex < static_cast<Index>(m_sortedValues.size()) && startIndex <= endIndex) {
            result = getIndexUsingIntervalsCanBeOutsideTarget(startIndex, endIndex, target);
            // result = getIndexUsingIntervalsInsideTarget(startIndex, endIndex, target);
        }
        return result;
    }

private:
    Index getIndexUsingIntervalsCanBeOutsideTarget(
        Index const startIndex, Index const endIndex, Value const& target) const {
        // Some end cases analysis:
        // -> If interval is one element[a], loop ends, we check low target
        // -> If interval is two elements[a,b]:
        // ---> middleValue < target -> low moves to right, only b retains (target might be to the left)
        // ---> middleValue == target -> low moves to right, only b retains (target might be to the left)
        // ---> target < middleValue -> high moves to left, only a retains
        // -> If interval is three elements, this reduces to one element
        // -> If interval is four elements, this reduces to one element or two elements

        Index result(INVALID_INDEX);
        Index lowIndex(startIndex), highIndex(endIndex);
        while (lowIndex < highIndex) {
            Index middleIndex = getMidpointOfIndexes(lowIndex, highIndex);
            if (m_sortedValues[middleIndex] <= target) {
                lowIndex = middleIndex + 1;
            } else {
                highIndex = middleIndex - 1;
            }
        }
        if (target == m_sortedValues[lowIndex]) {
            result = lowIndex;
        } else if (lowIndex > startIndex && target == m_sortedValues[lowIndex - 1]) {
            result = lowIndex - 1;
        }
        return result;
    }

    Index getIndexUsingIntervalsInsideTarget(Index const startIndex, Index const endIndex, Value const& target) const {
        // Some end cases analysis:
        // -> If interval is one element[a], loop ends, we check either low or high target
        // -> If interval is two elements[a,b], loop ends, we check either low or high target
        // -> If interval is three elements, this reduces to two elements
        // -> If interval is four elements, this reduces to two element or three elements

        Index result(INVALID_INDEX);
        Index lowIndex(startIndex), highIndex(endIndex);
        while (lowIndex + 1 < highIndex) {
            Index middleIndex = getMidpointOfIndexes(lowIndex, highIndex);
            if (target <= m_sortedValues[middleIndex]) {
                highIndex = middleIndex;
            } else {
                lowIndex = middleIndex;
            }
        }
        if (target == m_sortedValues[lowIndex]) {
            result = lowIndex;
        } else if (target == m_sortedValues[highIndex]) {
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
