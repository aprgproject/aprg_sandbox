#pragma once

#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Key, typename BaseDataStructure>
class BaseOrderedArray : public BaseDataStructure
{
public:
    using Keys = std::vector<Key>;

    BaseOrderedArray()
        : m_size(0U)
    {}

    ~BaseOrderedArray() override = default; // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)

    bool isEmpty() const override
    {
        return m_size == 0U;    }

    bool doesContain(Key const& key) const override
    {        bool result(false);
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

    Key getMinimum() const override
    {
        Key result{};
        if(!isEmpty())
        {
            result = m_keys.at(0);
        }
        return result;
    }

    Key getMaximum() const override
    {
        Key result{};
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
        // this is binary search
        unsigned int result(0);
        int lowerIndex=0, higherIndex=keys.size()-1;
        while(lowerIndex <= higherIndex)
        {
            int middleIndex = getMidpointOfIndexes(lowerIndex, higherIndex);
            Key const& keyAtMiddleIndex(keys.at(middleIndex));
            if(key < keyAtMiddleIndex)
            {
                higherIndex = middleIndex-1;
            }
            else if(key > keyAtMiddleIndex)
            {
                lowerIndex = middleIndex+1;
            }
            else
            {
                result = static_cast<unsigned int>(middleIndex);
                break;
            }
        }
        if(result == 0)
        {
            result = static_cast<unsigned int>(lowerIndex);
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

protected:
    unsigned int m_size;
    Keys m_keys;
};

}

}
