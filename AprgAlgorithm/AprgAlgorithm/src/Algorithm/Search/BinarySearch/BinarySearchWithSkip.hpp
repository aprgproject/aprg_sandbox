#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

namespace alba
{
namespace algorithm
{
template <typename Values>
class BinarySearchWithSkip
{
public:
    using Index = unsigned int;
    using Value = typename Values::value_type;

    BinarySearchWithSkip(Values const& sortedValues)
        : m_sortedValues(sortedValues)
    {}

    Value findNearestValue(Value const& value)
    {
        Index index(0);
        Index size(m_sortedValues.size());
        for(Index skip = size/2; skip>=1; skip/=2) // skip start from half of size, then quarter of size, then eighth of size and soon
        {
            while(index+skip < size && m_sortedValues.at(index+skip) <= value)
            {
                index += skip;
            }
        }
        return getNearestValueOnCurrentIndex(value, index);
    }

private:

    Value getNearestValueOnCurrentIndex(Value const& value, Index const index) const
    {
        Value firstValue(getValueAt(index));
        Value secondValue(getValueAt(index+1));
        Value distanceFromFirstValue(mathHelper::getPositiveDelta(value, firstValue));
        Value distanceFromSecondValue(mathHelper::getPositiveDelta(value, secondValue));
        Value lowestDistance(std::min(distanceFromFirstValue, distanceFromSecondValue));
        Value result;
        if(lowestDistance==distanceFromFirstValue)
        {
            result = firstValue;
        }
        else if(lowestDistance==distanceFromSecondValue)
        {
            result = secondValue;
        }
        return result;
    }

    inline Value getValueAt(Index const index) const
    {
        Value value{};
        if(index<m_sortedValues.size())
        {
            value = m_sortedValues.at(index);
        }
        return value;
    }

private:
    Values const& m_sortedValues;
};

}

}
