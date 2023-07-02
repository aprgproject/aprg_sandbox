#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class TernaryNearestValueSearch {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    TernaryNearestValueSearch(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Value getNearestValue(Value const& value) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            Index selectedIndex(getIndexOfNearestValueWithoutCheck(0, m_sortedValues.size() - 1, value));
            if (selectedIndex != INVALID_INDEX) {
                result = m_sortedValues[selectedIndex];
            }
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfNearestValueWithoutCheck(0, m_sortedValues.size() - 1, value);
        }
        return result;
    }

    Index getIndexOfNearestValue(Index const lowIndex, Index const highIndex, Value const& value) const {
        Index result(INVALID_INDEX);
        if (lowIndex < static_cast<Index>(m_sortedValues.size()) &&
            highIndex < static_cast<Index>(m_sortedValues.size()) && lowIndex <= highIndex) {
            result = getIndexOfNearestValueWithoutCheck(lowIndex, highIndex, value);
        }
        return result;
    }

private:
    Index getIndexOfNearestValueWithoutCheck(Index const lowIndex, Index const highIndex, Value const& value) const {
        Index result(INVALID_INDEX);
        if (value < m_sortedValues[lowIndex]) {
            result = (lowIndex == 0) ? 0 : getIndexOfNearestValueInBetweenTwoIndices(lowIndex - 1, lowIndex, value);
        } else if (m_sortedValues[highIndex] < value) {
            Index lastIndex = static_cast<Index>(m_sortedValues.size()) - 1;
            result = (highIndex == lastIndex)
                         ? lastIndex
                         : getIndexOfNearestValueInBetweenTwoIndices(highIndex, highIndex + 1, value);
        } else {
            Index firstMiddleIndex = getFirstOneThirdIndex(lowIndex, highIndex);
            Index secondMiddleIndex = getSecondOneThirdIndex(lowIndex, highIndex);
            if (value < m_sortedValues[firstMiddleIndex]) {
                result = getIndexOfNearestValueWithoutCheck(lowIndex, firstMiddleIndex - 1, value);
            } else if (m_sortedValues[secondMiddleIndex] < value) {
                result = getIndexOfNearestValueWithoutCheck(secondMiddleIndex + 1, highIndex, value);
            } else {
                result = getIndexOfNearestValueWithoutCheck(firstMiddleIndex + 1, secondMiddleIndex - 1, value);
            }
        }
        return result;
    }

    Index getIndexOfNearestValueInBetweenTwoIndices(
        Index const lowIndex, Index const highIndex, Value const& value) const {
        Value deviationFromLower(mathHelper::getPositiveDelta(value, m_sortedValues[lowIndex]));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues[highIndex]));
        return (deviationFromLower <= deviationFromHigher) ? lowIndex : highIndex;
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
