#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class BinaryNearestValueSearchWithRecursion {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithRecursion(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Value getNearestValue(Value const& value) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues.at(getIndexOfNearestValueWithoutCheck(0, m_sortedValues.size() - 1, value));
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
    Index getIndexOfNearestValueWithoutCheck(
        Index const lowIndex, Index const highIndex, Value const& value) const {
        if (lowIndex + 1 < highIndex) {
            // Binary search with one comparison per iteration

            Index middleIndex = getMidpointOfIndexes(lowIndex, highIndex);
            Value middleValue(m_sortedValues.at(middleIndex));
            if (value <= middleValue) {
                return getIndexOfNearestValueWithoutCheck(lowIndex, middleIndex, value);
            } else {
                return getIndexOfNearestValueWithoutCheck(middleIndex, highIndex, value);
            }
        } else {
            return getIndexOfNearestValueInBetweenTwoIndices(lowIndex, highIndex, value);
        }
    }

    Index getIndexOfNearestValueInBetweenTwoIndices(
        Index const lowIndex, Index const highIndex, Value const& value) const {
        Value deviationFromLower(mathHelper::getPositiveDelta(value, m_sortedValues.at(lowIndex)));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues.at(highIndex)));
        return (deviationFromLower <= deviationFromHigher) ? lowIndex : highIndex;
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
