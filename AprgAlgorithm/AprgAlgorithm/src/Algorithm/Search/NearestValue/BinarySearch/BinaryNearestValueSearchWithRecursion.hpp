#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class BinaryNearestValueSearchWithRecursion
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinaryNearestValueSearchWithRecursion(Values const& sortedValues)
        : m_sortedValues(sortedValues)
    {}

    Value getNearestValue(Value const& value) const
    {
        Value result{};
        if(!m_sortedValues.empty())
        {
            Index selectedIndex(getIndexOfNearestValueWithoutCheck(0U, m_sortedValues.size()-1, value));
            if(selectedIndex != INVALID_INDEX)
            {
                result = m_sortedValues.at(selectedIndex);
            }
        }
        return result;
    }

    Index getIndexOfNearestValue(Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(!m_sortedValues.empty())
        {
            result = getIndexOfNearestValueWithoutCheck(0U, m_sortedValues.size()-1, value);
        }
        return result;
    }

    Index getIndexOfNearestValue(Index const lowerIndex, Index const higherIndex, Value const& value) const
    {
        Index result(INVALID_INDEX);
        if(lowerIndex < m_sortedValues.size() && higherIndex < m_sortedValues.size() && lowerIndex<=higherIndex)
        {
            result = getIndexOfNearestValueWithoutCheck(lowerIndex, higherIndex, value);
        }
        return result;
    }

private:

    Index getIndexOfNearestValueWithoutCheck(Index const lowerIndex, Index const higherIndex, Value const& value) const
    {
        Index result(INVALID_INDEX);
        Index middleIndex = (lowerIndex+higherIndex)/2;
        Value middleValue(m_sortedValues.at(middleIndex));
        if(value == middleValue)
        {
            result = middleIndex;
        }
        else if(value < middleValue)
        {
            result = (lowerIndex+1 >= middleIndex)
                    ? getIndexOfNearestValueInBetweenTwoIndices(lowerIndex, middleIndex, value)
                    : getIndexOfNearestValueWithoutCheck(lowerIndex, middleIndex-1, value);
        }
        else if(middleValue < value)
        {
            result = (middleIndex+1 >= higherIndex)
                    ? getIndexOfNearestValueInBetweenTwoIndices(middleIndex, higherIndex, value)
                    : getIndexOfNearestValueWithoutCheck(middleIndex+1, higherIndex, value);
        }
        return result;
    }

    Index getIndexOfNearestValueInBetweenTwoIndices(Index const lowerIndex, Index const higherIndex, Value const& value) const
    {
        Value deviationFromLower(mathHelper::getPositiveDelta(value, m_sortedValues.at(lowerIndex)));
        Value deviationFromHigher(mathHelper::getPositiveDelta(value, m_sortedValues.at(higherIndex)));
        return (deviationFromLower <= deviationFromHigher) ? lowerIndex : higherIndex;
    }

    Values const& m_sortedValues;
};

}

}

