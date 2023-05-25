#include <Algorithm/Queue/LinkedListQueue.hpp>
#include <AlgorithmTests/Queue/Utilities/CommonTestsWithQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithQueue;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using QueueForTest = LinkedListQueue<int>;
}

TEST(LinkedListQueueTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<QueueForTest>(); }

TEST(LinkedListQueueTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<QueueForTest>(); }

TEST(LinkedListQueueTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<QueueForTest>(); }

TEST(LinkedListQueueTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<QueueForTest>(); }

TEST(LinkedListQueueTest, EnqueueWorks) { testEnqueueWithInt<QueueForTest>(); }

TEST(LinkedListQueueTest, DequeueWorks) { testDequeueWithInt<QueueForTest>(); }

TEST(LinkedListQueueTest, DISABLED_DequeueWorksWithAssertionWhenItsEmpty)  // disabled because it takes too long
{
    testDequeueAssertionWhenEmptyWithInt<QueueForTest>();
}

}  // namespace algorithm

}  // namespace alba
