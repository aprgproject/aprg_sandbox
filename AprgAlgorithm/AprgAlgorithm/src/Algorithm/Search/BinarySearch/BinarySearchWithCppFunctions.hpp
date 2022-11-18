#pragma once

#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <algorithm>

namespace alba
{

namespace algorithm
{

template <typename Values> // this should be a non set container to be efficient because std::lower_bound and std::upper_bound are used
class BinarySearchWithCppFunctions
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = std::numeric_limits<Index>::max();

    BinarySearchWithCppFunctions(Values const& sortedValues)
        : m_sortedValues(sortedValues)
    {}
    Value getNearestValue(Value const& value) const
    {
        Value result{};        if(!m_sortedValues.empty())
        {
            result = getNearestValueUsingEqualRange(value);
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            result = getIndexOfNearestValueUsingEqualRange(value);        }
        return result;
    }
    Value getLowerBound(Value const& value) const
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            auto lowerBoundIt = std::lower_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), value);
            result = *lowerBoundIt;
        }
        return result;
    }

    Value getHigherBound(Value const& value) const
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            auto upperBoundIt = std::upper_bound(m_sortedValues.cbegin(), m_sortedValues.cend(), value);
            result = *upperBoundIt;
        }
        return result;
    }

private:

    Value getNearestValueUsingEqualRange(Value const& value) const
    {
        auto lowerAndUpperBoundItPair = containerHelper::getLowerAndUpperConstIteratorsForNonSet(m_sortedValues, value); // assumption is non set
        Value result{};
        Value lowerBoundValue(*(lowerAndUpperBoundItPair.first));
        if(value == lowerBoundValue)
        {
            result = value;
        }
        else
        {
            Value higherBoundValue(*(lowerAndUpperBoundItPair.second));
            Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
            Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherBoundValue));
            result = (deviationFromLower <= deviationFromHigher) ? lowerBoundValue : higherBoundValue;
        }
        return result;
    }

    Index getIndexOfNearestValueUsingEqualRange(Value const& value) const
    {
        auto lowerAndUpperBoundItPair = containerHelper::getLowerAndUpperConstIteratorsForNonSet(m_sortedValues, value); // assumption is non set
        Index result(INVALID_INDEX);
        Index lowerBoundIndex = std::distance(m_sortedValues.cbegin(), lowerAndUpperBoundItPair.first);
        Value lowerBoundValue(*(lowerAndUpperBoundItPair.first));
        if(value == lowerBoundValue)        {
            result = lowerBoundIndex;
        }
        else        {
            Value higherBoundValue(*(lowerAndUpperBoundItPair.second));
            Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
            Value deviationFromHigher(mathHelper::getPositiveDelta(value, higherBoundValue));
            result = (deviationFromLower <= deviationFromHigher)
                    ? lowerBoundIndex
                    : std::distance(m_sortedValues.cbegin(), lowerAndUpperBoundItPair.second);
        }
        return result;
    }

    Values const& m_sortedValues;
};

}

}

// The C++ standard library contains the following functions that are based on binary search and work in logarithmic time:
// • lower_bound returns a pointer to the first array element whose value is at least x.
// • upper_bound returns a pointer to the first array element whose value is larger than x.
// • equal_range returns both above pointers.

// The functions assume that the array is sorted.
// If there is no such element, the pointer points to the element after the last array element.
