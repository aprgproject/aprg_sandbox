#pragma once

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <vector>

namespace alba
{

template <typename ObjectType>
class BinarySearch
{
    using Objects = std::vector<ObjectType>;
public:
    BinarySearch()
        : m_indexOfLowest{0}
        , m_indexOfHighest{0}
    {}
    BinarySearch(std::initializer_list<ObjectType> const& initialObjects)
        : m_indexOfLowest{0}
        , m_indexOfHighest{0}
    {
        add(initialObjects);
    }
    ObjectType findNearestValue(ObjectType const& value)
    {
        while(m_indexOfHighest - m_indexOfLowest > 2)
        {
            findValueForOneIteration(value);
        }
        return getNearestValueFromLowestMiddleHighest(value);
    }
    ObjectType getLowestValue() const
    {
        return getValueIndex(m_indexOfLowest);
    }
    ObjectType getMiddleValue() const
    {
        return getValueIndex(getMiddleIndex());
    }
    ObjectType getHighestValue() const
    {
        return getValueIndex(m_indexOfHighest);
    }
    ObjectType getNearestValueFromLowestMiddleHighest(ObjectType const& value) const
    {
        ObjectType distanceFromLowestValue(mathHelper::getPositiveDelta(value, getLowestValue()));
        ObjectType distanceFromMiddleValue(mathHelper::getPositiveDelta(value, getMiddleValue()));
        ObjectType distanceFromHighestValue(mathHelper::getPositiveDelta(value, getHighestValue()));
        ObjectType lowestDistance(std::min(std::min(distanceFromLowestValue, distanceFromMiddleValue), distanceFromHighestValue));
        ObjectType result;
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
    void add(std::initializer_list<ObjectType> const& initialObjects)
    {
        for(ObjectType const& object : initialObjects)
        {
            add(object);
        }
    }
    void add(ObjectType const& value)
    {
        m_objects.insert(std::upper_bound(m_objects.begin(), m_objects.end(), value), value);
        updateIndexes();
    }
    void findValueForOneIteration(ObjectType const& value)
    {
         unsigned int middleIndex(getMiddleIndex());
         ObjectType middleValue(getValueIndex(middleIndex));
         if(value>middleValue)
         {
             m_indexOfLowest = middleIndex+1;
         }
         else if(value<middleValue)
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
    ObjectType getValueIndex(unsigned int const index) const
    {
        ObjectType object{0};
        if(index<m_objects.size())
        {
            object = m_objects[index];
        }
        return object;
    }
    unsigned int getMiddleIndex() const
    {
        return (m_indexOfLowest+m_indexOfHighest)/2;
    }
    void updateIndexes()
    {
        m_indexOfLowest=0;
        m_indexOfHighest=m_objects.size()-1;
    }

    unsigned int m_indexOfLowest;
    unsigned int m_indexOfHighest;
    Objects m_objects;
};

}
