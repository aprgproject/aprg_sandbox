#include <Algorithm/Search/UniqueProblems/FindCommonElementsInThreeSortedContainers/FindCommonElementsInThreeSortedContainers.hpp>

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
using QueryForTest = FindCommonElementsInThreeSortedContainers<ValuesForTest>;
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenFirstContainerIsEmpty)
{
    ValuesForTest values1{1U, 5U, 10U, 20U, 40U, 80U};
    ValuesForTest values2;
    ValuesForTest values3;
    QueryForTest query;

    ValuesForTest expectedValues;
    EXPECT_EQ(expectedValues, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenSecondContainerIsEmpty)
{
    ValuesForTest values1;
    ValuesForTest values2{6U, 7U, 20U, 80U, 100U};
    ValuesForTest values3;
    QueryForTest query;

    ValuesForTest expectedValues;
    EXPECT_EQ(expectedValues, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenThirdContainerIsEmpty)
{
    ValuesForTest values1;
    ValuesForTest values2;
    ValuesForTest values3{3U, 4U, 15U, 20U, 30U, 70U, 80U, 120U};
    QueryForTest query;

    ValuesForTest expectedValues;
    EXPECT_EQ(expectedValues, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksOnExample1)
{
    ValuesForTest values1{1U, 5U, 10U, 20U, 40U, 80U};
    ValuesForTest values2{6U, 7U, 20U, 80U, 100U};
    ValuesForTest values3{3U, 4U, 15U, 20U, 30U, 70U, 80U, 120U};
    QueryForTest query;

    ValuesForTest expectedValues1{20U, 80U};
    EXPECT_EQ(expectedValues1, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksOnExample2)
{
    ValuesForTest values1{1U, 5U, 5U};
    ValuesForTest values2{3U, 4U, 5U, 5U, 10U};
    ValuesForTest values3{5U, 5U, 10U, 20U};
    QueryForTest query;

    ValuesForTest expectedValues1{5U, 5U};
    EXPECT_EQ(expectedValues1, query.getCommonElements(values1, values2, values3));
}

}

}
