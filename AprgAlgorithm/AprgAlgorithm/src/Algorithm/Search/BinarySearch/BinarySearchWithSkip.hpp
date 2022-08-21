#pragma once

#include <Common/Math/AlbaMathHelper.hpp>

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

    BinarySearchWithSkip()
    {}

    Value findNearestValue(Values const& sortedValues, Value const& value)
    {
        Index index(0);
        Index size(sortedValues.size());
        for(Index skip = size/2; skip>=1; skip/=2) // skip start from half of size, then quarter of size, then eighth of size and soon
        {
            while(index+skip < size && sortedValues.at(index+skip) <= value)
            {
                index += skip;
            }
        }
        return getNearestValueOnCurrentIndex(sortedValues, value, index);
    }
private:

    Value getNearestValueOnCurrentIndex(Values const& sortedValues, Value const& value, Index const index) const
    {
        Value firstValue(getValueAt(sortedValues, index));
        Value secondValue(getValueAt(sortedValues, index+1));
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

    Value getValueAt(Values const& sortedValues, Index const index) const
    {
        Value value{};
        if(index<sortedValues.size())
        {
            value = sortedValues.at(index);
        }
        return value;
    }
};

}

}
