#include <Algorithm/Stack/FixedSizeStack.hpp>
#include <AlgorithmTests/Stack/Utilities/CommonTestsWithStack.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithStack;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using StackForTest = FixedSizeStack<int, 10>;
}

TEST(FixedSizeStackTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<StackForTest>(); }

TEST(FixedSizeStackTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<StackForTest>(); }

TEST(FixedSizeStackTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<StackForTest>(); }

TEST(FixedSizeStackTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<StackForTest>(); }

TEST(FixedSizeStackTest, PushWorks) { testPushWithInt<StackForTest>(); }

TEST(FixedSizeStackTest, PopWorks) { testPopWithInt<StackForTest>(); }

TEST(FixedSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty)  // disabled because it takes too long
{
    testPopAssertionWhenEmptyWithInt<StackForTest>();
}

TEST(FixedSizeStackTest, DISABLED_PushWorksWithAssertionWhenItReachesMaximumSize)  // disabled because it takes too long
{
    StackForTest stack;

    for (int i = 0; i < 10; i++) {
        stack.push(i);
    }
    EXPECT_DEATH(stack.push(100), "Assertion failed!");
}

}  // namespace algorithm

}  // namespace alba
