#pragma once

#include <Algorithm/Queue/BaseQueue.hpp>

#include <cassert>
#include <memory>

namespace alba {

namespace algorithm {

template <typename Object>
class DoublingSizeCircularQueue : public BaseQueue<Object> {
public:
    static constexpr int MINUMUM_CONTAINER_SIZE = 1;

    DoublingSizeCircularQueue() : m_containerSize(0), m_firstIndex(0), m_afterLastIndex(0), m_objects(nullptr) {
        initialize(MINUMUM_CONTAINER_SIZE);
    }

    ~DoublingSizeCircularQueue() { deleteAllObjects(); }
    bool isEmpty() const override { return getSize() == 0; }

    int getSize() const override {        if (m_firstIndex <= m_afterLastIndex) {
            return m_afterLastIndex - m_firstIndex;
        } else {
            return m_containerSize - m_firstIndex + m_afterLastIndex;
        }
    }

    void enqueue(Object const& object) override {
        resizeOnEnqueueIfNeeded();
        moveBackIndexIfNeeded(m_afterLastIndex);
        m_objects[m_afterLastIndex++] = object;
    }

    Object dequeue() override {
        // should be not empty
        assert(m_firstIndex != m_afterLastIndex);
        moveBackIndexIfNeeded(m_firstIndex);
        Object result(m_objects[m_firstIndex++]);
        resizeOnDequeueIfNeeded();
        return result;
    }

    int getContainerSize() const { return m_containerSize; }

private:
    void deleteAllObjects() {
        if (m_objects != nullptr) {
            delete[](m_objects);
        }
    }

    void initialize(int const initialSize) {
        if (m_objects == nullptr) {
            m_objects = new Object[initialSize];
            m_containerSize = initialSize;
        }
    }

    void moveBackIndexIfNeeded(int& index) {
        if (index >= m_containerSize) {
            index = 0;
        }
    }

    void resize(int const newSize) {
        Object* newObjects = new Object[newSize];
        if (m_objects != nullptr) {
            if (m_firstIndex <= m_afterLastIndex) {
                std::copy(m_objects + m_firstIndex, m_objects + m_afterLastIndex, newObjects);
            } else {
                std::copy(m_objects + m_firstIndex, m_objects + m_containerSize, newObjects);
                std::copy(m_objects, m_objects + m_afterLastIndex, newObjects + m_containerSize - m_firstIndex);
            }
            delete[](m_objects);
        }
        m_afterLastIndex = getSize();
        m_firstIndex = 0;
        m_objects = newObjects;
        m_containerSize = newSize;
    }

    void resizeOnEnqueueIfNeeded() {
        if (getSize() >= m_containerSize) {
            resize(m_containerSize * 2);
        }
    }

    void resizeOnDequeueIfNeeded() {
        if (m_containerSize > 0 && getSize() == m_containerSize / 4) {
            resize(std::max(MINUMUM_CONTAINER_SIZE, m_containerSize / 2));
        }
    }

    int m_containerSize;
    int m_firstIndex;
    int m_afterLastIndex;    Object* m_objects;
};

}  // namespace algorithm
}  // namespace alba
