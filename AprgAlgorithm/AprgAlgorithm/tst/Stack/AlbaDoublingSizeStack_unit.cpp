#include <Stack/AlbaDoublingSizeStack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using StackForTest = AlbaDoublingSizeStack<unsigned int>;
}

TEST(AlbaDoublingSizeStackTest, IsEmptyWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);

    EXPECT_TRUE(stack1.isEmpty());
    EXPECT_FALSE(stack2.isEmpty());
}

TEST(AlbaDoublingSizeStackTest, GetStackSizeWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);
    stack2.push(5U);
    stack2.push(4U);

    EXPECT_EQ(0U, stack1.getStackSize());
    EXPECT_EQ(3U, stack2.getStackSize());
}

TEST(AlbaDoublingSizeStackTest, GetContainerSizeWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);
    stack2.push(5U);
    stack2.push(4U);

    EXPECT_EQ(1U, stack1.getContainerSize());
    EXPECT_EQ(4U, stack2.getContainerSize());
}

TEST(AlbaDoublingSizeStackTest, PushWorks)
{
    StackForTest stack;

    stack.push(5U);

    EXPECT_EQ(5U, stack.pop());
}

TEST(AlbaDoublingSizeStackTest, PushWorksWithDoublingContainerSize)
{
    StackForTest stack;
    EXPECT_EQ(1U, stack.getContainerSize());

    stack.push(10U);
    stack.push(10U);
    EXPECT_EQ(2U, stack.getContainerSize());

    stack.push(10U);
    EXPECT_EQ(4U, stack.getContainerSize());

    stack.push(10U);
    stack.push(10U);
    EXPECT_EQ(8U, stack.getContainerSize());
}

TEST(AlbaDoublingSizeStackTest, PopWorks)
{
    StackForTest stack;
    stack.push(5U);

    EXPECT_EQ(5U, stack.pop());
}

TEST(AlbaDoublingSizeStackTest, PopWorksWithHalvingContainerSize)
{
    StackForTest stack;

    stack.push(10U);
    stack.push(10U);
    stack.push(10U);
    stack.push(10U);
    stack.push(10U);
    EXPECT_EQ(8U, stack.getContainerSize());

    EXPECT_EQ(10U, stack.pop());
    EXPECT_EQ(10U, stack.pop());
    EXPECT_EQ(10U, stack.pop());
    EXPECT_EQ(4U, stack.getContainerSize());

    EXPECT_EQ(10U, stack.pop());
    EXPECT_EQ(2U, stack.getContainerSize());

    EXPECT_EQ(10U, stack.pop());
    EXPECT_EQ(1U, stack.getContainerSize());
}

TEST(AlbaDoublingSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    StackForTest stack;

    EXPECT_DEATH(stack.pop(), "Assertion failed!");
}

}
