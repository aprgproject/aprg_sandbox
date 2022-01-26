#include <Queue/LinkedListQueue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using QueueForTest = LinkedListQueue<unsigned int>;
}

TEST(LinkedListQueueTest, IsEmptyWorks)
{
    QueueForTest queue1;
    QueueForTest queue2;
    queue2.enqueue(10U);

    EXPECT_TRUE(queue1.isEmpty());
    EXPECT_FALSE(queue2.isEmpty());
}

TEST(LinkedListQueueTest, GetSizeWorks)
{
    QueueForTest queue1;
    QueueForTest queue2;
    queue2.enqueue(10U);
    queue2.enqueue(5U);
    queue2.enqueue(4U);

    EXPECT_EQ(0U, queue1.getSize());
    EXPECT_EQ(3U, queue2.getSize());
}

TEST(LinkedListQueueTest, EnqueueWorks)
{
    QueueForTest queue;

    queue.enqueue(1U);
    queue.enqueue(2U);
    queue.enqueue(3U);

    EXPECT_EQ(3U, queue.getSize());
    EXPECT_EQ(1U, queue.dequeue());
    EXPECT_EQ(2U, queue.dequeue());
    EXPECT_EQ(3U, queue.dequeue());
}

TEST(LinkedListQueueTest, DequeueWorks)
{
    QueueForTest queue;
    queue.enqueue(1U);
    queue.enqueue(2U);
    queue.enqueue(3U);

    EXPECT_EQ(1U, queue.dequeue());
    EXPECT_EQ(2U, queue.dequeue());
    EXPECT_EQ(3U, queue.dequeue());
    EXPECT_EQ(0U, queue.getSize());
}

TEST(LinkedListQueueTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    QueueForTest queue;

    EXPECT_DEATH(queue.dequeue(), "Assertion failed!");
}

}
