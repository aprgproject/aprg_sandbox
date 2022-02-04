#pragma once

#include <SymbolTable/BaseSymbolTable.hpp>

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value>
class OrderedArraySymbolTable : public BaseSymbolTable<Key, Value>
{public:
    using Keys = std::vector<Key>;

    OrderedArraySymbolTable()        : m_size(0)
    {}

    bool isEmpty() const override
    {
        return m_size == 0;
    }

    bool doesContain(Key const& key) const override
    {
        bool result(false);
        if(!isEmpty())
        {
            unsigned int rank(getRank(key));
            if(rank < m_size && m_keys.at(rank) == key)
            {
                result = true;
            }
        }
        return result;
    }

    unsigned int getSize() const override
    {
        return m_size;
    }

    unsigned int getRank(Key const& key) const override
    {
        return getRank(key, m_keys);
    }

    Value get(Key const& key) const override
    {
        Value result{};
        if(!isEmpty())
        {
            unsigned int rank(getRank(key));
            if(rank < m_size && m_keys.at(rank) == key)
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
            result = m_keys.at(m_size-1);
        }
        return result;
    }

    Key selectAt(unsigned int const index) const override
    {
        return selectAt(index, m_keys);
    }

    Key getFloor(Key const& key) const override
    {
        return getFloor(key, m_keys);
    }

    Key getCeiling(Key const& key) const override
    {
        return getCeiling(key, m_keys);
    }

    void put(Key const& key, Value const& value) override
    {
        bool isKeyFound(false);
        unsigned int rank(getRank(key));
        if(rank < m_size && m_keys.at(rank) == key)
        {
            m_values[rank] = value;
            isKeyFound = true;
        }
        if(!isKeyFound)
        {
            m_keys.emplace_back();
            m_values.emplace_back();
            for(unsigned int i=m_size; i>rank; i--)
            {
                m_keys[i] = m_keys.at(i-1);
                m_values[i] = m_values.at(i-1);
            }
            m_keys[rank] = key;
            m_values[rank] = value;
            m_size++;
        }
    }

    void deleteBasedOnKey(Key const& key) override
    {
        unsigned int rank(getRank(key));
        if(rank < m_size && m_keys.at(rank) == key)
        {
            if(m_size >= 2)
            {
                for(unsigned int i=rank; i<m_size-1; i++)
                {
                    m_keys[i] = m_keys.at(i+1);
                    m_values[i] = m_values.at(i+1);
                }
            }
            m_keys.pop_back();
            m_values.pop_back();
            m_size--;
        }
    }

    void deleteMinimum() override
    {
        for(unsigned int i=0; i<m_size-1; i++)
        {
            m_keys[i] = m_keys.at(i+1);
            m_values[i] = m_values.at(i+1);
        }
        m_keys.pop_back();
        m_values.pop_back();
        m_size--;
    }

    void deleteMaximum() override
    {
        m_keys.pop_back();
        m_values.pop_back();
        m_size--;
    }

    Keys getKeys() const override
    {
        return m_keys;
    }

    Keys getKeysInRangeInclusive(Key const& low, Key const& high) const override
    {
        Keys result;
        for(Key const& currentKey : m_keys)
        {
            if(currentKey >= low && currentKey <= high)
            {
                result.emplace_back(currentKey);
            }
        }
        return result;
    }

    static unsigned int getRank(Key const& key, Keys const& keys)
    {
        unsigned int result(0);
        int lowIndex=0, highIndex=keys.size()-1;
        while(lowIndex <= highIndex)
        {
            int midIndex=(lowIndex+highIndex)/2;
            Key const& keyAtMidIndex(keys.at(midIndex));
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

    static Key selectAt(unsigned int const index, Keys const& keys)
    {
        Key result{};
        if(index < keys.size())
        {
            result = keys.at(index);
        }
        return result;
    }

    static Key getFloor(Key const& key, Keys const& keys)
    {
        Key result{};
        unsigned int rank(getRank(key, keys));
        if(rank < keys.size() && keys.at(rank) == key)
        {
            result = key;
        }
        else if(rank-1 < keys.size() && keys.at(rank-1) < key)
        {
            result = keys.at(rank-1);
        }
        return result;
    }

    static Key getCeiling(Key const& key, Keys const& keys)
    {
        Key result{};
        unsigned int rank(getRank(key, keys));
        if(rank < keys.size())
        {
            result = keys.at(rank);
        }
        return result;
    }

private:
    unsigned int m_size;
    std::vector<Key> m_keys;
    std::vector<Value> m_values;
};

}

}