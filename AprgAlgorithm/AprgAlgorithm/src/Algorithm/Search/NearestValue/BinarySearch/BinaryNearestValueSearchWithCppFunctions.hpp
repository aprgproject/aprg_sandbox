#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>  // this should be a non set container to be efficient because std::lower_bound and
                            // std::upper_bound are used
class BinaryNearestValueSearchWithCppFunctions {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithCppFunctions(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Value getNearestValue(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            result = getNearestValueUsingEqualRange(target);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& target) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfNearestValueUsingEqualRange(target);
        }
        return result;
    }

    Value getLowerBound(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            auto lowerBoundIt = std::lower_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), target);
            result = *lowerBoundIt;
        }
        return result;
    }

    Value getHigherBound(Value const& target) const {
        Value result{};
        if (!m_sortedValues.empty()) {
            auto upperBoundIt = std::upper_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), target);
            result = *upperBoundIt;
        }
        return result;
    }

private:
    Value getNearestValueUsingEqualRange(Value const& target) const {
        auto lowerAndUpperBoundItPair =
            containerHelper::getLowerAndUpperConstIteratorsForNonSet(m_sortedValues, target);  // assumption is non set
        Value lowerBoundValue(*(lowerAndUpperBoundItPair.first));
        Value higherBoundValue(*(lowerAndUpperBoundItPair.second));
        Value deviationFromLower(mathHelper::getPositiveDelta(target, lowerBoundValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(target, higherBoundValue));
        return (deviationFromLower <= deviationFromHigher) ? lowerBoundValue : higherBoundValue;
    }

    Index getIndexOfNearestValueUsingEqualRange(Value const& target) const {
        auto lowerAndUpperBoundItPair =
            containerHelper::getLowerAndUpperConstIteratorsForNonSet(m_sortedValues, target);  // assumption is non set
        Value lowerBoundValue(*(lowerAndUpperBoundItPair.first));
        Value higherBoundValue(*(lowerAndUpperBoundItPair.second));
        Value deviationFromLower(mathHelper::getPositiveDelta(target, lowerBoundValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(target, higherBoundValue));
        return (deviationFromLower <= deviationFromHigher)
                   ? std::distance(m_sortedValues.cbegin(), lowerAndUpperBoundItPair.first)
                   : std::distance(m_sortedValues.cbegin(), lowerAndUpperBoundItPair.second);
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
