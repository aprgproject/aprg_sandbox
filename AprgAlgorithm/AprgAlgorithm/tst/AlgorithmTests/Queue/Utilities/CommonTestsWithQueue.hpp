#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace CommonTestsWithQueue {

template <typename Queue>
void testIsEmptyWhenEmptyWithInt() {
    Queue queue;

    EXPECT_TRUE(queue.isEmpty());
}

template <typename Queue>
void testIsEmptyWhenNotEmptyWithInt() {
    Queue queue;
    queue.enqueue(10);

    EXPECT_FALSE(queue.isEmpty());
}

template <typename Queue>
void testGetSizeWhenEmptyWithInt() {
    Queue queue;

    EXPECT_EQ(0, queue.getSize());
}

template <typename Queue>
void testGetSizeWhenNotEmptyWithInt() {
    Queue queue;
    queue.enqueue(10);
    queue.enqueue(5);
    queue.enqueue(4);

    EXPECT_EQ(3, queue.getSize());
}

template <typename Queue>
void testEnqueueWithInt() {
    Queue queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    ASSERT_EQ(3, queue.getSize());
    EXPECT_EQ(1, queue.dequeue());
    EXPECT_EQ(2, queue.dequeue());
    EXPECT_EQ(3, queue.dequeue());
}

template <typename Queue>
void testDequeueWithInt() {
    Queue queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    EXPECT_EQ(1, queue.dequeue());
    EXPECT_EQ(2, queue.dequeue());
    EXPECT_EQ(3, queue.dequeue());
    ASSERT_EQ(0, queue.getSize());
}

template <typename Queue>
void testDequeueAssertionWhenEmptyWithInt() {
    Queue queue;
    EXPECT_DEATH(queue.dequeue(), "Assertion failed!");
}

}  // namespace CommonTestsWithQueue

}  // namespace algorithm

}  // namespace alba
