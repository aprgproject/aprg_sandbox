#pragma once

#include <Common/Math/AlbaMathHelper.hpp>

namespace alba
{

namespace algorithm
{

template <typename Objects>
class BinarySearchWithSkip
{
public:
    using Object = typename Objects::value_type;

    BinarySearchWithSkip()
    {}

    Object findNearestValue(Objects const& sortedObjects, Object const& object)
    {
        unsigned int index(0);
        unsigned int size(sortedObjects.size());
        for(unsigned int skip = size/2; skip>=1; skip/=2) // skip start from half of size, then quarter of size, then eighth of size and soon
        {
            while(index+skip < size && sortedObjects.at(index+skip) <= object)
            {
                index += skip;
            }
        }
        return getNearestValueOnCurrentIndex(sortedObjects, object, index);
    }
private:

    Object getNearestValueOnCurrentIndex(Objects const& sortedObjects, Object const& object, unsigned int const index) const
    {
        Object firstValue(getObjectAt(sortedObjects, index));
        Object secondValue(getObjectAt(sortedObjects, index+1));
        Object distanceFromFirstValue(mathHelper::getPositiveDelta(object, firstValue));
        Object distanceFromSecondValue(mathHelper::getPositiveDelta(object, secondValue));
        Object lowestDistance(std::min(distanceFromFirstValue, distanceFromSecondValue));
        Object result;
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

    Object getObjectAt(Objects const& sortedObjects, unsigned int const index) const
    {
        Object object{};
        if(index<sortedObjects.size())
        {
            object = sortedObjects.at(index);
        }
        return object;
    }
};

}

}
