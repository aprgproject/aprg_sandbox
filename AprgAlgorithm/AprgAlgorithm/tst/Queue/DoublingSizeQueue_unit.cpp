#include <Queue/DoublingSizeQueue.hpp>
#include <Queue/Utilities/CommonTestsWithBaseQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseQueue;
using namespace std;

namespace alba
{

namespace
{
using QueueForUnsignedInt = DoublingSizeQueue<unsigned int>;
}

TEST(DoublingSizeQueueTest, IsEmptyWorksWhenEmpty)
{
    QueueForUnsignedInt queue;
    performIsEmptyTestWhenEmpty(queue);
}

TEST(DoublingSizeQueueTest, IsEmptyWorksWhenNotEmpty)
{
    QueueForUnsignedInt queue;
    performIsEmptyTestWhenNotEmpty(queue);
}

TEST(DoublingSizeQueueTest, GetSizeWorksWhenEmpty)
{
    QueueForUnsignedInt queue;
    performGetSizeTestWhenEmpty(queue);
}

TEST(DoublingSizeQueueTest, GetSizeWorksWhenNotEmpty)
{
    QueueForUnsignedInt queue;
    performGetSizeTestWhenNotEmpty(queue);
}

TEST(DoublingSizeQueueTest, EnqueueWorks)
{
    QueueForUnsignedInt queue;
    performEnqueueTest(queue);
}

TEST(DoublingSizeQueueTest, DequeueWorks)
{
    QueueForUnsignedInt queue;
    performDequeueTest(queue);
}

TEST(DoublingSizeQueueTest, DISABLED_DequeueWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    QueueForUnsignedInt queue;
    performDequeueAssertionTestWhenEmpty(queue);
}

}
