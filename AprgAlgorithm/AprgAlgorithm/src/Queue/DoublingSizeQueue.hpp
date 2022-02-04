#pragma once

#include <Queue/BaseQueue.hpp>

#include <cassert>
#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Object>
class DoublingSizeQueue : public BaseQueue<Object>
{public:

    DoublingSizeQueue()
        : m_queueSize(0)        , m_containerSize(0)
        , m_objects(nullptr)
    {
        initialize(INITIAL_CONTAINER_SIZE);
    }

    ~DoublingSizeQueue()
    {
        deleteAllObjects();
    }

    bool isEmpty() const override
    {
        return m_queueSize == 0;
    }

    unsigned int getSize() const override
    {
        return m_queueSize;
    }

    void enqueue(Object const& object) override
    {
        resizeOnEnqueueIfNeeded();
        m_objects[m_queueSize++] = object;
    }

    Object dequeue() override
    {
        assert(m_queueSize > 0);
        Object result(m_objects[0]);
        if(m_containerSize > 0 && m_queueSize-1 == m_containerSize/4)
        {
            resize(m_containerSize*2, 1U);
        }
        else
        {
            for(unsigned int i=0; i<m_queueSize; i++)
            {
                m_objects[i] = m_objects[i+1];
            }
        }
        m_queueSize--;
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

    void resize(unsigned int const newSize, unsigned int const copyOffset)
    {
        Object* newObjects = new Object[newSize]{};
        if(m_objects != nullptr)
        {
            std::copy(m_objects + copyOffset, m_objects + std::min(m_queueSize, newSize), newObjects);
            delete[](m_objects);
        }
        m_objects = newObjects;
        m_containerSize = newSize;
    }

    void resizeOnEnqueueIfNeeded()
    {
        if(m_queueSize == m_containerSize)
        {
            resize(m_containerSize*2, 0U);
        }
    }

    static constexpr unsigned int INITIAL_CONTAINER_SIZE = 1U;
    unsigned int m_queueSize;
    unsigned int m_containerSize;
    Object* m_objects;
};

}

}