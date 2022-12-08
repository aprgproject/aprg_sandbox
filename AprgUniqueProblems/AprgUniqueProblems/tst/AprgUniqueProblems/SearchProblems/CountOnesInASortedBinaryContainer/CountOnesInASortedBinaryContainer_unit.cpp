#include <AprgUniqueProblems/SearchProblems/CountOnesInASortedBinaryContainer/CountOnesInASortedBinaryContainer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<bool>;
using QueryForTest = CountOnesInASortedBinaryContainer<ValuesForTest>;
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnEmpty)
{
    ValuesForTest valuesForTest;
    QueryForTest query;

    EXPECT_EQ(0U, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnOneValue)
{
    ValuesForTest valuesForTest{true};
    QueryForTest query;

    EXPECT_EQ(1U, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnWhenAllZeroes)
{
    ValuesForTest valuesForTest{false, false, false, false, false, false, false};
    QueryForTest query;

    EXPECT_EQ(0U, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnWhenAllOnes)
{
    ValuesForTest valuesForTest{true, true, true, true, true, true, true};
    QueryForTest query;

    EXPECT_EQ(7U, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

TEST(CountOnesInASortedBinaryContainerTest, GetNumberOfOnesInASortedBinaryContainerWorksOnExample1)
{
    ValuesForTest valuesForTest{false, false, false, true, true, true, true};
    QueryForTest query;

    EXPECT_EQ(4U, query.getNumberOfOnesInASortedBinaryContainer(valuesForTest));
}

}

}
