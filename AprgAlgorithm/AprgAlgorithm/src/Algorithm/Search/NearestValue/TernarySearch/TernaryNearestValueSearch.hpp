#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
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
                result = m_sortedValues.at(selectedIndex);
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

    Index getIndexOfNearestValue(Index const lowerIndex, Index const higherIndex, Value const& value) const {
        Index result(INVALID_INDEX);
        if (lowerIndex < static_cast<Index>(m_sortedValues.size()) &&
            higherIndex < static_cast<Index>(m_sortedValues.size()) && lowerIndex <= higherIndex) {
            result = getIndexOfNearestValueWithoutCheck(lowerIndex, higherIndex, value);
        }
        return result;
    }

private:
    Index getIndexOfNearestValueWithoutCheck(
        Index const lowerIndex, Index const higherIndex, Value const& value) const {
        Index result(INVALID_INDEX);
        if (value < m_sortedValues.at(lowerIndex)) {
            result =
                (lowerIndex == 0) ? 0 : getIndexOfNearestValueInBetweenTwoIndices(lowerIndex - 1, lowerIndex, value);
        } else if (m_sortedValues.at(higherIndex) < value) {
            result = (higherIndex == static_cast<Index>(m_sortedValues.size()) - 1)
                         ? m_sortedValues.size() - 1
                         : getIndexOfNearestValueInBetweenTwoIndices(higherIndex, higherIndex + 1, value);
        } else {
            Index oneThirdSize = (higherIndex - lowerIndex) / 3;
            Index firstMiddleIndex = lowerIndex + oneThirdSize;
            Index secondMiddleIndex = firstMiddleIndex + oneThirdSize;
            Value firstMiddleValue(m_sortedValues.at(firstMiddleIndex));
            Value secondMiddleValue(m_sortedValues.at(secondMiddleIndex));
            if (value == firstMiddleValue) {
                result = firstMiddleIndex;
            } else if (value == secondMiddleValue) {
                result = secondMiddleIndex;
            } else if (firstMiddleValue > value)  // if on the first one-third part
            {
                result = getIndexOfNearestValueWithoutCheck(lowerIndex, firstMiddleIndex - 1, value);
            } else if (secondMiddleValue < value)  // if on the third one-third part
            {
                result = getIndexOfNearestValueWithoutCheck(secondMiddleIndex + 1, higherIndex, value);
            } else  // if on the second one-third part
            {
                result = getIndexOfNearestValueWithoutCheck(firstMiddleIndex + 1, secondMiddleIndex - 1, value);
            }
        }
        return result;
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
