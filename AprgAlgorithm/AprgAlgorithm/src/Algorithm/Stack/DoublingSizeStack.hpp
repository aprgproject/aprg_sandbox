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

    void push(Object const& object) override // constant amortized (best case: constant, worst case: linear due to resizing)
    {
        resizeOnPushIfNeeded();
        m_objects[m_stackSize++] = object;
    }

    Object pop() override // constant amortized (best case: constant, worst case: linear due to resizing)
    {
        assert(m_stackSize > 0);
        Object result(m_objects[--m_stackSize]);        resizeOnPopIfNeeded();
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

    void resize(unsigned int const newSize) // array is between 25% and 100% full
    {
        Object* newObjects = new Object[newSize]{};
        if(m_objects != nullptr)        {
            std::copy(m_objects, m_objects + std::min(m_stackSize, newSize), newObjects);
            delete[](m_objects);
        }        m_objects = newObjects;
        m_containerSize = newSize;
    }

    void resizeOnPushIfNeeded()
    {
        if(m_stackSize == m_containerSize) // only resize to double when stack is full, on average the cost is 3N -> N + (2+4+8+...+N) = 3N
        {
            resize(m_containerSize*2);
        }    }

    void resizeOnPopIfNeeded()
    {
        if(m_containerSize > 0 && m_stackSize == m_containerSize/4) // only resize to half when its one-fourth full to avoid "thrashing" (push pop push pop action)
        {
            resize(m_containerSize/2);
        }    }

    static constexpr unsigned int INITIAL_CONTAINER_SIZE = 1U;
    unsigned int m_stackSize;    unsigned int m_containerSize;
    Object* m_objects;
};

}

}
