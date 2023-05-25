#pragma once

#include <Algorithm/Queue/BaseQueue.hpp>

#include <cassert>
#include <memory>

namespace alba {

namespace algorithm {

template <typename Object>
class DoublingSizeQueue : public BaseQueue<Object> {
public:
    DoublingSizeQueue() : m_containerSize(0), m_beforeFirstEntryIndex(-1), m_lastEntryIndex(-1), m_objects(nullptr) {
        initialize(INITIAL_CONTAINER_SIZE);
    }

    ~DoublingSizeQueue() { deleteAllObjects(); }

    bool isEmpty() const override { return getSize() == 0; }

    int getSize() const override { return m_lastEntryIndex - m_beforeFirstEntryIndex; }

    void enqueue(Object const& object) override {
        resizeOnEnqueueIfNeeded();
        m_objects[++m_lastEntryIndex] = object;
    }

    Object dequeue() override {
        assert(m_containerSize > m_beforeFirstEntryIndex + 1);
        Object result(m_objects[++m_beforeFirstEntryIndex]);
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
            m_objects = new Object[initialSize]{};
            m_containerSize = initialSize;
        }
    }

    void resize(int const newSize) {
        Object* newObjects = new Object[newSize]{};
        if (m_objects != nullptr) {
            std::copy(m_objects + m_beforeFirstEntryIndex + 1, m_objects + m_lastEntryIndex + 1, newObjects);
            delete[](m_objects);
        }
        m_lastEntryIndex = getSize() - 1;
        m_beforeFirstEntryIndex = -1;
        m_objects = newObjects;
        m_containerSize = newSize;
    }

    void resizeOnEnqueueIfNeeded() {
        if (m_lastEntryIndex + 1 == m_containerSize) {
            resize(m_containerSize * 2);
        }
    }

    void resizeOnDequeueIfNeeded() {
        if (m_containerSize > 0 && getSize() == m_containerSize / 4) {
            resize(m_containerSize / 2);
        }
    }

    static constexpr int INITIAL_CONTAINER_SIZE = 1;
    int m_containerSize;
    int m_beforeFirstEntryIndex;
    int m_lastEntryIndex;
    Object* m_objects;
};

}  // namespace algorithm

}  // namespace alba
