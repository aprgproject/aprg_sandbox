#include <Algorithm/Stack/LinkedListStack.hpp>
#include <AlgorithmTests/Stack/Utilities/CommonTestsWithStack.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithStack;
using namespace std;

namespace alba{

namespace algorithm
{

namespace
{
using StackForTest = LinkedListStack<unsigned int>;
}

TEST(LinkedListStackTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedInt<StackForTest>();
}

TEST(LinkedListStackTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedInt<StackForTest>();
}

TEST(LinkedListStackTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedInt<StackForTest>();
}

TEST(LinkedListStackTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedInt<StackForTest>();
}

TEST(LinkedListStackTest, PushWorks)
{
    testPushWithUnsignedInt<StackForTest>();
}

TEST(LinkedListStackTest, PopWorks)
{
    testPopWithUnsignedInt<StackForTest>();
}

TEST(LinkedListStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    testPopAssertionWhenEmptyWithUnsignedInt<StackForTest>();
}

}
}