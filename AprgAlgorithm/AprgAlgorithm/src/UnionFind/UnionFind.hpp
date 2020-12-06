#pragma once

#include <map> //or unordered_map?

namespace alba
{

template <typename ObjectType>
class UnionFind
{
    using ConnectionMap = std::map<ObjectType, ObjectType>;
    using ConnectionPair = std::pair<ObjectType, ObjectType>;
public:
    UnionFind()
    {}

    void connect(ObjectType const& object1, ObjectType const& object2)
    {
        bool isObject1LowerThanObject2(object1<object2);
        ObjectType objectTemp1(isObject1LowerThanObject2 ? object1 : object2);
        ObjectType objectTemp2(isObject1LowerThanObject2 ? object2 : object1);
        initializeToConnectionMapIfNeeded(object1);
        initializeToConnectionMapIfNeeded(object2);
        ObjectType root(getRoot(objectTemp1));
        m_connectionMap[objectTemp1] = root;
        m_connectionMap[objectTemp2] = root;
    }
    bool isConnected(ObjectType const& object1, ObjectType const& object2) const
    {
        return getRoot(object1) == getRoot(object2);
    }

private:
    void initializeToConnectionMapIfNeeded(ObjectType const& object)
    {
        if(!isExistingInConnectionMap(object))
        {
            m_connectionMap[object] = object;
        }
    }
    ObjectType getRoot(ObjectType const& object) const
    {
        ObjectType currentObject(object);
        while(isExistingInConnectionMap(currentObject))
        {
            ObjectType const& tempRoot(m_connectionMap.at(currentObject));
            if(tempRoot==currentObject)
            {
                break;
            }
            currentObject = tempRoot;
        }
        return currentObject;
    }
    bool isExistingInConnectionMap(ObjectType const& object) const
    {
        return m_connectionMap.find(object) != m_connectionMap.end();
    }
    ConnectionMap m_connectionMap;
};

}
