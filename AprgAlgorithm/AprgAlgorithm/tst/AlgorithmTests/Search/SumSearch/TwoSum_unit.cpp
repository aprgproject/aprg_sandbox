#include <Algorithm/Search/SumSearch/TwoSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using SumSearch = TwoSum<ValuesForTest>;
using ValueForTest = SumSearch::Value;
using ValuePairForTest = SumSearch::ValuePair;
}  // namespace

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWorksOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 9, 10};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(search.getNonDuplicateTwoValuesWithSum(12));

    ValuePairForTest pairToExpect{5, 7};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWithIndexesWorksOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 9, 10};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(search.getNonDuplicateTwoValuesWithSum(12, 2, 4));

    ValuePairForTest pairToExpect{5, 7};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetNonDuplicateTwoValuesWithSumWithIndexesDoesNotWorkOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 9, 10};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(
        search.getNonDuplicateTwoValuesWithSum(12, 3, 4));  // index must be within 2 and 4

    ValuePairForTest pairToExpect{0, 0};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatedTwoValuesWithSumWorksOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 10};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(search.getPossibleDuplicatedTwoValuesWithSum(18));

    ValuePairForTest pairToExpect{9, 9};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatedTwoValuesWithSumWithIndexesWorksOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 10};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(search.getPossibleDuplicatedTwoValuesWithSum(18, 4, 6));

    ValuePairForTest pairToExpect{9, 9};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

TEST(TwoSumTest, GetPossibleDuplicatedTwoValuesWithSumWithIndexesDoesNotWorkOnExample1) {
    ValuesForTest sortedValues{1, 4, 5, 6, 7, 9, 10};
    SumSearch search(sortedValues);

    ValuePairForTest pairToVerify(
        search.getPossibleDuplicatedTwoValuesWithSum(18, 6, 6));  // index must be within 2 and 4

    ValuePairForTest pairToExpect{0, 0};
    EXPECT_EQ(pairToExpect, pairToVerify);
}

}  // namespace algorithm

}  // namespace alba
