#include <Algorithm/Stack/LinkedListStack.hpp>
#include <AlgorithmTests/Stack/Utilities/CommonTestsWithStack.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithStack;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using StackForTest = LinkedListStack<int>;
}

TEST(LinkedListStackTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<StackForTest>(); }

TEST(LinkedListStackTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<StackForTest>(); }

TEST(LinkedListStackTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<StackForTest>(); }

TEST(LinkedListStackTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<StackForTest>(); }

TEST(LinkedListStackTest, PushWorks) { testPushWithInt<StackForTest>(); }

TEST(LinkedListStackTest, PopWorks) { testPopWithInt<StackForTest>(); }

TEST(LinkedListStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty)  // disabled because it takes too long
{
    testPopAssertionWhenEmptyWithInt<StackForTest>();
}

}  // namespace algorithm

}  // namespace alba
