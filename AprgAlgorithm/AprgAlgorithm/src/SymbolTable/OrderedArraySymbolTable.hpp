#pragma once

#include <vector>

namespace alba
{

template <typename Key, typename Object>
class OrderedArraySymbolTable
{
public:

    OrderedArraySymbolTable()
        : m_currentSize(0)
    {}

    bool isEmpty() const
    {
        return m_currentSize == 0;
    }

    unsigned int getSize() const
    {
        return m_currentSize;
    }

    Object get(Key const& key) const
    {
        Object result{};
        if(!isEmpty())
        {
            unsigned int rank(getRank(key));
            if(rank < m_currentSize && m_keys.at(rank) == key)
            {
                result = m_objects.at(rank);
            }
        }
        return result;
    }

    unsigned int getRank(Key const& key) const
    {
        // Rank is the number of keys less than key
        unsigned int result(0);
        int lowIndex=0, highIndex=m_currentSize-1;
        while(lowIndex <= highIndex)
        {
            int midIndex=(lowIndex+highIndex)/2;
            Key const& keyAtMidIndex(m_keys.at(midIndex));
            if(key < keyAtMidIndex)
            {
                highIndex = midIndex-1;
            }
            else if(key > keyAtMidIndex)
            {
                lowIndex = midIndex+1;
            }
            else
            {
                result = static_cast<unsigned int>(midIndex);
                break;
            }
        }
        if(result == 0)
        {
            result = static_cast<unsigned int>(lowIndex);
        }
        return result;
    }

    Object getMinimum() const
    {
        Object result{};
        if(!isEmpty())
        {
            result = m_objects.at(0);
        }
        return result;
    }

    Object getMaximum() const
    {
        Object result{};
        if(!isEmpty())
        {
            result = m_objects.at(m_currentSize-1);
        }
        return result;
    }

    Key selectAt(unsigned int const index) const
    {
        return m_keys.at(index);
    }

    Key getFloor(Key const& key) const
    {
        // Smallest key greater than or equal to key
        Key result{};
        unsigned int rank(getRank(key));
        if(rank < m_currentSize && m_keys.at(rank) == key)
        {
            result = key;
        }
        else if(rank-1 < m_currentSize && m_keys.at(rank-1) < key)
        {
            result = m_keys.at(rank-1);
        }
        return result;
    }

    Key getCeiling(Key const& key) const
    {
        // Smallest key greater than or equal to key
        Key result{};
        unsigned int rank(getRank(key));
        if(rank < m_currentSize)
        {
            result = m_keys.at(rank);
        }
        return result;
    }

    void put(Key const& key, Object const& object)
    {
        bool isKeyFound(false);
        unsigned int rank(getRank(key));
        if(rank < m_currentSize && m_keys.at(rank) == key)
        {
            m_objects[rank] = object;
            isKeyFound = true;
        }
        if(!isKeyFound)
        {
            m_keys.emplace_back();
            m_objects.emplace_back();
            for(unsigned int i=m_currentSize; i>rank; i--)
            {
                m_keys[i] = m_keys.at(i-1);
                m_objects[i] = m_objects.at(i-1);
            }
            m_keys[rank] = key;
            m_objects[rank] = object;
            m_currentSize++;
        }
    }

    void deleteBasedOnKey(Key const& key)
    {
        unsigned int rank(getRank(key));
        if(rank < m_currentSize && m_keys.at(rank) == key)
        {
            if(m_currentSize >= 2)
            {
                for(unsigned int i=rank; i<m_currentSize-1; i++)
                {
                    m_keys[i] = m_keys.at(i+1);
                    m_objects[i] = m_objects.at(i+1);
                }
            }
            m_keys.pop_back();
            m_objects.pop_back();
            m_currentSize--;
        }
    }

private:
    unsigned int m_currentSize;
    std::vector<Key> m_keys;
    std::vector<Object> m_objects;
};

}
