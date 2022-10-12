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

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWorksOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getNonDuplicateTwoValuesWithSum(12U));

    ValuesPairForTest pairToExpect{5U, 7U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWithIndexesWorksOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getNonDuplicateTwoValuesWithSum(12U, 2U, 4U));

    ValuesPairForTest pairToExpect{5U, 7U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWithIndexesDoesNotWorkOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getNonDuplicateTwoValuesWithSum(12U, 3U, 4U)); // index must be within 2U and 4U

    ValuesPairForTest pairToExpect{0U, 0U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatedTwoValuesWithSumWorksOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getPossibleDuplicatedTwoValuesWithSum(18U));

    ValuesPairForTest pairToExpect{9U, 9U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatedTwoValuesWithSumWithIndexesWorksOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getPossibleDuplicatedTwoValuesWithSum(18U, 4U, 6U));

    ValuesPairForTest pairToExpect{9U, 9U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatedTwoValuesWithSumWithIndexesDoesNotWorkOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getPossibleDuplicatedTwoValuesWithSum(18U, 6U, 6U)); // index must be within 2U and 4U

    ValuesPairForTest pairToExpect{0U, 0U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

}

}
