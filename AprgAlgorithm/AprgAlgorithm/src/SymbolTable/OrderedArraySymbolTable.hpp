#pragma once

#include <SymbolTable/BaseSymbolTable.hpp>

#include <vector>

namespace alba
{

template <typename Key, typename Value>
class OrderedArraySymbolTable : public BaseSymbolTable<Key, Value>
{
public:
    OrderedArraySymbolTable()
        : m_currentSize(0)
    {}

    bool isEmpty() const override
    {
        return m_currentSize == 0;
    }

    unsigned int getSize() const override
    {
        return m_currentSize;
    }

    unsigned int getRank(Key const& key) const override
    {
        unsigned int result(0);
        int lowIndex=0, highIndex=m_currentSize-1;
        while(lowIndex <= highIndex)        {
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

    Value get(Key const& key) const override
    {
        Value result{};
        if(!isEmpty())
        {
            unsigned int rank(getRank(key));
            if(rank < m_currentSize && m_keys.at(rank) == key)
            {
                result = m_values.at(rank);
            }
        }
        return result;
    }

    Key getMinimum() const override
    {
        Value result{};
        if(!isEmpty())
        {
            result = m_keys.at(0);
        }
        return result;
    }

    Key getMaximum() const override
    {
        Value result{};
        if(!isEmpty())
        {
            result = m_keys.at(m_currentSize-1);        }
        return result;
    }

    Key selectAt(unsigned int const index) const override
    {
        return m_keys.at(index);
    }

    Key getFloor(Key const& key) const override
    {
        Key result{};
        unsigned int rank(getRank(key));
        if(rank < m_currentSize && m_keys.at(rank) == key)        {
            result = key;
        }
        else if(rank-1 < m_currentSize && m_keys.at(rank-1) < key)
        {
            result = m_keys.at(rank-1);
        }
        return result;
    }

    Key getCeiling(Key const& key) const override
    {
        Key result{};
        unsigned int rank(getRank(key));
        if(rank < m_currentSize)        {
            result = m_keys.at(rank);
        }
        return result;
    }

    void put(Key const& key, Value const& value) override
    {
        bool isKeyFound(false);
        unsigned int rank(getRank(key));
        if(rank < m_currentSize && m_keys.at(rank) == key)
        {
            m_values[rank] = value;
            isKeyFound = true;
        }
        if(!isKeyFound)
        {
            m_keys.emplace_back();
            m_values.emplace_back();
            for(unsigned int i=m_currentSize; i>rank; i--)
            {
                m_keys[i] = m_keys.at(i-1);
                m_values[i] = m_values.at(i-1);
            }
            m_keys[rank] = key;
            m_values[rank] = value;
            m_currentSize++;
        }
    }

    void deleteBasedOnKey(Key const& key) override
    {
        unsigned int rank(getRank(key));
        if(rank < m_currentSize && m_keys.at(rank) == key)        {
            if(m_currentSize >= 2)
            {
                for(unsigned int i=rank; i<m_currentSize-1; i++)
                {
                    m_keys[i] = m_keys.at(i+1);
                    m_values[i] = m_values.at(i+1);
                }
            }
            m_keys.pop_back();
            m_values.pop_back();
            m_currentSize--;
        }
    }

    void deleteMinimum() override
    {
        for(unsigned int i=0; i<m_currentSize-1; i++)
        {
            m_keys[i] = m_keys.at(i+1);
            m_values[i] = m_values.at(i+1);
        }
        m_keys.pop_back();
        m_values.pop_back();
        m_currentSize--;
    }

    void deleteMaximum() override
    {
        m_keys.pop_back();
        m_values.pop_back();
        m_currentSize--;
    }

private:
    unsigned int m_currentSize;
    std::vector<Key> m_keys;
    std::vector<Value> m_values;
};

}