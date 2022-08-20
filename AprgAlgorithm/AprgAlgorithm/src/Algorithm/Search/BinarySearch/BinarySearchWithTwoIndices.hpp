#pragma once

#include <Common/Math/AlbaMathHelper.hpp>

namespace alba
{
namespace algorithm
{

template <typename Values>
class BinarySearchWithTwoIndices
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;

    BinarySearchWithTwoIndices(Values const& sortedValues)
        : m_indexOfLowest(0)
        , m_indexOfHighest(sortedValues.size()-1)
        , m_sortedValues(sortedValues)
    {}

    BinarySearchWithTwoIndices(Index const indexOfLowest, Index const indexOfHighest, Values const& sortedValues)
        : m_indexOfLowest(indexOfLowest)
        , m_indexOfHighest(indexOfHighest)
        , m_sortedValues(sortedValues)
    {}

    Value findNearestValue(Value const& value)
    {
        while(m_indexOfHighest - m_indexOfLowest > 2)
        {
            findValueForOneIteration(value);
        }
        return getNearestValueFromLowestMiddleHighest(value);
    }

    Value getLowestValue() const
    {
        return getValueAt(m_indexOfLowest);
    }

    Value getMiddleValue() const
    {
        return getValueAt(getMiddleIndex());
    }

    Value getHighestValue() const
    {
        return getValueAt(m_indexOfHighest);
    }

    Value getNearestValueFromLowestMiddleHighest(Value const& value) const
    {
        Value distanceFromLowestValue(mathHelper::getPositiveDelta(value, getLowestValue()));
        Value distanceFromMiddleValue(mathHelper::getPositiveDelta(value, getMiddleValue()));
        Value distanceFromHighestValue(mathHelper::getPositiveDelta(value, getHighestValue()));
        Value lowestDistance(std::min(std::min(distanceFromLowestValue, distanceFromMiddleValue), distanceFromHighestValue));
        Value result;
        if(lowestDistance==distanceFromLowestValue)
        {
            result = getLowestValue();
        }
        else if(lowestDistance==distanceFromMiddleValue)
        {
            result = getMiddleValue();
        }
        else if(lowestDistance==distanceFromHighestValue)
        {
            result = getHighestValue();
        }
        return result;
    }

    void findValueForOneIteration(Value const& value)
    {
         Index middleIndex(getMiddleIndex());
         Value middleValue(getValueAt(middleIndex));
         if(value > middleValue)
         {
             m_indexOfLowest = middleIndex+1;
         }
         else if(value < middleValue)
         {
             m_indexOfHighest = middleIndex-1;
         }         else
         {
             m_indexOfLowest = middleIndex;
             m_indexOfHighest = middleIndex;         }
    }

private:

    Value getValueAt(Index const index) const
    {
        Value value{};
        if(index<m_sortedValues.size())
        {
            value = m_sortedValues.at(index);
        }
        return value;
    }

    Index getMiddleIndex() const
    {
        return (m_indexOfLowest+m_indexOfHighest)/2;
    }

    Index m_indexOfLowest;
    Index m_indexOfHighest;
    Values const& m_sortedValues;
};

}
}