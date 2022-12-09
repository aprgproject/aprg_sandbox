#include <AprgUniqueProblems/SearchProblems/FindAPairInAContainerWithSumClosestToAValue/FindAPairInAContainerWithSumClosestToAValue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using QueryForTest = FindAPairInAContainerWithSumClosestToAValue<ValuesForTest>;
using ValuePairForTest = QueryForTest::ValuePair;
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnEmpty)
{
    ValuesForTest valuesForTest;
    QueryForTest query(valuesForTest);

    QueryForTest::ValuePair expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(50U));
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnOneValue)
{
    ValuesForTest valuesForTest{12};
    QueryForTest query(valuesForTest);

    QueryForTest::ValuePair expectedValuePair{};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(50U));
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnExample1)
{
    ValuesForTest valuesForTest{12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
    QueryForTest query(valuesForTest);

    QueryForTest::ValuePair expectedValuePair{12U, 39U};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(50U));
}

TEST(FindAPairInAContainerWithSumClosestToAValueTest, GetValuePairWithSumClosestToAValueWorksOnExample2)
{
    ValuesForTest valuesForTest{10, 22, 28, 29, 30, 40};
    QueryForTest query(valuesForTest);

    QueryForTest::ValuePair expectedValuePair{22U, 30U};
    EXPECT_EQ(expectedValuePair, query.getValuePairWithSumClosestToAValue(54U));
}

}

}
