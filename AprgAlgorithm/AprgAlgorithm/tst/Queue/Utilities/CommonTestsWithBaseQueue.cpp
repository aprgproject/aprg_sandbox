#include <Queue/Utilities/CommonTestsWithBaseQueue.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithBaseQueue
{
void performIsEmptyTestWhenEmpty(BaseQueueForUnsignedInt & queue)
{
    EXPECT_TRUE(queue.isEmpty());}

void performIsEmptyTestWhenNotEmpty(BaseQueueForUnsignedInt & queue)
{
    queue.enqueue(10U);

    EXPECT_FALSE(queue.isEmpty());
}

void performGetSizeTestWhenEmpty(BaseQueueForUnsignedInt & queue)
{
    EXPECT_EQ(0U, queue.getSize());
}

void performGetSizeTestWhenNotEmpty(BaseQueueForUnsignedInt & queue)
{
    queue.enqueue(10U);
    queue.enqueue(5U);
    queue.enqueue(4U);

    EXPECT_EQ(3U, queue.getSize());
}

void performEnqueueTest(BaseQueueForUnsignedInt & queue)
{
    queue.enqueue(1U);
    queue.enqueue(2U);
    queue.enqueue(3U);

    ASSERT_EQ(3U, queue.getSize());
    EXPECT_EQ(1U, queue.dequeue());
    EXPECT_EQ(2U, queue.dequeue());
    EXPECT_EQ(3U, queue.dequeue());
}

void performDequeueTest(BaseQueueForUnsignedInt & queue)
{
    queue.enqueue(1U);
    queue.enqueue(2U);
    queue.enqueue(3U);

    EXPECT_EQ(1U, queue.dequeue());
    EXPECT_EQ(2U, queue.dequeue());
    EXPECT_EQ(3U, queue.dequeue());
    ASSERT_EQ(0U, queue.getSize());
}

void performDequeueAssertionTestWhenEmpty(BaseQueueForUnsignedInt & queue)
{
    EXPECT_DEATH(queue.dequeue(), "Assertion failed!");
}

}

}

}