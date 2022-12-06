#include <Algorithm/Search/UniqueProblems/FindThePairWithClosestToSumFromTwoSortedContainers/FindThePairWithClosestToSumFromTwoSortedContainers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = FindThePairWithClosestToSumFromTwoSortedContainers<ValuesForTest>;
}

TEST(FindThePairWithClosestToSumFromTwoSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenFirstContainerIsEmpty)
{
    ValuesForTest values1{1U, 4U, 5U, 7U};
    ValuesForTest values2;
    QueryForTest query;

    QueryForTest::ValuePair expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairThatIsClosestToSum(values1, values2, 32U));
}

TEST(FindThePairWithClosestToSumFromTwoSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenSecondContainerIsEmpty)
{
    ValuesForTest values1;
    ValuesForTest values2{10U, 20U, 30U, 40U};
    QueryForTest query;

    QueryForTest::ValuePair expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairThatIsClosestToSum(values1, values2, 32U));
}

TEST(FindThePairWithClosestToSumFromTwoSortedContainersTest, GetValuePairThatIsClosestToSumWorksOnExample1)
{
    ValuesForTest values1{1U, 4U, 5U, 7U};
    ValuesForTest values2{10U, 20U, 30U, 40U};
    QueryForTest query;

    QueryForTest::ValuePair expectedValuePair1{1U, 30U};
    QueryForTest::ValuePair expectedValuePair2{7U, 40U};
    EXPECT_EQ(expectedValuePair1, query.getValuePairThatIsClosestToSum(values1, values2, 32U));
    EXPECT_EQ(expectedValuePair2, query.getValuePairThatIsClosestToSum(values1, values2, 50U));
}

}

}
