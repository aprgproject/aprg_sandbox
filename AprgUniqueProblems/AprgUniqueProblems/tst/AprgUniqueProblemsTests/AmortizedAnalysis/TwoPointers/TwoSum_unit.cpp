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
    TwoSum search({10, 9, 9, 7, 1, 4, 5, 6});

    EXPECT_EQ((ValuesPair{5, 7}), search.getTwoValuesWithSum(12));
}

}  // namespace alba
