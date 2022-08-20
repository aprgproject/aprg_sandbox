#include <Algorithm/Search/SumSearch/TwoSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using SumSearch = TwoSum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using ValuesPairForTest = SumSearch::ValuesPair;
}

TEST(TwoSumTest, GetTwoValuesWithSumWorksOnExample1)
{
    SumSearch search;
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};

    ValuesPairForTest pairToVerify(search.getTwoValuesWithSum(12U, sortedValues));

    ValuesPairForTest pairToExpect{5U, 7U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetTwoValuesWithSumWithIndicesWorksOnExample1)
{
    SumSearch search;
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};

    ValuesPairForTest pairToVerify(search.getTwoValuesWithSum(12U, 2U, 4U, sortedValues));

    ValuesPairForTest pairToExpect{5U, 7U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetTwoValuesWithSumWithIndicesDoesNotWorkOnExample1)
{
    SumSearch search;
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};

    ValuesPairForTest pairToVerify(search.getTwoValuesWithSum(12U, 3U, 4U, sortedValues)); // index must be within 2U and 4U

    ValuesPairForTest pairToExpect{0U, 0U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

}

}