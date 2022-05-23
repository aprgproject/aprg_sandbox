#pragma once

#include <Common/Math/AlbaMathHelper.hpp>
namespace alba
{

namespace algorithm
{

template <typename Objects>
class BinarySearchWithTwoIndices
{
public:
    using Object = typename Objects::value_type;

    BinarySearchWithTwoIndices(Objects const& sortedObjects)
        : m_indexOfLowest(0)
        , m_indexOfHighest(sortedObjects.size()-1)
        , m_sortedObjects(sortedObjects)
    {}

    Object findNearestValue(Object const& object)
    {
        while(m_indexOfHighest - m_indexOfLowest > 2)
        {
            findValueForOneIteration(object);
        }
        return getNearestValueFromLowestMiddleHighest(object);
    }

    Object getLowestObject() const
    {
        return getObjectAt(m_indexOfLowest);
    }

    Object getMiddleObject() const
    {
        return getObjectAt(getMiddleIndex());
    }

    Object getHighestObject() const
    {
        return getObjectAt(m_indexOfHighest);
    }

    Object getNearestValueFromLowestMiddleHighest(Object const& object) const
    {
        Object distanceFromLowestValue(mathHelper::getPositiveDelta(object, getLowestObject()));
        Object distanceFromMiddleValue(mathHelper::getPositiveDelta(object, getMiddleObject()));
        Object distanceFromHighestValue(mathHelper::getPositiveDelta(object, getHighestObject()));
        Object lowestDistance(std::min(std::min(distanceFromLowestValue, distanceFromMiddleValue), distanceFromHighestValue));
        Object result;
        if(lowestDistance==distanceFromLowestValue)
        {
            result = getLowestObject();
        }
        else if(lowestDistance==distanceFromMiddleValue)
        {
            result = getMiddleObject();
        }
        else if(lowestDistance==distanceFromHighestValue)
        {
            result = getHighestObject();
        }
        return result;
    }

    void findValueForOneIteration(Object const& object)
    {
         unsigned int middleIndex(getMiddleIndex());
         Object middleValue(getObjectAt(middleIndex));
         if(object > middleValue)
         {
             m_indexOfLowest = middleIndex+1;
         }
         else if(object < middleValue)
         {
             m_indexOfHighest = middleIndex-1;
         }
         else
         {
             m_indexOfLowest = middleIndex;
             m_indexOfHighest = middleIndex;
         }
    }

private:

    Object getObjectAt(unsigned int const index) const
    {
        Object object{};
        if(index<m_sortedObjects.size())
        {
            object = m_sortedObjects.at(index);
        }
        return object;
    }

    unsigned int getMiddleIndex() const
    {
        return (m_indexOfLowest+m_indexOfHighest)/2;
    }

    unsigned int m_indexOfLowest;
    unsigned int m_indexOfHighest;
    Objects const& m_sortedObjects;
};

}

}
