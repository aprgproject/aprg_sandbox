#include <AprgUniqueProblems/SearchProblems/FindTheMissingNumber/FindTheMissingNumber.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using QueryForTest = FindTheMissingNumber<ValuesForTest>;
}

TEST(FindTheMissingNumberTest, GetTheMissingNumberWorksOnEmpty)
{
    ValuesForTest valuesForTest;
    QueryForTest query;

    EXPECT_EQ(1U, query.getTheMissingNumberUsingSum(valuesForTest));
    EXPECT_EQ(1U, query.getTheMissingNumberUsingXor(valuesForTest));
}

TEST(FindTheMissingNumberTest, GetTheMissingNumberWorksOnOneValue)
{
    ValuesForTest valuesForTest{2U};
    QueryForTest query;

    EXPECT_EQ(1U, query.getTheMissingNumberUsingSum(valuesForTest));
    EXPECT_EQ(1U, query.getTheMissingNumberUsingXor(valuesForTest));
}

TEST(FindTheMissingNumberTest, GetTheMissingNumberWorksOnExample1)
{
    ValuesForTest valuesForTest{1U,2U,3U,5U};
    QueryForTest query;

    EXPECT_EQ(4U, query.getTheMissingNumberUsingSum(valuesForTest));
    EXPECT_EQ(4U, query.getTheMissingNumberUsingXor(valuesForTest));
}

TEST(FindTheMissingNumberTest, GetTheMissingNumberWorksOnExample2)
{
    ValuesForTest valuesForTest{1U,2U,4U,6U,3U,7U,8U};
    QueryForTest query;

    EXPECT_EQ(5U, query.getTheMissingNumberUsingSum(valuesForTest));
    EXPECT_EQ(5U, query.getTheMissingNumberUsingXor(valuesForTest));
}
}

}
