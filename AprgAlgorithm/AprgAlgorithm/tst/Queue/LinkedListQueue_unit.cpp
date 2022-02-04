#include <Queue/LinkedListQueue.hpp>
#include <Queue/Utilities/CommonTestsWithBaseQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseQueue;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using QueueForUnsignedInt = LinkedListQueue<unsigned int>;}

TEST(LinkedListQueueTest, IsEmptyWorksWhenEmpty)
{    QueueForUnsignedInt queue;
    performIsEmptyTestWhenEmpty(queue);
}

TEST(LinkedListQueueTest, IsEmptyWorksWhenNotEmpty)
{
    QueueForUnsignedInt queue;
    performIsEmptyTestWhenNotEmpty(queue);
}

TEST(LinkedListQueueTest, GetSizeWorksWhenEmpty)
{
    QueueForUnsignedInt queue;
    performGetSizeTestWhenEmpty(queue);
}

TEST(LinkedListQueueTest, GetSizeWorksWhenNotEmpty)
{
    QueueForUnsignedInt queue;
    performGetSizeTestWhenNotEmpty(queue);
}

TEST(LinkedListQueueTest, EnqueueWorks)
{
    QueueForUnsignedInt queue;
    performEnqueueTest(queue);
}

TEST(LinkedListQueueTest, DequeueWorks)
{
    QueueForUnsignedInt queue;
    performDequeueTest(queue);
}

TEST(LinkedListQueueTest, DISABLED_DequeueWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    QueueForUnsignedInt queue;
    performDequeueAssertionTestWhenEmpty(queue);
}

}

}