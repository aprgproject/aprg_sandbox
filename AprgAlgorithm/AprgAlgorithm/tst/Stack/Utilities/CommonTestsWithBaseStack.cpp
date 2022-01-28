#include <Stack/Utilities/CommonTestsWithBaseStack.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

namespace CommonTestsWithBaseStack
{

void performIsEmptyTestWhenEmpty(BaseStackForUnsignedInt & stack)
{
    EXPECT_TRUE(stack.isEmpty());
}

void performIsEmptyTestWhenNotEmpty(BaseStackForUnsignedInt & stack)
{
    stack.push(10U);

    EXPECT_FALSE(stack.isEmpty());
}

void performGetSizeTestWhenEmpty(BaseStackForUnsignedInt & stack)
{
    EXPECT_EQ(0U, stack.getSize());
}

void performGetSizeTestWhenNotEmpty(BaseStackForUnsignedInt & stack)
{
    stack.push(10U);
    stack.push(5U);
    stack.push(4U);

    EXPECT_EQ(3U, stack.getSize());
}

void performPushTest(BaseStackForUnsignedInt & stack)
{
    stack.push(1U);
    stack.push(2U);
    stack.push(3U);

    ASSERT_EQ(3U, stack.getSize());
    EXPECT_EQ(3U, stack.pop());
    EXPECT_EQ(2U, stack.pop());
    EXPECT_EQ(1U, stack.pop());
}

void performPopTest(BaseStackForUnsignedInt & stack)
{    stack.push(1U);
    stack.push(2U);
    stack.push(3U);

    EXPECT_EQ(3U, stack.pop());
    EXPECT_EQ(2U, stack.pop());
    EXPECT_EQ(1U, stack.pop());
    ASSERT_EQ(0U, stack.getSize());
}

void performPopAssertionTestWhenEmpty(BaseStackForUnsignedInt & stack)
{
    EXPECT_DEATH(stack.pop(), "Assertion failed!");
}
}

}
