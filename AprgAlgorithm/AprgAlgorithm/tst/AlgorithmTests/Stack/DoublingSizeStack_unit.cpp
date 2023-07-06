#include <Algorithm/Stack/DoublingSizeStack.hpp>
#include <AlgorithmTests/Stack/Utilities/CommonTestsWithStack.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithStack;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using StackForTest = DoublingSizeStack<int>;
}

TEST(DoublingSizeStackTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<StackForTest>(); }

TEST(DoublingSizeStackTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<StackForTest>(); }

TEST(DoublingSizeStackTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<StackForTest>(); }

TEST(DoublingSizeStackTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<StackForTest>(); }

TEST(DoublingSizeStackTest, PushWorks) { testPushWithInt<StackForTest>(); }

TEST(DoublingSizeStackTest, PopWorks) { testPopWithInt<StackForTest>(); }

TEST(DoublingSizeStackTest, GetContainerSizeWorks) {
    StackForTest stack1;
    StackForTest stack2;
    stack2.push(10);
    stack2.push(5);
    stack2.push(4);

    EXPECT_EQ(1, stack1.getContainerSize());
    EXPECT_EQ(4, stack2.getContainerSize());
}

TEST(DoublingSizeStackTest, MinimumContainerSizeIsContained) {
    StackForTest stack;
    stack.push(10);
    stack.pop();

    EXPECT_EQ(StackForTest::MINUMUM_CONTAINER_SIZE, stack.getContainerSize());
}

TEST(DoublingSizeStackTest, PushWorksWithDoublingContainerSize) {
    StackForTest stack;
    EXPECT_EQ(1, stack.getContainerSize());

    stack.push(1);
    stack.push(2);
    EXPECT_EQ(2, stack.getContainerSize());

    stack.push(3);
    EXPECT_EQ(4, stack.getContainerSize());

    stack.push(4);
    stack.push(5);
    EXPECT_EQ(8, stack.getContainerSize());
}

TEST(DoublingSizeStackTest, PopWorksWithHalvingContainerSize) {
    StackForTest stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    EXPECT_EQ(8, stack.getContainerSize());

    EXPECT_EQ(5, stack.pop());
    EXPECT_EQ(4, stack.pop());
    EXPECT_EQ(3, stack.pop());
    EXPECT_EQ(4, stack.getContainerSize());

    EXPECT_EQ(2, stack.pop());
    EXPECT_EQ(2, stack.getContainerSize());

    EXPECT_EQ(1, stack.pop());
    EXPECT_EQ(1, stack.getContainerSize());
}

// disabled because it takes too long
TEST(DoublingSizeStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) {
    testPopAssertionWhenEmptyWithInt<StackForTest>();
}

}  // namespace algorithm

}  // namespace alba
