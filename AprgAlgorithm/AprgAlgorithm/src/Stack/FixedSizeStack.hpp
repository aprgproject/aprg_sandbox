#pragma once

#include <Stack/BaseStack.hpp>

#include <array>
#include <cassert>
namespace alba
{

template <typename Object, unsigned int SIZE>
class FixedSizeStack : public BaseStack<Object>
{
public:
    using Objects = std::array<Object, SIZE>;
    FixedSizeStack()
        : m_currentSize(0)
    {}

    bool isEmpty() const override
    {
        return m_currentSize == 0;
    }

    unsigned int getSize() const override
    {
        return m_currentSize;
    }

    void push(Object const& object) override
    {
        assert(m_currentSize < SIZE);
        m_objects[m_currentSize++] = object;
    }

    Object pop() override
    {
        assert(m_currentSize > 0);
        return m_objects[--m_currentSize];
    }

    Objects const& getObjects() const
    {
        return m_objects;
    }

private:

    unsigned int m_currentSize;    Objects m_objects;
};

}
