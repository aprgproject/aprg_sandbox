#pragma once

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <vector>

namespace alba
{

template <typename Object>
class BinarySearch
{
    using Objects = std::vector<Object>;
public:
    BinarySearch()
        : m_indexOfLowest{0}
        , m_indexOfHighest{0}
    {}
    BinarySearch(std::initializer_list<Object> const& initialObjects)
        : m_indexOfLowest{0}
        , m_indexOfHighest{0}
    {
        add(initialObjects);
    }
    Object findNearestValue(Object const& value)
    {
        while(m_indexOfHighest - m_indexOfLowest > 2)
        {
            findValueForOneIteration(value);
        }
        return getNearestValueFromLowestMiddleHighest(value);
    }
    Object getLowestValue() const
    {
        return getValueIndex(m_indexOfLowest);
    }
    Object getMiddleValue() const
    {
        return getValueIndex(getMiddleIndex());
    }
    Object getHighestValue() const
    {
        return getValueIndex(m_indexOfHighest);
    }
    Object getNearestValueFromLowestMiddleHighest(Object const& value) const
    {
        Object distanceFromLowestValue(mathHelper::getPositiveDelta(value, getLowestValue()));
        Object distanceFromMiddleValue(mathHelper::getPositiveDelta(value, getMiddleValue()));
        Object distanceFromHighestValue(mathHelper::getPositiveDelta(value, getHighestValue()));
        Object lowestDistance(std::min(std::min(distanceFromLowestValue, distanceFromMiddleValue), distanceFromHighestValue));
        Object result;
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
    void add(std::initializer_list<Object> const& initialObjects)
    {
        for(Object const& object : initialObjects)
        {
            add(object);
        }
    }
    void add(Object const& value)
    {
        m_objects.insert(std::upper_bound(m_objects.begin(), m_objects.end(), value), value);
        updateIndexes();
    }
    void findValueForOneIteration(Object const& value)
    {
         unsigned int middleIndex(getMiddleIndex());
         Object middleValue(getValueIndex(middleIndex));
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
    Object getValueIndex(unsigned int const index) const
    {
        Object object{0};
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
