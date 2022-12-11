#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template <typename Object>
class UnionFindUsingMap : public BaseUnionFind<Object>
{
public:
    using ConnectionMap = std::map<Object, Object>; // you are using map, so log N but this should to be near constant (boo!)

    UnionFindUsingMap() = default;

    bool isConnected(Object const& object1, Object const& object2) const override
    {
        return getRoot(object1) == getRoot(object2);
    }

    Object getRoot(Object const& object) const override
    {
        // Is it log(N) * log(N) * log(N)...?
        // Is it log(log(log(N)))...? if its then its log*(N)
        Object currentObject(object);
        auto tempRootIt = m_connectionMap.find(currentObject);
        while(tempRootIt != m_connectionMap.end())
        {
            Object const& tempRoot(tempRootIt->second);
            if(tempRoot==currentObject)
            {
                break;
            }
            currentObject = tempRoot;
            tempRootIt = m_connectionMap.find(currentObject);
        }
        return currentObject;
    }

    void connect(Object const& object1, Object const& object2) override
    {
        initializeToConnectionMapIfNeeded(object1);
        initializeToConnectionMapIfNeeded(object2);
        Object root(std::min(getRoot(object1), getRoot(object2)));
        m_connectionMap[object1] = root;
        m_connectionMap[object2] = root;
    }

    ConnectionMap const& getConnectionMap() const
    {
        return m_connectionMap;
    }

private:
    void initializeToConnectionMapIfNeeded(Object const& object)
    {
        m_connectionMap.emplace(object, object);
    }
    ConnectionMap m_connectionMap;
};

}

}
