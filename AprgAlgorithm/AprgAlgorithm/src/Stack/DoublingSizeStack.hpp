#pragma once

#include <algorithm>
#include <cassert>

namespace alba
{

template <typename Object>
class DoublingSizeStack
{
public:
    static constexpr unsigned int INITIAL_SIZE = 1U;

    DoublingSizeStack()
        : m_stackSize(0)
        , m_containerSize(0)
        , m_objects(nullptr)
    {
        resize(INITIAL_SIZE);
    }

    ~DoublingSizeStack()
    {
        deleteAllObjects();
    }

    bool isEmpty() const
    {
        return m_stackSize == 0;
    }

    unsigned int getStackSize() const
    {
        return m_stackSize;
    }

    unsigned int getContainerSize() const
    {
        return m_containerSize;
    }

    void resize(unsigned int const newSize)
    {
        Object* newObjects = new Object[newSize]{};
        if(m_objects != nullptr)
        {
            std::copy(m_objects, m_objects + std::min(m_stackSize, newSize), newObjects);
            delete[](m_objects);
        }
        m_objects = newObjects;
        m_containerSize = newSize;
    }

    void push(Object const& object)
    {
        if(m_stackSize == m_containerSize)
        {
            resize(m_containerSize*2);
        }
        m_objects[m_stackSize++] = object;
    }

    Object pop()
    {
        assert(m_stackSize > 0);
        Object result(m_objects[--m_stackSize]);
        if(m_containerSize > 0 && m_stackSize == m_containerSize/4)
        {
            resize(m_containerSize/2);
        }
        return result;
    }

private:
    void deleteAllObjects()
    {
        if(m_objects != nullptr)
        {
            delete[](m_objects);
        }
    }

    unsigned int m_stackSize;
    unsigned int m_containerSize;
    Object* m_objects;
};

}
