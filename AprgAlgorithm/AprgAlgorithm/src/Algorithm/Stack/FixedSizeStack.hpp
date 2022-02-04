#pragma once

#include <Algorithm/Stack/BaseStack.hpp>

#include <array>
#include <cassert>

namespace alba
{

namespace algorithm
{

template <typename Object, unsigned int SIZE>
class FixedSizeStack : public BaseStack<Object>
{
public:
    using Objects = std::array<Object, SIZE>;

    FixedSizeStack()
        : m_size(0)
    {}

    bool isEmpty() const override
    {
        return m_size == 0;
    }

    unsigned int getSize() const override
    {
        return m_size;
    }

    void push(Object const& object) override
    {
        assert(m_size < SIZE);
        m_objects[m_size++] = object;
    }

    Object pop() override
    {
        assert(m_size > 0);
        return m_objects[--m_size];
    }

    Objects const& getObjects() const
    {
        return m_objects;
    }

private:
    unsigned int m_size;
    Objects m_objects;
};

}

}
