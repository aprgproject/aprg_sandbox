#pragma once

#include <Algorithm/Queue/BaseQueue.hpp>

#include <array>
#include <cassert>
#include <memory>

namespace alba {

namespace algorithm {

template <typename Object, int SIZE>
class FixedSizeCircularQueue : public BaseQueue<Object> {
public:
    using Objects = std::array<Object, SIZE>;

    FixedSizeCircularQueue() : m_firstIndex(0), m_afterLastIndex(0) {}

    bool isEmpty() const override { return getSize() == 0; }

    int getSize() const override {
        if (m_firstIndex <= m_afterLastIndex) {
            return m_afterLastIndex - m_firstIndex;
        } else {
            return SIZE - m_firstIndex + m_afterLastIndex;
        }
    }

    void enqueue(Object const& object) override {
        m_objects[m_afterLastIndex++] = object;
        moveBackIndexIfNeeded(m_afterLastIndex);
        assert(m_firstIndex != m_afterLastIndex);
    }

    Object dequeue() override {
        assert(m_firstIndex != m_afterLastIndex);
        Object result(m_objects[m_firstIndex++]);
        moveBackIndexIfNeeded(m_firstIndex);
        return result;
    }

private:
    void moveBackIndexIfNeeded(int& index) {
        if (index >= SIZE) {
            index = 0;
        }
    }

    int m_firstIndex;
    int m_afterLastIndex;
    Objects m_objects;
};

}  // namespace algorithm

}  // namespace alba
