#include <Stack/LinkedListStack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using StackForTest = LinkedListStack<unsigned int>;
}

TEST(LinkedListStackTest, IsEmptyWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);

    EXPECT_TRUE(stack1.isEmpty());
    EXPECT_FALSE(stack2.isEmpty());
}

TEST(LinkedListStackTest, GetSizeWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);
    stack2.push(5U);
    stack2.push(4U);

    EXPECT_EQ(0U, stack1.getSize());
    EXPECT_EQ(3U, stack2.getSize());
}

TEST(LinkedListStackTest, PushWorks)
{
    StackForTest stack;

    stack.push(1U);
    stack.push(2U);
    stack.push(3U);

    EXPECT_EQ(3U, stack.getSize());
    EXPECT_EQ(3U, stack.pop());
    EXPECT_EQ(2U, stack.pop());
    EXPECT_EQ(1U, stack.pop());
}

TEST(LinkedListStackTest, PopWorks)
{
    StackForTest stack;
    stack.push(1U);
    stack.push(2U);
    stack.push(3U);

    EXPECT_EQ(3U, stack.pop());
    EXPECT_EQ(2U, stack.pop());
    EXPECT_EQ(1U, stack.pop());
    EXPECT_EQ(0U, stack.getSize());
}

TEST(LinkedListStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    StackForTest stack;

    EXPECT_DEATH(stack.pop(), "Assertion failed!");
}

}
