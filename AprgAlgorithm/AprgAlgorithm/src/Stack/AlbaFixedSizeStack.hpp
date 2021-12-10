#pragma once

#include <array>
#include <cassert>

namespace alba
{

template <typename ObjectType, unsigned int SIZE>
class AlbaFixedSizeStack
{
public:
    using Objects = std::array<ObjectType, SIZE>;

    AlbaFixedSizeStack()
        : m_currentSize(0)
    {}

    bool isEmpty() const
    {
        return m_currentSize == 0;
    }

    unsigned int getSize() const
    {
        return m_currentSize;
    }

    Objects const& getObjects() const
    {
        return m_objects;
    }

    void push(ObjectType const& object)
    {
        assert(m_currentSize < SIZE);
        m_objects[m_currentSize++] = object;
    }

    ObjectType pop()
    {
        assert(m_currentSize > 0);
        return m_objects[--m_currentSize];
    }

private:

    unsigned int m_currentSize;
    Objects m_objects;
};

}
