#include <Algorithm/Queue/FixedSizeCircularQueue.hpp>
#include <AlgorithmTests/Queue/Utilities/CommonTestsWithQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithQueue;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using QueueForTest = FixedSizeCircularQueue<int, 10>;
}

TEST(FixedSizeCircularQueueTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<QueueForTest>(); }

TEST(FixedSizeCircularQueueTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<QueueForTest>(); }

TEST(FixedSizeCircularQueueTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<QueueForTest>(); }

TEST(FixedSizeCircularQueueTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<QueueForTest>(); }

TEST(FixedSizeCircularQueueTest, EnqueueWorks) { testEnqueueWithInt<QueueForTest>(); }

TEST(FixedSizeCircularQueueTest, DequeueWorks) { testDequeueWithInt<QueueForTest>(); }

// disabled because it takes too long
TEST(FixedSizeCircularQueueTest, DISABLED_DequeueWorksWithAssertionWhenItsEmpty) {
    testDequeueAssertionWhenEmptyWithInt<QueueForTest>();
}

// disabled because it takes too long
TEST(FixedSizeCircularQueueTest, DISABLED_PushWorksWithAssertionWhenItReachesMaximumSize) {
    QueueForTest queue;

    for (int i = 0; i < 9; i++) {
        queue.enqueue(i);
    }
    EXPECT_DEATH(queue.enqueue(100), "Assertion failed!");
}

}  // namespace algorithm

}  // namespace alba
