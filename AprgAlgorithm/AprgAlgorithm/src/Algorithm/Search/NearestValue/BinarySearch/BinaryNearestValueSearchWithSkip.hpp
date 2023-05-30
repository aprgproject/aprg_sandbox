#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
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

    Value getNearestValue(Value const& value) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues.at(getIndexOfNearestValueWithoutCheck(value));
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfNearestValueWithoutCheck(value);
        }
        return result;
    }

private:
    Index getIndexOfNearestValueWithoutCheck(Value const& value) const {
        Index lowIndex(getNearestLowerBoundIndex(value));
        return getIndexOfNearestValueFromLowerIndex(value, lowIndex);
    }

    Index getNearestLowerBoundIndex(Value const& value) const {
        Index result(0);
        Index size(m_sortedValues.size());
        for (Index forwardSkip = size / 2; forwardSkip >= 1;
             forwardSkip /=
             2)  // forward skip start from half of size, then quarter of size, then eighth of size and so on
        {
            while (result + forwardSkip < size && m_sortedValues.at(result + forwardSkip) <= value) {
                result += forwardSkip;
            }
        }
        return result;
    }

    Index getIndexOfNearestValueFromLowerIndex(Value const& value, Index const lowIndex) const {
        Value lowerBoundValue(m_sortedValues.at(lowIndex));
        Value highIndex(getHigherIndex(lowIndex));
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues.at(highIndex)));
        return (deviationFromLower <= deviationFromHigher) ? lowIndex : highIndex;
    }

    Index getHigherIndex(Index const lowIndex) const {
        return std::min(lowIndex + 1, static_cast<Index>(m_sortedValues.size()) - 1);
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
