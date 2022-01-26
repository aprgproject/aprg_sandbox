#include <Stack/FixedSizeStack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using StackForTest = FixedSizeStack<unsigned int, 10U>;
}

TEST(FixedSizeStackTest, IsEmptyWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);

    EXPECT_TRUE(stack1.isEmpty());
    EXPECT_FALSE(stack2.isEmpty());
}

TEST(FixedSizeStackTest, GetSizeWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);
    stack2.push(5U);
    stack2.push(4U);

    EXPECT_EQ(0U, stack1.getSize());
    EXPECT_EQ(3U, stack2.getSize());
}

TEST(FixedSizeStackTest, GetObjectsWorks)
{
    StackForTest stack;
    stack.push(10U);
    stack.push(5U);
    stack.push(4U);

    StackForTest::Objects const& objectsToVerify(stack.getObjects());

    EXPECT_EQ(10U, objectsToVerify.at(0));
    EXPECT_EQ(5U, objectsToVerify.at(1));
    EXPECT_EQ(4U, objectsToVerify.at(2));
}

TEST(FixedSizeStackTest, PushWorks)
{
    StackForTest stack;

    stack.push(10U);

    StackForTest::Objects const& objectsToVerify(stack.getObjects());
    EXPECT_EQ(1U, stack.getSize());
    EXPECT_EQ(10U, objectsToVerify.at(0));
}

TEST(FixedSizeStackTest, PopWorks)
{
    StackForTest stack;
    stack.push(10U);
    stack.push(5U);
    stack.push(4U);

    EXPECT_EQ(4U, stack.pop());
    StackForTest::Objects const& objectsToVerify(stack.getObjects());
    EXPECT_EQ(2U, stack.getSize());
    EXPECT_EQ(10U, objectsToVerify.at(0));
    EXPECT_EQ(5U, objectsToVerify.at(1));
}

TEST(FixedSizeStackTest, DISABLED_PushWorksWithAssertionWhenItReachesMaximumSize) //disabled because it takes too long
{
    StackForTest stack;

    for(unsigned int i=0; i<10; i++)
    {
        stack.push(i);
    }
    EXPECT_DEATH(stack.push(100), "Assertion failed!");
}

TEST(FixedSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    StackForTest stack;

    EXPECT_DEATH(stack.pop(), "Assertion failed!");
}

}
