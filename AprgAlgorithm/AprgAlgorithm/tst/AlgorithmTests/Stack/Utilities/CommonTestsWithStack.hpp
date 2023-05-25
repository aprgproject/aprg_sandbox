#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace CommonTestsWithStack {

template <typename Stack>
void testIsEmptyWhenEmptyWithInt() {
    Stack stack;

    EXPECT_TRUE(stack.isEmpty());
}

template <typename Stack>
void testIsEmptyWhenNotEmptyWithInt() {
    Stack stack;
    stack.push(10);

    EXPECT_FALSE(stack.isEmpty());
}

template <typename Stack>
void testGetSizeWhenEmptyWithInt() {
    Stack stack;

    EXPECT_EQ(0, stack.getSize());
}

template <typename Stack>
void testGetSizeWhenNotEmptyWithInt() {
    Stack stack;
    stack.push(10);
    stack.push(5);
    stack.push(4);

    EXPECT_EQ(3, stack.getSize());
}

template <typename Stack>
void testPushWithInt() {
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    ASSERT_EQ(3, stack.getSize());
    EXPECT_EQ(3, stack.pop());
    EXPECT_EQ(2, stack.pop());
    EXPECT_EQ(1, stack.pop());
}

template <typename Stack>
void testPopWithInt() {
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(3, stack.pop());
    EXPECT_EQ(2, stack.pop());
    EXPECT_EQ(1, stack.pop());
    ASSERT_EQ(0, stack.getSize());
}

template <typename Stack>
void testPopAssertionWhenEmptyWithInt() {
    Stack stack;

    EXPECT_DEATH(stack.pop(), "Assertion failed!");
}

}  // namespace CommonTestsWithStack

}  // namespace algorithm

}  // namespace alba
