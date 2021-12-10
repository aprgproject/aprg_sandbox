#include <Stack/AlbaLinkedListStack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using StackForTest = AlbaLinkedListStack<unsigned int>;
}

TEST(AlbaLinkedListStackTest, IsEmptyWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);

    EXPECT_TRUE(stack1.isEmpty());
    EXPECT_FALSE(stack2.isEmpty());
}

TEST(AlbaLinkedListStackTest, GetSizeWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);
    stack2.push(5U);
    stack2.push(4U);

    EXPECT_EQ(0U, stack1.getSize());
    EXPECT_EQ(3U, stack2.getSize());
}

TEST(AlbaLinkedListStackTest, PushWorks)
{
    StackForTest stack;

    stack.push(5U);

    EXPECT_EQ(5U, stack.pop());
}

TEST(AlbaLinkedListStackTest, PopWorks)
{
    StackForTest stack;
    stack.push(5U);

    EXPECT_EQ(5U, stack.pop());
}

TEST(AlbaLinkedListStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    StackForTest stack;

    EXPECT_DEATH(stack.pop(), "Assertion failed!");
}

}
