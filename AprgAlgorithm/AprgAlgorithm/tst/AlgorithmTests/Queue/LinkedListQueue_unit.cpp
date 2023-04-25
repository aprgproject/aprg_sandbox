#include <Algorithm/Queue/LinkedListQueue.hpp>
#include <AlgorithmTests/Queue/Utilities/CommonTestsWithQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithQueue;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using QueueForTest = LinkedListQueue<unsigned int>;
}

TEST(LinkedListQueueTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithUnsignedInt<QueueForTest>(); }

TEST(LinkedListQueueTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithUnsignedInt<QueueForTest>(); }

TEST(LinkedListQueueTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithUnsignedInt<QueueForTest>(); }

TEST(LinkedListQueueTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithUnsignedInt<QueueForTest>(); }

TEST(LinkedListQueueTest, EnqueueWorks) { testEnqueueWithUnsignedInt<QueueForTest>(); }

TEST(LinkedListQueueTest, DequeueWorks) { testDequeueWithUnsignedInt<QueueForTest>(); }

TEST(LinkedListQueueTest, DISABLED_DequeueWorksWithAssertionWhenItsEmpty)  // disabled because it takes too long
{
    testDequeueAssertionWhenEmptyWithUnsignedInt<QueueForTest>();
}

}  // namespace algorithm

}  // namespace alba
