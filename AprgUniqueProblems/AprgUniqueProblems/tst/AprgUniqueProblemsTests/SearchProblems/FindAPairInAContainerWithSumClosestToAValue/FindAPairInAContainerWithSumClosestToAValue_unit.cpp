#include <AprgUniqueProblems/SearchProblems/FindAPairInAContainerWithSumClosestToAValue/FindAPairInAContainerWithSumClosestToAValue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using QueryForTest = FindAPairInAContainerWithSumClosestToAValue<ValuesForTest>;
using ValuePairForTest = QueryForTest::ValuePair;
}  // namespace
TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnEmpty) {
    ValuesForTest valuesForTest;
    QueryForTest query(valuesForTest);

    QueryForTest::ValuePair expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(50));
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnOneValue) {    ValuesForTest valuesForTest{12};
    QueryForTest query(valuesForTest);

    QueryForTest::ValuePair expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(50));
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnExample1) {
    ValuesForTest valuesForTest{12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
    QueryForTest query(valuesForTest);

    QueryForTest::ValuePair expectedValuePair{12, 39};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(50));
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnExample2) {
    ValuesForTest valuesForTest{10, 22, 28, 29, 30, 40};
    QueryForTest query(valuesForTest);

    QueryForTest::ValuePair expectedValuePair{22, 30};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(54));
}

}  // namespace algorithm
}  // namespace alba