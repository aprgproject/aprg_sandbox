#include <Stack/AlbaFixedSizeStack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using StackForTest = AlbaFixedSizeStack<unsigned int, 10U>;
}

TEST(AlbaFixedSizeStackTest, IsEmptyWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);

    EXPECT_TRUE(stack1.isEmpty());
    EXPECT_FALSE(stack2.isEmpty());
}

TEST(AlbaFixedSizeStackTest, GetSizeWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);
    stack2.push(5U);
    stack2.push(4U);

    EXPECT_EQ(0U, stack1.getSize());
    EXPECT_EQ(3U, stack2.getSize());
}

TEST(AlbaFixedSizeStackTest, GetObjectsWorks)
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

TEST(AlbaFixedSizeStackTest, PushWorks)
{
    StackForTest stack;

    stack.push(10U);

    StackForTest::Objects const& objectsToVerify(stack.getObjects());
    EXPECT_EQ(1U, stack.getSize());
    EXPECT_EQ(10U, objectsToVerify.at(0));
}

TEST(AlbaFixedSizeStackTest, PopWorks)
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

TEST(AlbaFixedSizeStackTest, DISABLED_PushWorksWithAssertionWhenItReachesMaximumSize) //disabled because it takes too long
{
    StackForTest stack;

    for(unsigned int i=0; i<10; i++)
    {
        stack.push(i);
    }
    EXPECT_DEATH(stack.push(100), "Assertion failed!");
}

TEST(AlbaFixedSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    StackForTest stack;

    EXPECT_DEATH(stack.pop(), "Assertion failed!");
}

}
