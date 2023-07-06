#pragma once

#include <Algorithm/Stack/BaseStack.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <cassert>
#include <memory>

namespace alba {

namespace algorithm {

template <typename Object, typename QueueWithObject>
class StackUsingTwoQueues : public BaseStack<Object> {
public:
    StackUsingTwoQueues() {}

    bool isEmpty() const override { return getSize() == 0; }

    int getSize() const override { return m_queueAtTheTop.getSize() + m_queueAtTheBottom.getSize(); }

    void push(Object const& object) override {
        m_queueAtTheTop.enqueue(object);
        transferAtPushIfNeeded();
    }

    Object pop() override {
        transferAtPopIfNeeded();
        rotateFirstToLast(m_queueAtTheTop);
        return m_queueAtTheTop.dequeue();
    }

private:
    void transferAtPushIfNeeded() {
        // remove items to make the size logarithmic
        int targetSizeAtTop = getTargetSizeAtTop(getSize());
        int limitSizeAtTop = targetSizeAtTop * 2;
        if (m_queueAtTheTop.getSize() > limitSizeAtTop) {
            // put all at the bottom
            while (!m_queueAtTheTop.isEmpty()) {
                m_queueAtTheBottom.enqueue(m_queueAtTheTop.dequeue());
            }

            // position so that end as the top
            rotate(m_queueAtTheBottom, m_queueAtTheBottom.getSize() - targetSizeAtTop);

            // put a logarithmic size at the top
            for (int i = 0; i < targetSizeAtTop; i++) {
                m_queueAtTheTop.enqueue(m_queueAtTheBottom.dequeue());
            }
        }
    }

    void transferAtPopIfNeeded() {
        // add items to make size logarithmic
        if (m_queueAtTheTop.isEmpty()) {
            int targetSizeAtTop = getTargetSizeAtTop(m_queueAtTheBottom.getSize());
            rotate(m_queueAtTheBottom, m_queueAtTheBottom.getSize() - targetSizeAtTop);
            for (int i = 0; i < targetSizeAtTop; i++) {
                m_queueAtTheTop.enqueue(m_queueAtTheBottom.dequeue());
            }
        }
    }

    int getTargetSizeAtTop(int const totalSize) const {
        // return the logarithmic size
        return std::max(
            1, static_cast<int>(
                   AlbaBitValueUtilities<uint64_t>::getLogarithmWithBase2Of(static_cast<uint64_t>(totalSize))));
    }

    void rotateFirstToLast(QueueWithObject& queue) {
        rotate(queue, static_cast<int>(m_queueAtTheBottom.getSize()) - 1);
    }

    void rotate(QueueWithObject& queue, int const numberOfTimes) {
        for (int i = 0; i < numberOfTimes; i++) {
            queue.enqueue(queue.dequeue());
        }
    }

    QueueWithObject m_queueAtTheTop;
    QueueWithObject m_queueAtTheBottom;
};

}  // namespace algorithm

}  // namespace alba
