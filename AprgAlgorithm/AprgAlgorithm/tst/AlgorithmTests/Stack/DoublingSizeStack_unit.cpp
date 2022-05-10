#include <Algorithm/Stack/DoublingSizeStack.hpp>
#include <AlgorithmTests/Stack/Utilities/CommonTestsWithStack.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithStack;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using StackForTest = DoublingSizeStack<unsigned int>;
}

TEST(DoublingSizeStackTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedInt<StackForTest>();
}

TEST(DoublingSizeStackTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedInt<StackForTest>();
}

TEST(DoublingSizeStackTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedInt<StackForTest>();
}

TEST(DoublingSizeStackTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedInt<StackForTest>();
}

TEST(DoublingSizeStackTest, PushWorks)
{
    testPushWithUnsignedInt<StackForTest>();
}

TEST(DoublingSizeStackTest, PopWorks)
{
    testPopWithUnsignedInt<StackForTest>();
}

TEST(DoublingSizeStackTest, GetContainerSizeWorks)
{
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10U);
    stack2.push(5U);
    stack2.push(4U);

    EXPECT_EQ(1U, stack1.getContainerSize());
    EXPECT_EQ(4U, stack2.getContainerSize());
}

TEST(DoublingSizeStackTest, PushWorksWithDoublingContainerSize)
{
    StackForTest stack;
    EXPECT_EQ(1U, stack.getContainerSize());

    stack.push(1U);
    stack.push(2U);
    EXPECT_EQ(2U, stack.getContainerSize());

    stack.push(3U);
    EXPECT_EQ(4U, stack.getContainerSize());

    stack.push(4U);
    stack.push(5U);
    EXPECT_EQ(8U, stack.getContainerSize());
}

TEST(DoublingSizeStackTest, PopWorksWithHalvingContainerSize)
{
    StackForTest stack;

    stack.push(1U);
    stack.push(2U);
    stack.push(3U);
    stack.push(4U);
    stack.push(5U);
    EXPECT_EQ(8U, stack.getContainerSize());

    EXPECT_EQ(5U, stack.pop());
    EXPECT_EQ(4U, stack.pop());
    EXPECT_EQ(3U, stack.pop());
    EXPECT_EQ(4U, stack.getContainerSize());

    EXPECT_EQ(2U, stack.pop());
    EXPECT_EQ(2U, stack.getContainerSize());

    EXPECT_EQ(1U, stack.pop());
    EXPECT_EQ(1U, stack.getContainerSize());
}

TEST(DoublingSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    testPopAssertionWhenEmptyWithUnsignedInt<StackForTest>();
}

}

}
