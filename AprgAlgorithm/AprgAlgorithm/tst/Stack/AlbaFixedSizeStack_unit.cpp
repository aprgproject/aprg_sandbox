#include <Stack/AlbaFixedSizeStack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

using FixedStackForTest = AlbaFixedSizeStack<unsigned int, 10U>;

TEST(AlbaFixedSizeStackTest, IsEmptyWorks)
{
    FixedStackForTest stack1;
    FixedStackForTest stack2;
    stack2.push(10U);

    EXPECT_TRUE(stack1.isEmpty());
    EXPECT_FALSE(stack2.isEmpty());
}

TEST(AlbaFixedSizeStackTest, GetSizeWorks)
{
    FixedStackForTest stack1;
    FixedStackForTest stack2;
    stack2.push(10U);
    stack2.push(5U);
    stack2.push(4U);

    EXPECT_EQ(0U, stack1.getSize());
    EXPECT_EQ(3U, stack2.getSize());
}

TEST(AlbaFixedSizeStackTest, GetObjectsWorks)
{
    FixedStackForTest stack;
    stack.push(10U);
    stack.push(5U);
    stack.push(4U);

    FixedStackForTest::Objects const& objectsToVerify(stack.getObjects());

    EXPECT_EQ(10U, objectsToVerify.at(0));
    EXPECT_EQ(5U, objectsToVerify.at(1));
    EXPECT_EQ(4U, objectsToVerify.at(2));
}

TEST(AlbaFixedSizeStackTest, PushWorks)
{
    FixedStackForTest stack;

    stack.push(10U);

    FixedStackForTest::Objects const& objectsToVerify(stack.getObjects());
    EXPECT_EQ(1U, stack.getSize());
    EXPECT_EQ(10U, objectsToVerify.at(0));
}

TEST(AlbaFixedSizeStackTest, PopWorks)
{
    FixedStackForTest stack;
    stack.push(10U);
    stack.push(5U);
    stack.push(4U);

    EXPECT_EQ(4U, stack.pop());
    FixedStackForTest::Objects const& objectsToVerify(stack.getObjects());
    EXPECT_EQ(2U, stack.getSize());
    EXPECT_EQ(10U, objectsToVerify.at(0));
    EXPECT_EQ(5U, objectsToVerify.at(1));
}

TEST(AlbaFixedSizeStackTest, DISABLED_PushWorksWithAssertionWhenItReachesMaximumSize) //disabled because it takes too long
{
    FixedStackForTest stack;

    for(unsigned int i=0; i<10; i++)
    {
        stack.push(i);
    }
    EXPECT_DEATH(stack.push(100), "Assertion failed!");
}

TEST(AlbaFixedSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    FixedStackForTest stack;

    EXPECT_DEATH(stack.pop(), "Assertion failed!");
}

}
