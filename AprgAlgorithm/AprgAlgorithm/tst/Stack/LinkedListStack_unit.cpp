#include <Stack/LinkedListStack.hpp>
#include <Stack/Utilities/CommonTestsWithBaseStack.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseStack;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using StackForUnsignedInt = LinkedListStack<unsigned int>;}

TEST(LinkedListStackTest, IsEmptyWorksWhenEmpty)
{    StackForUnsignedInt stack;
    performIsEmptyTestWhenEmpty(stack);
}

TEST(LinkedListStackTest, IsEmptyWorksWhenNotEmpty)
{
    StackForUnsignedInt stack;
    performIsEmptyTestWhenNotEmpty(stack);
}

TEST(LinkedListStackTest, GetSizeWorksWhenEmpty)
{
    StackForUnsignedInt stack;
    performGetSizeTestWhenEmpty(stack);
}

TEST(LinkedListStackTest, GetSizeWorksWhenNotEmpty)
{
    StackForUnsignedInt stack;
    performGetSizeTestWhenNotEmpty(stack);
}

TEST(LinkedListStackTest, PushWorks)
{
    StackForUnsignedInt stack;
    performPushTest(stack);
}

TEST(LinkedListStackTest, PopWorks)
{
    StackForUnsignedInt stack;
    performPopTest(stack);
}

TEST(LinkedListStackTest, DISABLED_PopWorksWithAssertionWhenItsEmpty) //disabled because it takes too long
{
    StackForUnsignedInt stack;
    performPopAssertionTestWhenEmpty(stack);
}

}

}