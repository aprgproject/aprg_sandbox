#include <Algorithm/Queue/QueueUsingTwoStacks.hpp>
#include <Algorithm/Stack/DoublingSizeStack.hpp>
#include <AlgorithmTests/Queue/Utilities/CommonTestsWithQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithQueue;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using QueueForTest = QueueUsingTwoStacks<int, DoublingSizeStack<int>>;
}

TEST(QueueUsingTwoStacksTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<QueueForTest>(); }

TEST(QueueUsingTwoStacksTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<QueueForTest>(); }

TEST(QueueUsingTwoStacksTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<QueueForTest>(); }

TEST(QueueUsingTwoStacksTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<QueueForTest>(); }

TEST(QueueUsingTwoStacksTest, EnqueueWorks) { testEnqueueWithInt<QueueForTest>(); }

TEST(QueueUsingTwoStacksTest, DequeueWorks) { testDequeueWithInt<QueueForTest>(); }

// disabled because it takes too long
TEST(QueueUsingTwoStacksTest, DISABLED_DequeueWorksWithAssertionWhenItsEmpty) {
    testDequeueAssertionWhenEmptyWithInt<QueueForTest>();
}

}  // namespace algorithm

}  // namespace alba
