#include <AprgUniqueProblems/AmortizedAnalysis/TwoPointers/TwoSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Value = TwoSum::Value;
using Values = TwoSum::Values;
using ValuesPair = TwoSum::ValuesPair;
}  // namespace

TEST(TwoSumTest, GetTwoIndexesWithSumWorksOnExample1) {
    TwoSum search({10U, 9U, 9U, 7U, 1U, 4U, 5U, 6U});

    EXPECT_EQ((ValuesPair{5U, 7U}), search.getTwoValuesWithSum(12));
}

}  // namespace alba
