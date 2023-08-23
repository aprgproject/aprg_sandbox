#include <UniqueProblems/SearchProblems/FindThePairWithClosestToSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValueForTest = int;
using ValuesForTest = vector<ValueForTest>;
using QueryForTest = FindThePairWithClosestToSum<ValuesForTest>;
}  // namespace

TEST(FindThePairWithClosestToSumTest, GetValuePairThatIsClosestToSumWorksWhenFirstContainerIsEmpty) {
    ValuesForTest values1{1, 4, 5, 7};
    ValuesForTest values2;
    QueryForTest query;

    QueryForTest::ValuePair expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairThatIsClosestToSum(values1, values2, 32));
}

TEST(FindThePairWithClosestToSumTest, GetValuePairThatIsClosestToSumWorksWhenSecondContainerIsEmpty) {
    ValuesForTest values1;
    ValuesForTest values2{10, 20, 30, 40};
    QueryForTest query;

    QueryForTest::ValuePair expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairThatIsClosestToSum(values1, values2, 32));
}

TEST(FindThePairWithClosestToSumTest, GetValuePairThatIsClosestToSumWorksOnExample1) {
    ValuesForTest values1{1, 4, 5, 7};
    ValuesForTest values2{10, 20, 30, 40};
    QueryForTest query;

    QueryForTest::ValuePair expectedValuePair1{1, 30};
    QueryForTest::ValuePair expectedValuePair2{7, 40};
    EXPECT_EQ(expectedValuePair1, query.getValuePairThatIsClosestToSum(values1, values2, 32));
    EXPECT_EQ(expectedValuePair2, query.getValuePairThatIsClosestToSum(values1, values2, 50));
}

}  // namespace algorithm

}  // namespace alba
