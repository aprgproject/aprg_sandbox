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

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWithIndicesWorksOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getNonDuplicateTwoValuesWithSum(12U, 2U, 4U));

    ValuesPairForTest pairToExpect{5U, 7U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWithIndicesDoesNotWorkOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getNonDuplicateTwoValuesWithSum(12U, 3U, 4U)); // index must be within 2U and 4U

    ValuesPairForTest pairToExpect{0U, 0U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatesTwoValuesWithSumWorksOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getPossibleDuplicatesTwoValuesWithSum(18U));

    ValuesPairForTest pairToExpect{9U, 9U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatesTwoValuesWithSumWithIndicesWorksOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getPossibleDuplicatesTwoValuesWithSum(18U, 4U, 6U));

    ValuesPairForTest pairToExpect{9U, 9U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatesTwoValuesWithSumWithIndicesDoesNotWorkOnExample1)
{
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuesPairForTest pairToVerify(search.getPossibleDuplicatesTwoValuesWithSum(18U, 6U, 6U)); // index must be within 2U and 4U

    ValuesPairForTest pairToExpect{0U, 0U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

}

}
