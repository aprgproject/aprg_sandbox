#include <Algorithm/Queue/DoublingSizeQueue.hpp>
#include <AlgorithmTests/Queue/Utilities/CommonTestsWithQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithQueue;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using QueueForTest = DoublingSizeQueue<unsigned int>;
}

TEST(DoublingSizeQueueTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedInt<QueueForTest>();
}

TEST(DoublingSizeQueueTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedInt<QueueForTest>();
}

TEST(DoublingSizeQueueTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedInt<QueueForTest>();
}

TEST(DoublingSizeQueueTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedInt<QueueForTest>();
}

TEST(DoublingSizeQueueTest, EnqueueWorks)
{
    testEnqueueWithUnsignedInt<QueueForTest>();
}

TEST(DoublingSizeQueueTest, DequeueWorks)
{
    testDequeueWithUnsignedInt<QueueForTest>();
}

TEST(DoublingSizeQueueTest, DISABLED_DequeueWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    testDequeueAssertionWhenEmptyWithUnsignedInt<QueueForTest>();
}

}

}
