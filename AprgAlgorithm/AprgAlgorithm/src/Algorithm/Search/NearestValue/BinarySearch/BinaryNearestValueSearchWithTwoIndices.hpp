#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba {
namespace algorithm {

template <typename Values>class BinaryNearestValueSearchWithTwoIndices {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithTwoIndices(Values const& sortedValues)
        : m_lowIndex(INVALID_INDEX), m_highIndex(INVALID_INDEX), m_sortedValues(sortedValues) {
        setInitialIndexes();
    }

    BinaryNearestValueSearchWithTwoIndices(Index const lowIndex, Index const highIndex, Values const& sortedValues)
        : m_lowIndex(INVALID_INDEX), m_highIndex(INVALID_INDEX), m_sortedValues(sortedValues) {
        setInitialIndexes(lowIndex, highIndex);
    }

    Value getNearestValue(Value const& value) {
        Value result{};
        if (!m_sortedValues.empty()) {
            moveIndexesUntilCloseToValue(value);
            result = m_sortedValues[getIndexOfNearestValueInBetweenTwoIndices(value)];
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            moveIndexesUntilCloseToValue(value);
            result = getIndexOfNearestValueInBetweenTwoIndices(value);
        }
        return result;
    }

    inline Index getLowerIndex() const { return m_lowIndex; }

    inline Index getHigherIndex() const { return m_highIndex; }

    Value getLowerValue() const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues[m_lowIndex];
        }
        return result;
    }

    Value getHigherValue() const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = m_sortedValues[m_highIndex];
        }
        return result;
    }

private:
    Index getIndexOfNearestValueInBetweenTwoIndices(Value const& value) const {
        Value deviationFromLower(mathHelper::getPositiveDelta(value, m_sortedValues[m_lowIndex]));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues[m_highIndex]));
        return (deviationFromLower <= deviationFromHigher) ? m_lowIndex : m_highIndex;
    }

    void setInitialIndexes() {
        if (!m_sortedValues.empty()) {
            m_lowIndex = 0;
            m_highIndex = m_sortedValues.size() - 1;  // fully closed interval
        }
    }

    void setInitialIndexes(Index const lowIndex, Index const highIndex) {
        if (!m_sortedValues.empty()) {
            Index maxIndex = m_sortedValues.size() - 1;
            m_lowIndex = std::min(lowIndex, maxIndex);
            m_highIndex = std::min(highIndex, maxIndex);  // fully closed interval
            if (m_lowIndex > m_highIndex) {
                std::swap(m_lowIndex, m_highIndex);
            }
        }
    }

    void moveIndexesUntilCloseToValue(Value const& value) {
        if (!m_sortedValues.empty()) {
            moveIndexesCloserUntilDistanceIsLessThanOrEqualToOne(value);
            moveIndexesCloserWhenValueIsBeyondTheIndices(value);
        }
    }

    void moveIndexesCloserUntilDistanceIsLessThanOrEqualToOne(Value const& value) {
        while (m_lowIndex + 1 < m_highIndex) {
            // Binary search with one comparison per iteration

            Index middleIndex(getMidpointOfIndexes(m_lowIndex, m_highIndex));
            Value middleValue(m_sortedValues[middleIndex]);
            if (value <= middleValue) {
                m_highIndex = middleIndex;
            } else {
                m_lowIndex = middleIndex;
            }
        }
    }

    void moveIndexesCloserWhenValueIsBeyondTheIndices(Value const& value) {
        if (value <= m_sortedValues[m_lowIndex]) {
            m_highIndex = m_lowIndex;
        } else if (m_sortedValues[m_highIndex] <= value) {
            m_lowIndex = m_highIndex;
        }
    }

    Index m_lowIndex;
    Index m_highIndex;
    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
