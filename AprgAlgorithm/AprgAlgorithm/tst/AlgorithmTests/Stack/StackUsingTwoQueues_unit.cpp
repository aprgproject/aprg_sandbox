#include <Algorithm/Queue/DoublingSizeCircularQueue.hpp>
#include <Algorithm/Stack/StackUsingTwoQueues.hpp>
#include <AlgorithmTests/Stack/Utilities/CommonTestsWithStack.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithStack;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using StackForTest = StackUsingTwoQueues<int, DoublingSizeCircularQueue<int>>;
}

TEST(StackUsingTwoQueuesTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<StackForTest>(); }

TEST(StackUsingTwoQueuesTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<StackForTest>(); }

TEST(StackUsingTwoQueuesTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<StackForTest>(); }

TEST(StackUsingTwoQueuesTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<StackForTest>(); }

TEST(StackUsingTwoQueuesTest, PushWorks) { testPushWithInt<StackForTest>(); }

TEST(StackUsingTwoQueuesTest, PopWorks) { testPopWithInt<StackForTest>(); }

// disabled because it takes too long
TEST(StackUsingTwoQueuesTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) {
    testPopAssertionWhenEmptyWithInt<StackForTest>();
}

}  // namespace algorithm

}  // namespace alba
