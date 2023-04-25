#include <Algorithm/Queue/DoublingSizeQueue.hpp>
#include <AlgorithmTests/Queue/Utilities/CommonTestsWithQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithQueue;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using QueueForTest = DoublingSizeQueue<unsigned int>;
}

TEST(DoublingSizeQueueTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithUnsignedInt<QueueForTest>(); }

TEST(DoublingSizeQueueTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithUnsignedInt<QueueForTest>(); }

TEST(DoublingSizeQueueTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithUnsignedInt<QueueForTest>(); }

TEST(DoublingSizeQueueTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithUnsignedInt<QueueForTest>(); }

TEST(DoublingSizeQueueTest, EnqueueWorks) { testEnqueueWithUnsignedInt<QueueForTest>(); }

TEST(DoublingSizeQueueTest, DequeueWorks) { testDequeueWithUnsignedInt<QueueForTest>(); }

TEST(DoublingSizeQueueTest, GetContainerSizeWorks) {
    QueueForTest queue1;
    QueueForTest queue2;
    queue2.enqueue(10U);
    queue2.enqueue(5U);
    queue2.enqueue(4U);

    EXPECT_EQ(1U, queue1.getContainerSize());
    EXPECT_EQ(4U, queue2.getContainerSize());
}

TEST(DoublingSizeQueueTest, PushWorksWithDoublingContainerSize) {
    QueueForTest queue;
    EXPECT_EQ(1U, queue.getContainerSize());

    queue.enqueue(1U);
    queue.enqueue(2U);
    EXPECT_EQ(2U, queue.getContainerSize());

    queue.enqueue(3U);
    EXPECT_EQ(4U, queue.getContainerSize());

    queue.enqueue(4U);
    queue.enqueue(5U);
    EXPECT_EQ(8U, queue.getContainerSize());
}

TEST(DoublingSizeQueueTest, PopWorksWithHalvingContainerSize) {
    QueueForTest queue;

    queue.enqueue(1U);
    queue.enqueue(2U);
    queue.enqueue(3U);
    queue.enqueue(4U);
    queue.enqueue(5U);
    EXPECT_EQ(8U, queue.getContainerSize());

    EXPECT_EQ(1U, queue.dequeue());
    EXPECT_EQ(2U, queue.dequeue());
    EXPECT_EQ(3U, queue.dequeue());
    EXPECT_EQ(4U, queue.getContainerSize());

    EXPECT_EQ(4U, queue.dequeue());
    EXPECT_EQ(2U, queue.getContainerSize());

    EXPECT_EQ(5U, queue.dequeue());
    EXPECT_EQ(1U, queue.getContainerSize());
}

TEST(DoublingSizeQueueTest, DISABLED_DequeueWorksWithAssertionWhenItsEmpty)  // disabled because it takes too long
{
    testDequeueAssertionWhenEmptyWithUnsignedInt<QueueForTest>();
}

}  // namespace algorithm

}  // namespace alba
