#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class BinaryNearestValueSearchWithRecursion {
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithRecursion(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Value getNearestValue(Value const& value) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues.at(getIndexOfNearestValueWithoutCheck(0U, m_sortedValues.size() - 1, value));
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfNearestValueWithoutCheck(0U, m_sortedValues.size() - 1, value);
        }
        return result;
    }

    Index getIndexOfNearestValue(Index const lowerIndex, Index const higherIndex, Value const& value) const {
        Index result(INVALID_INDEX);
        if (lowerIndex < m_sortedValues.size() && higherIndex < m_sortedValues.size() && lowerIndex <= higherIndex) {
            result = getIndexOfNearestValueWithoutCheck(lowerIndex, higherIndex, value);
        }
        return result;
    }

private:
    Index getIndexOfNearestValueWithoutCheck(
        Index const lowerIndex, Index const higherIndex, Value const& value) const {
        if (lowerIndex + 1U < higherIndex) {
            // Binary search with one comparison per iteration

            Index middleIndex = getMidpointOfIndexes(lowerIndex, higherIndex);
            Value middleValue(m_sortedValues.at(middleIndex));
            if (value <= middleValue) {
                return getIndexOfNearestValueWithoutCheck(lowerIndex, middleIndex, value);
            } else {
                return getIndexOfNearestValueWithoutCheck(middleIndex, higherIndex, value);
            }
        } else {
            return getIndexOfNearestValueInBetweenTwoIndices(lowerIndex, higherIndex, value);
        }
    }

    Index getIndexOfNearestValueInBetweenTwoIndices(
        Index const lowerIndex, Index const higherIndex, Value const& value) const {
        Value deviationFromLower(mathHelper::getPositiveDelta(value, m_sortedValues.at(lowerIndex)));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues.at(higherIndex)));
        return (deviationFromLower <= deviationFromHigher) ? lowerIndex : higherIndex;
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
