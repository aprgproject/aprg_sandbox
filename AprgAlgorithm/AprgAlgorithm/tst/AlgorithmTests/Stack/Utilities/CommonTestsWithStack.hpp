#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithStack
{

template <typename Stack>
void testIsEmptyWhenEmptyWithUnsignedInt()
{
    Stack stack;

    EXPECT_TRUE(stack.isEmpty());
}

template <typename Stack>
void testIsEmptyWhenNotEmptyWithUnsignedInt()
{
    Stack stack;
    stack.push(10U);

    EXPECT_FALSE(stack.isEmpty());
}

template <typename Stack>
void testGetSizeWhenEmptyWithUnsignedInt()
{
    Stack stack;

    EXPECT_EQ(0U, stack.getSize());
}

template <typename Stack>
void testGetSizeWhenNotEmptyWithUnsignedInt()
{
    Stack stack;
    stack.push(10U);
    stack.push(5U);
    stack.push(4U);

    EXPECT_EQ(3U, stack.getSize());
}

template <typename Stack>
void testPushWithUnsignedInt()
{
    Stack stack;
    stack.push(1U);
    stack.push(2U);
    stack.push(3U);

    ASSERT_EQ(3U, stack.getSize());
    EXPECT_EQ(3U, stack.pop());
    EXPECT_EQ(2U, stack.pop());
    EXPECT_EQ(1U, stack.pop());
}

template <typename Stack>
void testPopWithUnsignedInt()
{
    Stack stack;
    stack.push(1U);
    stack.push(2U);
    stack.push(3U);

    EXPECT_EQ(3U, stack.pop());
    EXPECT_EQ(2U, stack.pop());
    EXPECT_EQ(1U, stack.pop());
    ASSERT_EQ(0U, stack.getSize());
}

template <typename Stack>
void testPopAssertionWhenEmptyWithUnsignedInt()
{
    Stack stack;

    EXPECT_DEATH(stack.pop(), "Assertion failed!");
}

}

}

}
