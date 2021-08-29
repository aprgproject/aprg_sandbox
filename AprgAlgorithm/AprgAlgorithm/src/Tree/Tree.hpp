#pragma once

#include <iterator>
#include <memory>
#include <vector>

namespace alba
{

template <typename ObjectType>
class Tree
{
    using ObjectIndexes = std::vector<unsigned int>;
    using ObjectPtrs = std::vector<std::unique_ptr<ObjectType>>;
public:
    Tree()
    {}

    ObjectType const & getObjectReference(unsigned int const objectIndex)
    {
        m_objectPtrs.at(objectIndex);
    }

    unsigned int createNewObjectAndReturnObjectIndex(ObjectType const& object)
    {
        unsigned int objectIndex(0);
        if(m_emptyObjectIndexes.empty())
        {
            objectIndex = m_emptyObjectIndexes.size();
            m_objectPtrs.emplace_back(new ObjectType(object));
        }
        else
        {
            objectIndex = m_emptyObjectIndexes.front();
            m_objectPtrs[objectIndex].reset(new ObjectType(object));
        }
        return objectIndex;
    }

    void deleteObject(unsigned int const objectIndex)
    {
        if(objectIndex < m_objectPtrs.size())
        {
            if(objectIndex == m_objectPtrs.size()-1)
            {
                m_objectPtrs.pop_back();
            }
            else
            {
                m_objectPtrs[objectIndex].reset(nullptr);
                m_emptyObjectIndexes.emplace_back(objectIndex);
            }
            removeOutOfBoundEmptyIndexes();
        }
    }

    void removeOutOfBoundEmptyIndexes()
    {
        ObjectIndexes::const_iterator deleteIterator(m_emptyObjectIndexes.cend());
        for(ObjectIndexes::const_reverse_iterator reverseIterator = m_emptyObjectIndexes.crbegin();
            reverseIterator != m_emptyObjectIndexes.crend();
            reverseIterator++)
        {
            if(*reverseIterator < m_objectPtrs.size())
            {
                break;
            }
            deleteIterator = --(reverseIterator.base());
        }
        m_emptyObjectIndexes.erase(deleteIterator);
    }

private:
    ObjectIndexes m_emptyObjectIndexes;
    ObjectPtrs m_objectPtrs;
};

}
