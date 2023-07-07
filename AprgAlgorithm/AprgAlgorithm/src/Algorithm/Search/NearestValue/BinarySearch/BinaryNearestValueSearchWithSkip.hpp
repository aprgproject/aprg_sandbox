#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class BinaryNearestValueSearchWithSkip {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithSkip(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Value getNearestValue(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues[getIndexOfNearestValueWithoutCheck(target)];
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& target) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfNearestValueWithoutCheck(target);
        }
        return result;
    }

private:
    Index getIndexOfNearestValueWithoutCheck(Value const& target) const {
        Index lowIndex(getNearestLowerBoundIndex(target));
        return getIndexOfNearestValueFromLowerIndex(target, lowIndex);
    }

    Index getNearestLowerBoundIndex(Value const& target) const {
        Index result(0);
        Index size(m_sortedValues.size());
        // forward skip start from half of size, then quarter of size, then eighth of size and so on
        for (Index forwardSkip = size / 2; forwardSkip >= 1; forwardSkip /= 2) {
            result += forwardSkip;  // move to next position
            while (result < size && m_sortedValues[result] <= target) {
                result += forwardSkip;
            }
            result -= forwardSkip;  // return to valid position
        }
        return result;
    }

    Index getIndexOfNearestValueFromLowerIndex(Value const& target, Index const lowIndex) const {
        Value lowerBoundValue(m_sortedValues[lowIndex]);
        Value highIndex(getHigherIndex(lowIndex));
        Value deviationFromLower(mathHelper::getPositiveDelta(target, lowerBoundValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(target, m_sortedValues[highIndex]));
        return (deviationFromLower <= deviationFromHigher) ? lowIndex : highIndex;
    }

    Index getHigherIndex(Index const lowIndex) const {
        return std::min(lowIndex + 1, static_cast<Index>(m_sortedValues.size()) - 1);
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
