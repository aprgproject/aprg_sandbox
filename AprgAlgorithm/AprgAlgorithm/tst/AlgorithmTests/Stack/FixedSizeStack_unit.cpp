#include <Algorithm/Stack/FixedSizeStack.hpp>
#include <AlgorithmTests/Stack/Utilities/CommonTestsWithStack.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithStack;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using StackForTest = FixedSizeStack<unsigned int, 10U>;
}

TEST(FixedSizeStackTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithUnsignedInt<StackForTest>(); }

TEST(FixedSizeStackTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithUnsignedInt<StackForTest>(); }

TEST(FixedSizeStackTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithUnsignedInt<StackForTest>(); }

TEST(FixedSizeStackTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithUnsignedInt<StackForTest>(); }

TEST(FixedSizeStackTest, PushWorks) { testPushWithUnsignedInt<StackForTest>(); }

TEST(FixedSizeStackTest, PopWorks) { testPopWithUnsignedInt<StackForTest>(); }

TEST(FixedSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty)  // disabled because it takes too long
{
    testPopAssertionWhenEmptyWithUnsignedInt<StackForTest>();
}

TEST(FixedSizeStackTest, DISABLED_PushWorksWithAssertionWhenItReachesMaximumSize)  // disabled because it takes too long
{
    StackForTest stack;

    for (unsigned int i = 0; i < 10; i++) {
        stack.push(i);
    }
    EXPECT_DEATH(stack.push(100), "Assertion failed!");
}

}  // namespace algorithm

}  // namespace alba
