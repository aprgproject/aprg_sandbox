#pragma once

#include <Algorithm/Stack/BaseStack.hpp>

#include <algorithm>
#include <cassert>

namespace alba
{

namespace algorithm
{

template <typename Object>
class DoublingSizeStack : public BaseStack<Object>
{
public:

    DoublingSizeStack()
        : m_stackSize(0)
        , m_containerSize(0)
        , m_objects(nullptr)
    {
        initialize(INITIAL_CONTAINER_SIZE);
    }

    ~DoublingSizeStack()
    {
        deleteAllObjects();
    }

    bool isEmpty() const override
    {
        return m_stackSize == 0;
    }

    unsigned int getSize() const override
    {
        return m_stackSize;
    }

    void push(Object const& object) override
    {
        resizeOnPushIfNeeded();
        m_objects[m_stackSize++] = object;
    }

    Object pop() override
    {
        assert(m_stackSize > 0);
        Object result(m_objects[--m_stackSize]);
        resizeOnPopIfNeeded();
        return result;
    }

    unsigned int getContainerSize() const
    {
        return m_containerSize;
    }

private:

    void deleteAllObjects()
    {
        if(m_objects != nullptr)
        {
            delete[](m_objects);
        }
    }

    void initialize(unsigned int const initialSize)
    {
        if(m_objects == nullptr)
        {
            m_objects = new Object[initialSize]{};
            m_containerSize = initialSize;
        }
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

    void resizeOnPushIfNeeded()
    {
        if(m_stackSize == m_containerSize)
        {
            resize(m_containerSize*2);
        }
    }

    void resizeOnPopIfNeeded()
    {
        if(m_containerSize > 0 && m_stackSize == m_containerSize/4)
        {
            resize(m_containerSize/2);
        }
    }

    static constexpr unsigned int INITIAL_CONTAINER_SIZE = 1U;
    unsigned int m_stackSize;
    unsigned int m_containerSize;
    Object* m_objects;
};

}

}
