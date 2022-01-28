#include <Stack/DoublingSizeStack.hpp>
#include <Stack/Utilities/CommonTestsWithBaseStack.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseStack;
using namespace std;

namespace alba{

namespace
{
using StackForUnsignedInt = DoublingSizeStack<unsigned int>;
}

TEST(DoublingSizeStackTest, IsEmptyWorksWhenEmpty)
{
    StackForUnsignedInt stack;
    performIsEmptyTestWhenEmpty(stack);
}

TEST(DoublingSizeStackTest, IsEmptyWorksWhenNotEmpty)
{
    StackForUnsignedInt stack;
    performIsEmptyTestWhenNotEmpty(stack);
}

TEST(DoublingSizeStackTest, GetSizeWorksWhenEmpty)
{
    StackForUnsignedInt stack;
    performGetSizeTestWhenEmpty(stack);
}

TEST(DoublingSizeStackTest, GetSizeWorksWhenNotEmpty)
{
    StackForUnsignedInt stack;
    performGetSizeTestWhenNotEmpty(stack);
}

TEST(DoublingSizeStackTest, PushWorks)
{
    StackForUnsignedInt stack;
    performPushTest(stack);
}

TEST(DoublingSizeStackTest, PopWorks)
{
    StackForUnsignedInt stack;
    performPopTest(stack);
}

TEST(DoublingSizeStackTest, GetContainerSizeWorks)
{
    StackForUnsignedInt stack1;
    StackForUnsignedInt stack2;
    stack2.push(10U);
    stack2.push(5U);
    stack2.push(4U);
    EXPECT_EQ(1U, stack1.getContainerSize());
    EXPECT_EQ(4U, stack2.getContainerSize());
}

TEST(DoublingSizeStackTest, PushWorksWithDoublingContainerSize)
{
    StackForUnsignedInt stack;
    EXPECT_EQ(1U, stack.getContainerSize());

    stack.push(10U);    stack.push(10U);
    EXPECT_EQ(2U, stack.getContainerSize());

    stack.push(10U);
    EXPECT_EQ(4U, stack.getContainerSize());

    stack.push(10U);
    stack.push(10U);
    EXPECT_EQ(8U, stack.getContainerSize());
}

TEST(DoublingSizeStackTest, PopWorksWithHalvingContainerSize)
{
    StackForUnsignedInt stack;

    stack.push(10U);
    stack.push(10U);    stack.push(10U);
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

TEST(DoublingSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    StackForUnsignedInt stack;
    performPopAssertionTestWhenEmpty(stack);
}

}