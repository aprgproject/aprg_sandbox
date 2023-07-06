#include <Algorithm/Queue/DoublingSizeCircularQueue.hpp>
#include <AlgorithmTests/Queue/Utilities/CommonTestsWithQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithQueue;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using QueueForTest = DoublingSizeCircularQueue<int>;
}

TEST(DoublingSizeCircularQueueTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<QueueForTest>(); }

TEST(DoublingSizeCircularQueueTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<QueueForTest>(); }

TEST(DoublingSizeCircularQueueTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<QueueForTest>(); }

TEST(DoublingSizeCircularQueueTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<QueueForTest>(); }

TEST(DoublingSizeCircularQueueTest, EnqueueWorks) { testEnqueueWithInt<QueueForTest>(); }

TEST(DoublingSizeCircularQueueTest, DequeueWorks) { testDequeueWithInt<QueueForTest>(); }

TEST(DoublingSizeCircularQueueTest, GetContainerSizeWorks) {
    QueueForTest queue1;
    QueueForTest queue2;
    queue2.enqueue(10);
    queue2.enqueue(5);
    queue2.enqueue(4);

    EXPECT_EQ(1, queue1.getContainerSize());
    EXPECT_EQ(4, queue2.getContainerSize());
}

TEST(DoublingSizeCircularQueueTest, PushWorksWithDoublingContainerSize) {
    QueueForTest queue;
    EXPECT_EQ(1, queue.getContainerSize());

    queue.enqueue(1);
    queue.enqueue(2);
    EXPECT_EQ(2, queue.getContainerSize());

    queue.enqueue(3);
    EXPECT_EQ(4, queue.getContainerSize());

    queue.enqueue(4);
    queue.enqueue(5);
    EXPECT_EQ(8, queue.getContainerSize());
}

TEST(DoublingSizeCircularQueueTest, PopWorksWithHalvingContainerSize) {
    QueueForTest queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    EXPECT_EQ(8, queue.getContainerSize());

    EXPECT_EQ(1, queue.dequeue());
    EXPECT_EQ(2, queue.dequeue());
    EXPECT_EQ(3, queue.dequeue());
    EXPECT_EQ(4, queue.getContainerSize());

    EXPECT_EQ(4, queue.dequeue());
    EXPECT_EQ(2, queue.getContainerSize());

    EXPECT_EQ(5, queue.dequeue());
    EXPECT_EQ(1, queue.getContainerSize());
}

// disabled because it takes too long
TEST(DoublingSizeCircularQueueTest, DISABLED_DequeueWorksWithAssertionWhenItsEmpty) {
    testDequeueAssertionWhenEmptyWithInt<QueueForTest>();
}

}  // namespace algorithm

}  // namespace alba
