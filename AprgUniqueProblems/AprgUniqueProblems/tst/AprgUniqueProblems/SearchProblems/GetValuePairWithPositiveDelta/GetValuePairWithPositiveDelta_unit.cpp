#include <AprgUniqueProblems/SearchProblems/GetValuePairWithPositiveDelta/GetValuePairWithPositiveDelta.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using QueryForTest = GetValuePairWithPositiveDelta<ValuesForTest>;
using ValuePairForTest = QueryForTest::ValuePair;
}

TEST(GetValuePairWithPositiveDeltaTest, GetNumberOfOnesInASortedBinaryContainerWorksOnEmpty)
{
    ValuesForTest sortedValues;
    QueryForTest query(sortedValues);

    ValuePairForTest pairToExpect{};
    EXPECT_EQ(pairToExpect, query.getValuePairWithPositiveDelta(8U));
}

TEST(GetValuePairWithPositiveDeltaTest, GetNumberOfOnesInASortedBinaryContainerWorksOnOneValue)
{
    ValuesForTest sortedValues{5U};
    QueryForTest query(sortedValues);

    ValuePairForTest pairToExpect{};
    EXPECT_EQ(pairToExpect, query.getValuePairWithPositiveDelta(8U));
}

TEST(GetValuePairWithPositiveDeltaTest, GetPossibleDuplicatedTwoValuesWithSumWithIndexesDoesNotWorkOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    QueryForTest query(sortedValues);

    ValuePairForTest pairToExpect{1U, 9U};
    EXPECT_EQ(pairToExpect, query.getValuePairWithPositiveDelta(8U));
}

}

}
