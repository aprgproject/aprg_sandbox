#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class BinaryNearestValueSearchWithSkip
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithSkip(Values const& sortedValues)
        : m_sortedValues(sortedValues)
    {}

    Value getNearestValue(Value const& value) const
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            result = m_sortedValues.at(getIndexOfNearestValueWithoutCheck(value));
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            result = getIndexOfNearestValueWithoutCheck(value);
        }
        return result;
    }

private:

    Index getIndexOfNearestValueWithoutCheck(Value const& value) const
    {
        Index lowerIndex(getNearestLowerBoundIndex(value));
        return getIndexOfNearestValueFromLowerIndex(value, lowerIndex);
    }

    Index getNearestLowerBoundIndex(Value const& value) const
    {
        Index result(0);
        Index size(m_sortedValues.size());
        for(Index forwardSkip = size/2; forwardSkip>=1; forwardSkip/=2) // forward skip start from half of size, then quarter of size, then eighth of size and so on
        {
            while(result+forwardSkip < size && m_sortedValues.at(result+forwardSkip) <= value)
            {
                result += forwardSkip;
            }
        }
        return result;
    }

    Index getIndexOfNearestValueFromLowerIndex(Value const& value, Index const lowerIndex) const
    {
        Value lowerBoundValue(m_sortedValues.at(lowerIndex));
        Value higherIndex(getHigherIndex(lowerIndex));
        Value deviationFromLower(mathHelper::getPositiveDelta(value, lowerBoundValue));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues.at(higherIndex)));
        return (deviationFromLower <= deviationFromHigher) ? lowerIndex : higherIndex;
    }

    Index getHigherIndex(Index const lowerIndex) const
    {
        return std::min(lowerIndex+1, m_sortedValues.size()-1);
    }

    Values const& m_sortedValues;
};

}

}
