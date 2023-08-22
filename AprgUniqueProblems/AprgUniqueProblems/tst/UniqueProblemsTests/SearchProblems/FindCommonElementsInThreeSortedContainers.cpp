#include <UniqueProblems/SearchProblems/FindCommonElementsInThreeSortedContainers.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = FindCommonElementsInThreeSortedContainers<ValuesForTest>;
}  // namespace

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenFirstContainerIsEmpty) {
    ValuesForTest values1{1, 5, 10, 20, 40, 80};
    ValuesForTest values2;
    ValuesForTest values3;
    QueryForTest query;

    ValuesForTest expectedValues;
    EXPECT_EQ(expectedValues, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenSecondContainerIsEmpty) {
    ValuesForTest values1;
    ValuesForTest values2{6, 7, 20, 80, 100};
    ValuesForTest values3;
    QueryForTest query;

    ValuesForTest expectedValues;
    EXPECT_EQ(expectedValues, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksWhenThirdContainerIsEmpty) {
    ValuesForTest values1;
    ValuesForTest values2;
    ValuesForTest values3{3, 4, 15, 20, 30, 70, 80, 120};
    QueryForTest query;

    ValuesForTest expectedValues;
    EXPECT_EQ(expectedValues, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksOnExample1) {
    ValuesForTest values1{1, 5, 10, 20, 40, 80};
    ValuesForTest values2{6, 7, 20, 80, 100};
    ValuesForTest values3{3, 4, 15, 20, 30, 70, 80, 120};
    QueryForTest query;

    ValuesForTest expectedValues1{20, 80};
    EXPECT_EQ(expectedValues1, query.getCommonElements(values1, values2, values3));
}

TEST(FindCommonElementsInThreeSortedContainersTest, GetValuePairThatIsClosestToSumWorksOnExample2) {
    ValuesForTest values1{1, 5, 5};
    ValuesForTest values2{3, 4, 5, 5, 10};
    ValuesForTest values3{5, 5, 10, 20};
    QueryForTest query;

    ValuesForTest expectedValues1{5, 5};
    EXPECT_EQ(expectedValues1, query.getCommonElements(values1, values2, values3));
}

}  // namespace algorithm

}  // namespace alba
