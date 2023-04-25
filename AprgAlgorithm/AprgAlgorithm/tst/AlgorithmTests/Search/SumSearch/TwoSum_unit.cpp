#include <Algorithm/Search/SumSearch/TwoSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<unsigned int>;
using SumSearch = TwoSum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using ValuePairForTest = SumSearch::ValuePair;
}  // namespace

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWorksOnExample1) {
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(search.getNonDuplicateTwoValuesWithSum(12U));

    ValuePairForTest pairToExpect{5U, 7U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWithIndexesWorksOnExample1) {
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(search.getNonDuplicateTwoValuesWithSum(12U, 2U, 4U));

    ValuePairForTest pairToExpect{5U, 7U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWithIndexesDoesNotWorkOnExample1) {
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(
        search.getNonDuplicateTwoValuesWithSum(12U, 3U, 4U));  // index must be within 2U and 4U

    ValuePairForTest pairToExpect{0U, 0U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatedTwoValuesWithSumWorksOnExample1) {
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(search.getPossibleDuplicatedTwoValuesWithSum(18U));

    ValuePairForTest pairToExpect{9U, 9U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatedTwoValuesWithSumWithIndexesWorksOnExample1) {
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(search.getPossibleDuplicatedTwoValuesWithSum(18U, 4U, 6U));

    ValuePairForTest pairToExpect{9U, 9U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatedTwoValuesWithSumWithIndexesDoesNotWorkOnExample1) {
    ValuesForTest sortedValues{1U, 4U, 5U, 6U, 7U, 9U, 10U};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(
        search.getPossibleDuplicatedTwoValuesWithSum(18U, 6U, 6U));  // index must be within 2U and 4U

    ValuePairForTest pairToExpect{0U, 0U};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

}  // namespace algorithm

}  // namespace alba
