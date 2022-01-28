#include <Stack/FixedSizeStack.hpp>
#include <Stack/Utilities/CommonTestsWithBaseStack.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseStack;
using namespace std;

namespace alba
{

namespace
{
using StackForUnsignedInt = FixedSizeStack<unsigned int, 10U>;
}

TEST(FixedSizeStackTest, IsEmptyWorksWhenEmpty)
{
    StackForUnsignedInt stack;
    performIsEmptyTestWhenEmpty(stack);
}

TEST(FixedSizeStackTest, IsEmptyWorksWhenNotEmpty)
{
    StackForUnsignedInt stack;
    performIsEmptyTestWhenNotEmpty(stack);
}

TEST(FixedSizeStackTest, GetSizeWorksWhenEmpty)
{
    StackForUnsignedInt stack;
    performGetSizeTestWhenEmpty(stack);
}

TEST(FixedSizeStackTest, GetSizeWorksWhenNotEmpty)
{
    StackForUnsignedInt stack;
    performGetSizeTestWhenNotEmpty(stack);
}

TEST(FixedSizeStackTest, PushWorks)
{
    StackForUnsignedInt stack;
    performPushTest(stack);
}

TEST(FixedSizeStackTest, PopWorks)
{
    StackForUnsignedInt stack;
    performPopTest(stack);
}

TEST(FixedSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    StackForUnsignedInt stack;
    performPopAssertionTestWhenEmpty(stack);
}

TEST(FixedSizeStackTest, DISABLED_PushWorksWithAssertionWhenItReachesMaximumSize) //disabled because it takes too long
{
    StackForUnsignedInt stack;

    for(unsigned int i=0; i<10; i++)
    {
        stack.push(i);
    }
    EXPECT_DEATH(stack.push(100), "Assertion failed!");
}

}
