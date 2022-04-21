#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithQueue
{

template <typename Queue>
void testIsEmptyWhenEmptyWithUnsignedInt()
{
    Queue queue;

    EXPECT_TRUE(queue.isEmpty());
}

template <typename Queue>
void testIsEmptyWhenNotEmptyWithUnsignedInt()
{
    Queue queue;
    queue.enqueue(10U);

    EXPECT_FALSE(queue.isEmpty());
}

template <typename Queue>
void testGetSizeWhenEmptyWithUnsignedInt()
{
    Queue queue;

    EXPECT_EQ(0U, queue.getSize());
}

template <typename Queue>
void testGetSizeWhenNotEmptyWithUnsignedInt()
{
    Queue queue;
    queue.enqueue(10U);
    queue.enqueue(5U);
    queue.enqueue(4U);

    EXPECT_EQ(3U, queue.getSize());
}

template <typename Queue>
void testEnqueueWithUnsignedInt()
{
    Queue queue;
    queue.enqueue(1U);
    queue.enqueue(2U);
    queue.enqueue(3U);

    ASSERT_EQ(3U, queue.getSize());
    EXPECT_EQ(1U, queue.dequeue());
    EXPECT_EQ(2U, queue.dequeue());
    EXPECT_EQ(3U, queue.dequeue());
}

template <typename Queue>
void testDequeueWithUnsignedInt()
{
    Queue queue;
    queue.enqueue(1U);
    queue.enqueue(2U);
    queue.enqueue(3U);

    EXPECT_EQ(1U, queue.dequeue());
    EXPECT_EQ(2U, queue.dequeue());
    EXPECT_EQ(3U, queue.dequeue());
    ASSERT_EQ(0U, queue.getSize());
}

template <typename Queue>
void testDequeueAssertionWhenEmptyWithUnsignedInt()
{
    Queue queue;
    EXPECT_DEATH(queue.dequeue(), "Assertion failed!");
}

}

}

}
