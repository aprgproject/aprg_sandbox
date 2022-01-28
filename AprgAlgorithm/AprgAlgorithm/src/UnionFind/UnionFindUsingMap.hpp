#pragma once

#include <UnionFind/BaseUnionFind.hpp>

#include <map>

namespace alba
{

template <typename Object>
class UnionFindUsingMap : public BaseUnionFind<Object>
{
    using ConnectionMap = std::map<Object, Object>; // you are using map, so log N but this should to be near constant (boo!)
public:
    UnionFindUsingMap()
    {}

    bool isConnected(Object const& object1, Object const& object2) const override
    {
        return getRoot(object1) == getRoot(object2);
    }

    Object getRoot(Object const& object) const override
    {
        Object currentObject(object);
        while(isExistingInConnectionMap(currentObject))        {
            Object const& tempRoot(m_connectionMap.at(currentObject));
            if(tempRoot==currentObject)
            {
                break;
            }
            currentObject = tempRoot;
        }
        return currentObject;
    }

    void connect(Object const& object1, Object const& object2) override
    {
        bool isObject1LowerThanObject2(object1<object2);
        Object lowerValueObject(isObject1LowerThanObject2 ? object1 : object2);        Object higherValueObject(isObject1LowerThanObject2 ? object2 : object1);
        initializeToConnectionMapIfNeeded(object1);
        initializeToConnectionMapIfNeeded(object2);
        Object root(getRoot(lowerValueObject));
        m_connectionMap[lowerValueObject] = root;
        m_connectionMap[higherValueObject] = root;
    }

private:
    void initializeToConnectionMapIfNeeded(Object const& object)
    {
        if(!isExistingInConnectionMap(object))
        {
            m_connectionMap[object] = object;
        }
    }

    bool isExistingInConnectionMap(Object const& object) const
    {
        return m_connectionMap.find(object) != m_connectionMap.end();
    }
    ConnectionMap m_connectionMap;
};

}